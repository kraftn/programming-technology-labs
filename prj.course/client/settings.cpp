#include <QMessageBox>
#include "settings.h"

settings::settings(QWidget* parent)
  : QDialog(parent, Qt::WindowTitleHint | Qt::WindowSystemMenuHint |
            Qt::WindowCloseButtonHint) {
  ui.setupUi(this);
  connect(ui.pushButton_save, SIGNAL(clicked()), this, SLOT(accept()));
  connect(ui.pushButton_cancel, SIGNAL(clicked()), this, SLOT(reject()));
}

settings::~settings() {

}

QString settings::GetIPAddress() const {
  return ui.lineEdit_IPAddress->text();
}

QString settings::GetPort1() const {
  return ui.lineEdit_port1->text();
}

QString settings::GetPort2() const {
  return ui.lineEdit_port2->text();
}

void settings::SetIPAddress(const QString& IP_address) {
  ui.lineEdit_IPAddress->setText(IP_address);
}

void settings::SetPort1(const QString& port1) {
  ui.lineEdit_port1->setText(port1);
}

void settings::SetPort2(const QString& port2) {
  ui.lineEdit_port2->setText(port2);
}

/*QTextCodec* codec = QTextCodec::codecForName("cp866");
QByteArray cp1251_bytes = codec->fromUnicode(s);
std::cout << atoi(cp1251_bytes.data());*/