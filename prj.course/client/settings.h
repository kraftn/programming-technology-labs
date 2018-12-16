#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>
#include <QtWidgets/QDialog>
#include "ui_settings.h"

class settings : public QDialog {

  Q_OBJECT

 public:
  settings(QWidget* parent = 0);
  ~settings();
  std::string GetIPAddress() const;
  std::string GetPort1() const;
  std::string GetPort2() const;
  void SetIPAddress(std::string IP_address);
  void SetPort1(std::string port1);
  void SetPort2(std::string port2);

 private:
  Ui::Dialog ui;
};

#endif