#include "beacon.h"

void Beacon::StartBlink(const QString& IP_address, const QString& port_reply, const QString& name_chat, zmq::context_t* context_inproc) {
  zmq::context_t context(1);
  zmq::socket_t beacon(context, ZMQ_PUB);
  beacon.bind("tcp://" + IP_address.toStdString() + ":60000");
  
  zmq::socket_t stop_blink(*context_inproc, ZMQ_DEALER);
  stop_blink.connect("inproc://stopblink");

  zmq::message_t message_inproc(1);
  while (!stop_blink.recv(&message_inproc, ZMQ_DONTWAIT)) {
      QString text_message(IP_address + ' ' + port_reply + ' ' + name_chat);
      zmq::message_t message(text_message.toStdString().length() + 1);
      memcpy(message.data(), text_message.toStdString().c_str(), text_message.toStdString().length() + 1);
      beacon.send(message);
  }

  stop_blink.send(message_inproc, ZMQ_DONTWAIT);
}
