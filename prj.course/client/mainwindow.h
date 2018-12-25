#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>
#include <QtWidgets/QMainWindow>
#include <QTextEdit>
#include <QThread>
#include <zmq.hpp>
#include "ui_mainwindow.h"
#include "receiver.h"

class mainwindow : public QMainWindow {
  Q_OBJECT

 public:
  mainwindow(QWidget* parent = 0);
  ~mainwindow();

 public slots:
  void DownloadSettings();
  void SetSettings();
  void SaveSettings();
  void EnterChat();
  void SendLetter();
  void LeaveChat();
  void GetResult(const char* result);

 signals:
  void StartReceive(const QString& IP_address,
                    const QString& port_pub, const QString& head_letter);

 private:
  Ui::MainWindow ui;
  QString IP_address_{ "" };
  QString port_pub_{ "" };
  QString port_rec_{ "" };
  QString name_{ "" };
  QString head_letter_{ "" };
  zmq::context_t context_{ 1 };
  zmq::socket_t sender_{ context_, ZMQ_REQ };
  QThread thread_;
};

#endif