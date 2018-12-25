#include <QSettings>
#include <QMessageBox>
#include <QTextCodec>
#include "mainwindow.h"
#include "settings.h"
#include "receiver.h"
#include <QFileDialog>
#include <zmq.hpp>

#include <iostream>

mainwindow::mainwindow(QWidget* parent)
  : QMainWindow(parent) {
  ui.setupUi(this);
  connect(ui.action_download, SIGNAL(triggered()), this,
          SLOT(DownloadSettings()));
  connect(ui.action_change, SIGNAL(triggered()), this, SLOT(SetSettings()));
  connect(ui.action_save, SIGNAL(triggered()), this, SLOT(SaveSettings()));
  connect(ui.pushButton_comeIn, SIGNAL(clicked()), this, SLOT(EnterChat()));
  connect(ui.pushButton_send, SIGNAL(clicked()), this, SLOT(SendLetter()));
  connect(ui.pushButton_exit, SIGNAL(clicked()), this, SLOT(LeaveChat()));




}

mainwindow::~mainwindow() {
  thread_.quit();
  thread_.wait();
}

void mainwindow::DownloadSettings() {
  QString path = QFileDialog::getOpenFileName(nullptr, "Download settings", "",
                                              "*.ini");
  if (!path.isNull()) {
    QSettings settings(path, QSettings::IniFormat);
    IP_address_ = settings.value("setting/IP_address").toString();
    port_rec_ = settings.value("setting/port_receiver").toString();
    port_pub_ = settings.value("setting/port_publisher").toString();
  }
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

void mainwindow::SaveSettings() {
  QString path = QFileDialog::getSaveFileName(nullptr, "Save settings", "",
                                              "*.ini");
  if (!path.isNull()) {
    QSettings settings(path, QSettings::IniFormat);
    settings.setValue("setting/IP_address", IP_address_);
    settings.setValue("setting/port_receiver", port_rec_);
    settings.setValue("setting/port_publisher", port_pub_);
    settings.sync();
  }
}

void mainwindow::EnterChat() {
  name_ = ui.lineEdit_enterName->text();

  if (IP_address_ == "" || port_pub_ == "" || port_rec_ == "" || name_ == "") {
    QMessageBox::information(nullptr, "Error",
                             "Enter IP address and numbers of ports. Enter your name, it mustn't be empty.");
    return;
  }

  QString configure("tcp://" + IP_address_ + ":" + port_rec_);
  sender_.connect(configure.toStdString());

  zmq_pollitem_t pollin[1];
  pollin[0].socket = (void*)(sender_);
  pollin[0].events = ZMQ_POLLIN;

  zmq::message_t outgoing(name_.toStdString().length() + 1);
  memcpy(outgoing.data(), name_.toStdString().c_str(),
         name_.toStdString().length() + 1);
  sender_.send(outgoing);
  zmq::poll(pollin, 1, 3000);

  if (pollin[0].revents == 0) {
    QMessageBox::information(nullptr, "Error",
                             "Problems with connection to the server.");
    sender_.disconnect(configure.toStdString());
    return;
  }
  else {
    zmq::message_t incoming;
    sender_.recv(&incoming);
    std::string incoming_text(reinterpret_cast<char*>(incoming.data()));
    if (incoming_text[0] == '0') {
      QMessageBox::information(nullptr, "Error",
                               "Member with this name already exits. Choose another name.");
      sender_.disconnect(configure.toStdString());
      return;
    }
    else {
      port_pub_ = QString::fromStdString(incoming_text.substr(2,
                                                              incoming_text.length() - 2));
      sender_.disconnect(configure.toStdString());
    }
  }

  ui.pushButton_comeIn->setEnabled(false);
  ui.pushButton_send->setEnabled(true);
  ui.pushButton_exit->setEnabled(true);
  ui.lineEdit_enterName->setEnabled(false);

  head_letter_ = name_ + ": ";

  Receiver* receiver = new Receiver();
  receiver->moveToThread(&thread_);
  connect(this, &mainwindow::StartReceive, receiver, &Receiver::StartReceive);
  connect(receiver, &Receiver::SendResult, this, &mainwindow::GetResult);
  connect(&thread_, &QThread::finished, receiver, &QObject::deleteLater);

  thread_.start();
  emit StartReceive(IP_address_, port_pub_, head_letter_);

  /* QString text_message(head_letter_ + name_ + " has connected to the chat");
   ui.textEdit_chat->append(text_message);

   zmq::message_t message(text_message.toStdString().length() + 1);
   memcpy(message.data(), text_message.toStdString().c_str(),
          text_message.toStdString().length() + 1);
   sender_.send(message, ZMQ_DONTWAIT);*/
}

void mainwindow::SendLetter() {
  QString text_message(ui.textEdit_message->toPlainText());
  text_message = head_letter_ + text_message;

  ui.textEdit_chat->append(text_message);

  zmq::message_t outgoing(text_message.toStdString().length() + 1);
  memcpy(outgoing.data(), text_message.toStdString().c_str(),
         text_message.toStdString().length() + 1);
  sender_.send(outgoing, ZMQ_DONTWAIT);

  ui.textEdit_message->clear();
}

void mainwindow::LeaveChat() {
  QString text_message(head_letter_ + name_ + " has left the chat");

  zmq::message_t message(text_message.toStdString().length() + 1);
  memcpy(message.data(), text_message.toStdString().c_str(),
         text_message.toStdString().length() + 1);
  sender_.send(message, ZMQ_DONTWAIT);

  close();
}

void mainwindow::GetResult(const char* result) {
  ui.textEdit_chat->append(QString::fromUtf8(result));
}