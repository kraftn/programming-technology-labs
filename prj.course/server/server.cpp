#include "server.h"
#include "forwarder.h"

#include <cstddef>
#include <QNetWorkInterface>
#include <QNetworkAddressEntry>
#include <QAbstractSocket>
#include <QList>
#include <QMessageBox>

Server::Server(QWidget* parent)
  : QMainWindow(parent) {
  ui.setupUi(this);
  connect(ui.pushButton_start, SIGNAL(clicked()), this, SLOT(Start()));
  connect(ui.pushButton_stop, SIGNAL(clicked()), this, SLOT(Stop()));
  connect(ui.pushButton_update, SIGNAL(clicked()), this, SLOT(Update()));
  stop_forward_.bind("inproc://stopforward");
}



Server::~Server() {
  if (thread_.isRunning()) {
    Stop();
  }
}



void Server::Start() {
  if (-1 == ui.comboBox->currentIndex()) {
    QMessageBox::information(nullptr, "Ошибка", "Выберите IP-адрес.");
    return;
  }

  if (ui.lineEdit->text().isEmpty()) {
    QMessageBox::information(nullptr, "Ошибка", "Введите название чата. Оно не должно быть пустым.");
    return;
  }

  ui.comboBox->setEnabled(false);
  ui.pushButton_update->setEnabled(false);
  ui.lineEdit->setEnabled(false);
  ui.pushButton_start->setEnabled(false);
  ui.pushButton_stop->setEnabled(true);

  QString IP_address(IP_addresses_[ui.comboBox->currentIndex()]);
  QString name_chat(ui.lineEdit->text());

  Forwarder* forwarder = new Forwarder();
  forwarder->moveToThread(&thread_);
  connect(this, &Server::StartForward, forwarder, &Forwarder::StartForward);
  connect(&thread_, &QThread::finished, forwarder, &QObject::deleteLater);

  thread_.start();
  emit StartForward(IP_address, name_chat, &context_inproc_);
}



void Server::Stop() {
  ui.comboBox->setEnabled(true);
  ui.pushButton_update->setEnabled(true);
  ui.lineEdit->setEnabled(true);
  ui.pushButton_start->setEnabled(true);
  ui.pushButton_stop->setEnabled(false);

  zmq::message_t message(1);
  stop_forward_.send(message, ZMQ_DONTWAIT);
  stop_forward_.recv(&message);

  thread_.quit();
  thread_.wait();
}



void Server::Update() {
  IP_addresses_.clear();
  ui.comboBox->clear();

  QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
  for (ptrdiff_t i_interfaces(0); i_interfaces < interfaces.size(); i_interfaces += 1) {
    if (interfaces[i_interfaces].flags().testFlag(QNetworkInterface::IsRunning)) {
      QList<QNetworkAddressEntry> entries = interfaces[i_interfaces].addressEntries();
      for (ptrdiff_t i_entries(0); i_entries < entries.size(); i_entries += 1) {
        if (entries[i_entries].ip().protocol() == QAbstractSocket::IPv4Protocol && !entries[i_entries].ip().isLoopback()) {
          IP_addresses_.push_back(entries[i_entries].ip().toString());
          ui.comboBox->addItem(entries[i_entries].ip().toString() + " / " + entries[i_entries].netmask().toString());
        }
      }
    }
  }

  if (IP_addresses_.empty()) {
    QMessageBox::information(nullptr, "Ошибка", "Подходящие IP-адреса не были найдены.");
  }
}
