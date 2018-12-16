#include "settings.h"

settings::settings(QWidget* parent)
  : QDialog(parent) {
  ui.setupUi(this);
  connect(ui.pushButton_save, SIGNAL(clicked()), this, SLOT(accept()));
  connect(ui.pushButton_cancel, SIGNAL(clicked()), this, SLOT(reject()));
}

settings::~settings() {

}

std::string settings::GetIPAddress() const {
  return (ui.lineEdit_IPAddress->text()).toStdString();
}

std::string settings::GetPort1() const {
  return (ui.lineEdit_port1->text()).toStdString();
}

std::string settings::GetPort2() const {
  return (ui.lineEdit_port2->text()).toStdString();
}

void settings::SetIPAddress(std::string IP_address) {
  ui.lineEdit_IPAddress->setText(QString::fromStdString(IP_address));
}

void settings::SetPort1(std::string port1) {
  ui.lineEdit_port1->setText(QString::fromStdString(port1));
}

void settings::SetPort2(std::string port2) {
  ui.lineEdit_port2->setText(QString::fromStdString(port2));
}

/*QTextCodec* codec = QTextCodec::codecForName("cp866");
QByteArray cp1251_bytes = codec->fromUnicode(s);
std::cout << atoi(cp1251_bytes.data());*/