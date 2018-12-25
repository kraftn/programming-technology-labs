#ifndef RECEIVER_H
#define RECEIVER_H

#include <string>
#include <QObject>
#include <QTextEdit>
#include <QString>
#include <zmq.hpp>

class Receiver: public QObject {

  Q_OBJECT

 public slots:

  void StartReceive(const QString& IP_address, const QString& port_pub,
                    const QString& head_letter) {
    zmq::context_t context(1);

    zmq::socket_t subscriber(context, ZMQ_SUB);

    QString configure("tcp://" + IP_address + ":" + port_pub);
    subscriber.connect(configure.toStdString());

    int option(1);
    subscriber.setsockopt(ZMQ_INVERT_MATCHING, &option, sizeof(option));
    subscriber.setsockopt(ZMQ_SUBSCRIBE, head_letter.toStdString().c_str(),
                          head_letter.toStdString().length());

    while (true) {
      zmq::message_t incoming;
      subscriber.recv(&incoming);
      emit SendResult(reinterpret_cast<char*>(incoming.data()));
    }
  }

 signals:
  void SendResult(const char* result);
};

#endif