#include "client.h"
#include "settings.h"
#include "subscriber.h"

#include <cstring>
#include <QSettings>
#include <QMessageBox>
#include <QTimer>
#include <QFileDialog>

Client::Client(QWidget* parent)
  : QMainWindow(parent) {
  ui.setupUi(this);
  connect(ui.action_download, SIGNAL(triggered()), this, SLOT(DownloadSettings()));
  connect(ui.action_change, SIGNAL(triggered()), this, SLOT(SetSettings()));
  connect(ui.action_save, SIGNAL(triggered()), this, SLOT(SaveSettings()));
  connect(ui.pushButton_come_in, SIGNAL(clicked()), this, SLOT(EnterChat()));
  connect(ui.pushButton_send, SIGNAL(clicked()), this, SLOT(SendLetter()));
  connect(ui.pushButton_exit, SIGNAL(clicked()), this, SLOT(LeaveChat()));
  
  stop_subscribe.bind("inproc://stopsubscribe");
  int32_t option_linger(0);
  request_.setsockopt(ZMQ_LINGER, &option_linger, sizeof(option_linger));
  int32_t option_relaxed(1);
  request_.setsockopt(ZMQ_REQ_RELAXED, &option_relaxed, sizeof(option_relaxed));
  sender_.setsockopt(ZMQ_LINGER, &option_linger, sizeof(option_linger));
}



Client::~Client() {
  if (thread_.isRunning()) {
    LeaveChat();
  }
}



void Client::DownloadSettings() {
  QString path = QFileDialog::getOpenFileName(this, "Загрузить настройки", QString(),
                                              "*.ini");
  if (!path.isNull()) {
    QSettings settings(path, QSettings::IniFormat);
    IP_address_ = settings.value("setting/IP_address").toString().toStdString();
    port_reply_ = settings.value("setting/port_reply").toString().toStdString();
    name_chat_ = settings.value("setting/name_chat").toString().toStdString();
    if (IP_address_.empty() || port_reply_.empty() || name_chat_.empty()) {
      QMessageBox::information(this, "Ошибка", "Неверные данные в файле.");
      IP_address_ = "";
      port_reply_ = "";
      name_chat_ = "";
    } else {
      ui.label_name_chat->setText(QString::fromStdString(name_chat_));
    }
  }
}



void Client::SetSettings() {
  Settings w;
  if (QDialog::Accepted == w.exec()) {
    IP_address_ = w.GetIPAddress();
    port_reply_ = w.GetPortReply();
    name_chat_ = w.GetNameChat();
    ui.label_name_chat->setText(QString::fromStdString(name_chat_));
  }
}



void Client::SaveSettings() {
  QString path = QFileDialog::getSaveFileName(this, "Сохранить настройки", QString(),
                                              "*.ini");
  if (!path.isNull()) {
    QSettings settings(path, QSettings::IniFormat);
    settings.setValue("setting/IP_address", QString::fromStdString(IP_address_));
    settings.setValue("setting/port_reply", QString::fromStdString(port_reply_));
    settings.setValue("setting/name_chat", QString::fromStdString(name_chat_));
    settings.sync();
  }
}



