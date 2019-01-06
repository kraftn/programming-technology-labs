#ifndef CLIENT_H
#define CLIENT_H

#include "ui_client.h"

#include <string>
#include <QMainWindow>
#include <QString>
#include <QThread>
#include <zmq.hpp>

class Client : public QMainWindow {
  Q_OBJECT

 public:
  Client(QWidget* parent = 0);
  ~Client();

 public slots:
  void DownloadSettings();
  void SetSettings();
  void SaveSettings();
  void EnterChat();
  void SendLetter();
  void LeaveChat();
  void GetResult(const char* result);

 signals:
  void StartReceive(const QString& IP_address, const QString& port_publisher, const QString& head_letter, zmq::context_t* context_inproc);

 private:
  Ui::MainWindow ui;
  std::string IP_address_{ "" };
  std::string port_reply_{ "" };
  std::string port_receiver_{ "" };
  QString name_{ "" };
  std::string name_chat_{ "" };
  zmq::context_t context_{ 1 };
  zmq::socket_t sender_{ context_, ZMQ_DEALER };
  zmq::socket_t request_{ context_, ZMQ_REQ };
  zmq::socket_t stop_subscribe{ context_, ZMQ_DEALER };
  QThread thread_;
};

#endif
