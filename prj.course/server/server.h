#ifndef SERVER_H
#define SERVER_H

#include "ui_server.h"

#include <vector>
#include <QMainWindow>
#include <QString>
#include <QThread>
#include <zmq.hpp>

class Server : public QMainWindow {
  Q_OBJECT

 public:
  Server(QWidget* parent = 0);
  ~Server();

 public slots:
  void Start();
  void Stop();
  void Update();

 signals:
  void StartForward(const QString& IP_address, const QString& name_chat,
                    zmq::context_t* context_inproc);

 private:
  Ui::MainWindow ui;
  std::vector<QString> IP_addresses_;
  QThread thread_;
  zmq::context_t context_inproc_{ 0 };
  zmq::socket_t stop_forward_{ context_inproc_, ZMQ_DEALER };
};

#endif
