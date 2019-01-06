#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include <QObject>
#include <QString>
#include <zmq.hpp>

class Subscriber: public QObject {

  Q_OBJECT

 public:
  Subscriber() {};
  ~Subscriber() {};

 public slots:
 void StartReceive(const QString& IP_address, const QString& port_publisher, const QString& head_letter, zmq::context_t* context_inproc);

 signals:
  void SendResult(const char* result);
};

#endif
