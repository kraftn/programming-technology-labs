#ifndef SETTINGS_H
#define SETTINGS_H

#include "ui_settings.h"

#include <string>
#include <QDialog>
#include <QStatusBar>

class Settings : public QDialog {

  Q_OBJECT

 public:
  Settings(QWidget* parent = 0);
  ~Settings() {};
  std::string GetIPAddress() const;
  std::string GetPortReply() const;
  std::string GetNameChat() const;
  
 public slots:
  void Scan();
  
 private:
  Ui::Dialog ui;
  QStatusBar statusbar{this};
  std::vector<quint32> networks_;
  std::vector<quint32> netmasks_;
  std::vector<std::string> IP_addresses_;
  std::vector<std::string> ports_reply_;
  std::vector<std::string> names_chat_;
};

#endif
