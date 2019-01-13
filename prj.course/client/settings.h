#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>
#include <vector>
#include <QDialog>
#include <QStatusBar>

#include "ui_settings.h"

// Класс для описания логики работы окна "Настройки" клиентской части программы
class Settings : public QDialog {
  Q_OBJECT

 public:
  Settings(QWidget* parent = nullptr);
  ~Settings() {}
  // Передача IP-адреса выбранного сервера клиентской части программы
  std::string GetIPAddress() const;
  // Передача порта выбранного сервера клиентской части программы
  std::string GetPortReply() const;
  // Передача названия выбранного чата клиентской части программы
  std::string GetNameChat() const;

 public slots:
  // Поиск работающих серверов
  void Scan();

 private:
  Ui::Dialog ui;
  // Строка состояния окна "Настройки"
  QStatusBar statusbar{this};
  // IP-адреса доступных сетей
  std::vector<quint32> networks_;
  // Маски доступных сетей
  std::vector<quint32> netmasks_;
  // IP-адреса найденных серверов
  std::vector<std::string> IP_addresses_;
  // Порты найденных серверов
  std::vector<std::string> ports_reply_;
  // Названия найденных чатов
  std::vector<std::string> names_chat_;
};

#endif
