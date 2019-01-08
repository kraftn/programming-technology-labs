#include "settings.h"

#include <cstddef>
#include <cmath>
#include <QSizePolicy>
#include <QNetWorkInterface>
#include <QNetworkAddressEntry>
#include <QAbstractSocket>
#include <QHostAddress>
#include <QList>
#include <QMessageBox>
#include <QString>
#include <zmq.hpp>

Settings::Settings(QWidget* parent)
  : QDialog(parent, Qt::WindowTitleHint | Qt::WindowSystemMenuHint |
            Qt::WindowCloseButtonHint) {
  ui.setupUi(this);

  statusbar.setSizeGripEnabled(false);
  QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
  sizePolicy.setHorizontalStretch(0);
  sizePolicy.setVerticalStretch(0);
  sizePolicy.setHeightForWidth(statusbar.sizePolicy().hasHeightForWidth());
  statusbar.setSizePolicy(sizePolicy);
  ui.gridLayout->addWidget(&statusbar, 8 ,0 ,1 ,2);

  connect(ui.pushButton_save, SIGNAL(clicked()), this, SLOT(accept()));
  connect(ui.pushButton_cancel, SIGNAL(clicked()), this, SLOT(reject()));
  connect(ui.pushButton_search, SIGNAL(clicked()), this, SLOT(Scan()));

  QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
  for (ptrdiff_t i_interfaces(0); i_interfaces < interfaces.size(); i_interfaces += 1) {
    if (interfaces[i_interfaces].flags().testFlag(QNetworkInterface::IsRunning)) {
      QList<QNetworkAddressEntry> entries = interfaces[i_interfaces].addressEntries();
      for (ptrdiff_t i_entries(0); i_entries < entries.size(); i_entries += 1) {
        if (QAbstractSocket::IPv4Protocol == entries[i_entries].ip().protocol() && !entries[i_entries].ip().isLoopback()) {
          quint32 network(0);
          network = entries[i_entries].ip().toIPv4Address() & entries[i_entries].netmask().toIPv4Address();
          networks_.push_back(network);
          netmasks_.push_back(entries[i_entries].netmask().toIPv4Address());
          ui.comboBox_networks->addItem(QHostAddress(network).toString() + " / " + entries[i_entries].netmask().toString());
        }
      }
    }
  }

}



void Settings::Scan() {
  if (-1 == ui.comboBox_networks->currentIndex()) {
    QMessageBox::information(this, "Ошибка", "Выберите IP-адрес сети.");
    return;
  }

  zmq::context_t context(1);
  zmq::socket_t scanner(context, ZMQ_SUB);
  scanner.setsockopt(ZMQ_SUBSCRIBE, "", 0);
  
  int32_t amount(0);
  quint32 netmask(netmasks_[ui.comboBox_networks->currentIndex()]);
  while (0 == netmask % 2) {
    amount += 1;
    netmask = netmask / 2;
  }
  quint32 network(networks_[ui.comboBox_networks->currentIndex()]);
  for (ptrdiff_t i(1); i < pow(2,amount) - 1; i += 1) {
    network += 1;
    std::string endpoint("tcp://" + QHostAddress(network).toString().toStdString() + ":70000");
    scanner.connect(endpoint);
  }

  zmq::pollitem_t pollin;
  pollin.socket = static_cast<void*>(scanner);
  pollin.events = ZMQ_POLLIN;
  pollin.revents = 1;

  IP_addresses_.clear();
  ports_reply_.clear();
  names_chat_.clear();
  ui.comboBox_rooms->clear();

  statusbar.showMessage("Поиск серверов...");
  while (pollin.revents != 0) {
    zmq::poll(&pollin, 1, 3000);

    if (pollin.revents != 0) {
      zmq::message_t message;
      scanner.recv(&message);
      std::string text_message(reinterpret_cast<char*>(message.data()));

      std::string IP_address(text_message.substr(0, text_message.find_first_of(' ')));
      IP_addresses_.push_back(IP_address);
      scanner.disconnect("tcp://" + IP_address + ":70000");
      text_message.erase(0, text_message.find_first_of(' ') + 1);
      ports_reply_.push_back(text_message.substr(0, text_message.find_first_of(' ')));
      std::string name_chat(text_message.erase(0, text_message.find_first_of(' ') + 1));
      names_chat_.push_back(name_chat);
      ui.comboBox_rooms->addItem(QString::fromStdString(name_chat));
    }
  }
  statusbar.clearMessage();

  if (IP_addresses_.empty()) {
    QMessageBox::information(this, "Результат", "Ни один сервер не был найден.");
  }
}



std::string Settings::GetIPAddress() const {
  if (ui.comboBox_rooms->currentIndex() != -1) {
    return IP_addresses_[ui.comboBox_rooms->currentIndex()];
  } else {
    return std::string("");
  }
}



std::string Settings::GetPortReply() const {
  if (ui.comboBox_rooms->currentIndex() != -1) {
    return ports_reply_[ui.comboBox_rooms->currentIndex()];
  }
  else {
    return std::string("");
  }
}



std::string Settings::GetNameChat() const {
  if (ui.comboBox_rooms->currentIndex() != -1) {
    return names_chat_[ui.comboBox_rooms->currentIndex()];
  }
  else {
    return std::string("");
  }
}
