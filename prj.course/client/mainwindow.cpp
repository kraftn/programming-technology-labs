#include <QSettings>
#include <QMessageBox>
#include "mainwindow.h"
#include "settings.h"
#include "receiver.h"

mainwindow::mainwindow(QWidget* parent)
  : QMainWindow(parent) {
  ui.setupUi(this);
  connect(ui.action_change, SIGNAL(triggered()), this, SLOT(SetSettings()));
  connect(ui.pushButton_comeIn, SIGNAL(clicked()), this, SLOT(EnterChat()));
  connect(ui.pushButton_send, SIGNAL(clicked()), this, SLOT(Send()));
  connect(ui.pushButton_exit, SIGNAL(clicked()), this, SLOT(Exit()));
  connect(ui.action_save, SIGNAL(triggered()), this, SLOT(Save()));

  QSettings settings("settings.ini", QSettings::IniFormat);
  IP_address_ = settings.value("setting/IP_address").toString().toStdString();
  port_rec_ = settings.value("setting/port_receiver").toString().toStdString();
  port_pub_ = settings.value("setting/port_publisher").toString().toStdString();
}

mainwindow::~mainwindow() {
  thread_.quit();
  thread_.wait();
}

void mainwindow::SetSettings() {
  settings w;
  w.SetIPAddress(IP_address_);
  w.SetPort1(port_rec_);
  w.SetPort2(port_pub_);
  if (w.exec() == QDialog::Accepted) {
    IP_address_ = w.GetIPAddress();
    port_rec_ = w.GetPort1();
    port_pub_ = w.GetPort2();
  }
}

void mainwindow::EnterChat() {
  ui.textEdit_chat->clear();

  name_ = ui.lineEdit_enterName->text().toStdString();
  head_letter_ = name_ + ": ";

  Receiver* receiver = new Receiver();
  receiver->moveToThread(&thread_);
  connect(this, &mainwindow::StartReceive, receiver, &Receiver::Receive);
  connect(&thread_, &QThread::finished, receiver, &QObject::deleteLater);
  thread_.start();
  emit StartReceive(ui.textEdit_chat, &IP_address_, &port_pub_, &head_letter_);

  std::string configure("tcp://" + IP_address_ + ":" + port_rec_);
  sender_.connect(configure);

  std::string text_message(head_letter_ + name_ + " has connected to the chat");
  QString output(QString::fromStdString(text_message));
  ui.textEdit_chat->append(output);

  zmq::message_t message(text_message.length() + 1);
  memcpy(message.data(), text_message.c_str(), text_message.length() + 1);
  sender_.send(message, ZMQ_DONTWAIT);
}

void mainwindow::Send() {
  std::string text_message(ui.textEdit_message->toPlainText().toStdString());
  text_message = head_letter_ + text_message;

  QString output(QString::fromStdString(text_message));
  ui.textEdit_chat->append(output);

  zmq::message_t outgoing(text_message.length() + 1);
  memcpy(outgoing.data(), text_message.c_str(), text_message.length() + 1);
  sender_.send(outgoing, ZMQ_DONTWAIT);

  ui.textEdit_message->clear();
}

void mainwindow::Exit() {
  thread_.quit();

  std::string text_message(head_letter_ + name_ + " has leaved the chat");
  QString output(QString::fromStdString(text_message));
  ui.textEdit_chat->append(output);

  zmq::message_t message(text_message.length() + 1);
  memcpy(message.data(), text_message.c_str(), text_message.length() + 1);
  sender_.send(message, ZMQ_DONTWAIT);

  sender_.disconnect("tcp://" + IP_address_ + ":" + port_rec_);
}

void mainwindow::Save() {
  QSettings settings("settings.ini", QSettings::IniFormat);
  settings.setValue("setting/IP_address", QString::fromStdString(IP_address_));
  settings.setValue("setting/port_receiver", QString::fromStdString(port_rec_));
  settings.setValue("setting/port_publisher", QString::fromStdString(port_pub_));
  settings.sync();
}