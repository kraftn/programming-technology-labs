#include "subscriber.h"

#include <string>
#include <cstdint>

void Subscriber::StartReceive(const QString& IP_address, const QString& port_publisher, const QString& head_letter, zmq::context_t* context_inproc) {
  zmq::context_t context(1);

  zmq::socket_t subscriber(context, ZMQ_SUB);
  int32_t option(1);
  subscriber.setsockopt(ZMQ_INVERT_MATCHING, &option, sizeof(option));
  subscriber.setsockopt(ZMQ_SUBSCRIBE, head_letter.toStdString().c_str(),
    head_letter.toStdString().length());

  QString endpoint("tcp://" + IP_address + ":" + port_publisher);
  subscriber.connect(endpoint.toStdString());

  zmq::socket_t stop_subscribe(*context_inproc, ZMQ_DEALER);
  stop_subscribe.connect("inproc://stopsubscribe");

  zmq::pollitem_t pollin[2];
  pollin[0].socket = static_cast<void*>(subscriber);
  pollin[0].events = ZMQ_POLLIN;
  pollin[1].socket = static_cast<void*>(stop_subscribe);
  pollin[1].events = ZMQ_POLLIN;
  pollin[1].revents = 0;

  while (0 == pollin[1].revents) {
    zmq::poll(pollin, 2);

    if (pollin[0].revents != 0) {
      zmq::message_t incoming;
      subscriber.recv(&incoming);
      emit SendResult(reinterpret_cast<char*>(incoming.data()));
    } else {
      zmq::message_t message(1);
      stop_subscribe.recv(&message);
      stop_subscribe.send(message, ZMQ_DONTWAIT);
    }
  }
}