void Client::EnterChat() {
  name_ = ui.lineEdit_enter_name->text();

  if (IP_address_.empty()) {
    QMessageBox::information(this, "Ошибка", "Выберите сервер в настройках.");
    return;
  }
  if (name_.isEmpty()) {
    QMessageBox::information(this, "Ошибка", "Введите Ваше имя. Оно не должно быть пустым.");
    return;
  }

  std::string endpoint_reply("tcp://" + IP_address_ + ":" + port_reply_);
  request_.connect(endpoint_reply);

  zmq::pollitem_t pollin;
  pollin.socket = static_cast<void*>(request_);
  pollin.events = ZMQ_POLLIN;

  QString text_outgoing("1 " + name_);
  zmq::message_t outgoing(text_outgoing.toStdString().length() + 1);
  memcpy(outgoing.data(), text_outgoing.toStdString().c_str(),
    text_outgoing.toStdString().length() + 1);
  request_.send(outgoing, ZMQ_DONTWAIT);
  
  ui.statusbar->showMessage("Подключение к серверу...");
  zmq::poll(&pollin, 1, 3000);
  ui.statusbar->clearMessage();

  QString port_publisher("");
  if (0 == pollin.revents) {
    QMessageBox::information(this, "Ошибка", "Проблемы с подключением к серверу.");
    request_.disconnect(endpoint_reply);
    return;
  }
  
  zmq::message_t incoming;
  request_.recv(&incoming);
  std::string incoming_text(reinterpret_cast<char*>(incoming.data()));
  if ('0' == incoming_text[0]) {
    QMessageBox::information(this, "Ошибка",
                              "Участник чата с таким именем уже существует. Введите другое имя.");
    request_.disconnect(endpoint_reply);
    return;
  }
  
  port_receiver_ = incoming_text.substr(2, incoming_text.find_last_of(' ') - 2);
  port_publisher = QString::fromStdString(incoming_text.substr(incoming_text.find_last_of(' ') + 1, 
    incoming_text.length() - incoming_text.find_last_of(' ') - 1));

  ui.pushButton_send->setEnabled(true);
  ui.pushButton_exit->setEnabled(true);
  ui.lineEdit_enter_name->setEnabled(false);
  ui.pushButton_come_in->setEnabled(false);
  ui.action_change->setEnabled(false);
  ui.action_download->setEnabled(false);

  std::string endpoint_receiver = "tcp://" + IP_address_ + ":" + port_receiver_;
  sender_.connect(endpoint_receiver);

  Subscriber* receiver = new Subscriber();
  receiver->moveToThread(&thread_);
  connect(this, &Client::StartReceive, receiver, &Subscriber::StartReceive);
  connect(receiver, &Subscriber::SendResult, this, &Client::GetResult);
  connect(&thread_, &QThread::finished, receiver, &QObject::deleteLater);

  thread_.start();
  emit StartReceive(QString::fromStdString(IP_address_), port_publisher, name_ + ": ", &context_);

  QString text_message(name_ + ": " + name_ + " присоединился к чату");
  ui.textEdit_chat->append(text_message);

  zmq::message_t message(text_message.toStdString().length() + 1);
  memcpy(message.data(), text_message.toStdString().c_str(),
        text_message.toStdString().length() + 1);
  sender_.send(message, ZMQ_DONTWAIT);
}



void Client::SendLetter() {
  QString text_message(ui.textEdit_message->toPlainText());
  text_message = name_ + ": " + text_message;

  ui.textEdit_chat->append(text_message);

  zmq::message_t outgoing(text_message.toStdString().length() + 1);
  memcpy(outgoing.data(), text_message.toStdString().c_str(),
         text_message.toStdString().length() + 1);
  sender_.send(outgoing, ZMQ_DONTWAIT);

  ui.textEdit_message->clear();
}



void Client::LeaveChat() {
  QString text_message(name_ + ": " + name_ + " отключился от чата");

  zmq::message_t message_bye(text_message.toStdString().length() + 1);
  memcpy(message_bye.data(), text_message.toStdString().c_str(),
         text_message.toStdString().length() + 1);
  sender_.send(message_bye, ZMQ_DONTWAIT);

  text_message = "0 " + name_;
  zmq::message_t message_name(text_message.toStdString().length() + 1);
  memcpy(message_name.data(), text_message.toStdString().c_str(),
    text_message.toStdString().length() + 1);
  request_.send(message_name, ZMQ_DONTWAIT);

  zmq::message_t message_inproc(1);
  stop_subscribe.send(message_inproc, ZMQ_DONTWAIT);
  stop_subscribe.recv(&message_inproc);
  thread_.quit();
  thread_.wait();

  std::string endpoint("tcp://" + IP_address_ + ":" + port_reply_);
  request_.disconnect(endpoint);
  endpoint = "tcp://" + IP_address_ + ":" + port_receiver_;
  sender_.disconnect(endpoint);

  ui.textEdit_chat->clear();

  ui.pushButton_send->setEnabled(false);
  ui.pushButton_exit->setEnabled(false);
  ui.lineEdit_enter_name->setEnabled(true);
  ui.pushButton_come_in->setEnabled(true);
  ui.action_change->setEnabled(true);
  ui.action_download->setEnabled(true);
}



void Client::GetResult(const char* result) {
  if (0 == strcmp(result, "0")) {
    QMessageBox::information(this, "Сообщение", "Сервер больше не работает.");
    LeaveChat();
  }
  else {
    ui.textEdit_chat->append(QString::fromUtf8(result));
  }
}
