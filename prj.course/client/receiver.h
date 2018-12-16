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

  void Receive(QTextEdit* text_edit, std::string* IP_address,
               std::string* port_pub, std::string* head_letter) {
    zmq::context_t context(1);

    zmq::socket_t subscriber(context, ZMQ_SUB);

    std::string configure("tcp://" + *IP_address + ":" + *port_pub);
    subscriber.connect(configure);

    int option(1);
    subscriber.setsockopt(ZMQ_INVERT_MATCHING, &option, sizeof(option));
    subscriber.setsockopt(ZMQ_SUBSCRIBE, head_letter->c_str(),
                          head_letter->length());

    while (true) {
      zmq::message_t incoming;
      subscriber.recv(&incoming);
      text_edit->append(QString::fromUtf8(reinterpret_cast<char*>(incoming.data())));
    }
  }
};

#endif