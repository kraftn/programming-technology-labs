#ifndef FORWARDER_H
#define FORWARDER_H

#include <QObject>
#include <QString>
#include <QThread>
#include <zmq.hpp>

class Forwarder: public QObject { 
 Q_OBJECT

 public:
  Forwarder() {};
  ~Forwarder();

 public slots:
  void StartForward(const QString& IP_address, const QString& name_chat, zmq::context_t* context_inproc);

 signals:
  void StartBlink(const QString& IP_address, const QString& port_reply, const QString& name_chat, zmq::context_t* context_inproc);

 private:
   QThread thread_;
   zmq::context_t context_inproc_{ 0 };
   zmq::socket_t stop_blink_{ context_inproc_, ZMQ_DEALER };
};

#endif
