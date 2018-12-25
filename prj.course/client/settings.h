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
  QString GetIPAddress() const;
  QString GetPort1() const;
  QString GetPort2() const;
  void SetIPAddress(const QString& IP_address);
  void SetPort1(const QString& port1);
  void SetPort2(const QString& port2);

 private:
  Ui::Dialog ui;
};

#endif