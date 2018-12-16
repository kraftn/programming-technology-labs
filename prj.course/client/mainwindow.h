#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>
#include <QtWidgets/QMainWindow>
#include <QTextEdit>
#include <QThread>
#include <zmq.hpp>
#include "ui_mainwindow.h"

class mainwindow : public QMainWindow {
  Q_OBJECT

 public:
  mainwindow(QWidget* parent = 0);
  ~mainwindow();

 public slots:
  void SetSettings();
  void EnterChat();
  void Send();
  void Exit();
  void Save();

 signals:
  void StartReceive(QTextEdit* text_edit, std::string* IP_address,
                    std::string* port_pub, std::string* head_letter);

 private:
  Ui::MainWindow ui;
  std::string IP_address_{ "" };
  std::string port_pub_{ "" };
  std::string port_rec_{ "" };
  std::string name_{ "" };
  std::string head_letter_{ "" };
  zmq::context_t context_{ 1 };
  zmq::socket_t sender_{ context_, ZMQ_DEALER };
  QThread thread_;
};

#endif