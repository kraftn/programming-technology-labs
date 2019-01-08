#include "forwarder.h"
#include "beacon.h"

#include <string>
#include <cstring>
#include <cstdint>
#include <list>
#include <algorithm>

void Forwarder::StartForward(const QString& IP_address, const QString& name_chat, zmq::context_t* context_inproc) {
  zmq::context_t context(1);

  std::string endpoint_set("tcp://" + IP_address.toStdString() + ":*");

  zmq::socket_t reply(context, ZMQ_REP);
  reply.bind(endpoint_set);

  zmq::socket_t receiver(context, ZMQ_DEALER);
  receiver.bind(endpoint_set);

  zmq::socket_t publisher(context, ZMQ_PUB);
  int32_t option(1);
  publisher.setsockopt(ZMQ_INVERT_MATCHING, &option, sizeof(option));
  publisher.bind(endpoint_set);

  char endpoint_get[50]("");
  size_t size_endpoint = sizeof(endpoint_get);
  reply.getsockopt(ZMQ_LAST_ENDPOINT, endpoint_get, &size_endpoint);
  std::string port_reply(endpoint_get);
  port_reply.erase(0, port_reply.find_last_of(':') + 1);

  Beacon* beacon = new Beacon();
  beacon->moveToThread(&thread_);
  connect(this, &Forwarder::StartBlink, beacon, &Beacon::StartBlink);
  connect(&thread_, &QThread::finished, beacon, &QObject::deleteLater);
  stop_blink_.bind("inproc://stopblink");

  thread_.start();
  emit StartBlink(IP_address, QString::fromStdString(port_reply), name_chat, &context_inproc_);

  strcpy(endpoint_get, "");
  receiver.getsockopt(ZMQ_LAST_ENDPOINT, endpoint_get, &size_endpoint);
  std::string port_receiver(endpoint_get);
  port_receiver.erase(0, port_receiver.find_last_of(':') + 1);

  strcpy(endpoint_get, "");
  publisher.getsockopt(ZMQ_LAST_ENDPOINT, endpoint_get, &size_endpoint);
  std::string port_publisher(endpoint_get);
  port_publisher.erase(0, port_publisher.find_last_of(':') + 1);

  zmq::socket_t stop_forward(*context_inproc, ZMQ_DEALER);
  stop_forward.connect("inproc://stopforward");

  zmq::pollitem_t pollin[3];
  pollin[0].socket = static_cast<void*>(reply);
  pollin[0].events = ZMQ_POLLIN;
  pollin[1].socket = static_cast<void*>(receiver);
  pollin[1].events = ZMQ_POLLIN;
  pollin[2].socket = static_cast<void*>(stop_forward);
  pollin[2].events = ZMQ_POLLIN;
  pollin[2].revents = 0;

  std::list<std::string> names;
  
  while (0 == pollin[2].revents) {
    zmq::poll(pollin, 3);

    if (pollin[0].revents != 0) {
      zmq::message_t incoming;
      reply.recv(&incoming);
      std::string text_incoming(reinterpret_cast<char*>(incoming.data()));
      std::string name(text_incoming.substr(2, text_incoming.length() - 2));

      if ('0' == text_incoming[0]) {
        names.remove(name);
        zmq::message_t outgoing(1);
        reply.send(outgoing);
      }
      else {
        auto i_names = std::find(names.begin(), names.end(), name);
        if (i_names != names.end()) {
          zmq::message_t outgoing(2);
          memcpy(outgoing.data(), "0", 2);
          reply.send(outgoing);
        }
        else {
          names.push_back(name);

          std::string text_outgoing = "1 " + port_receiver + " " + port_publisher;
          zmq::message_t outgoing(text_outgoing.length() + 1);
          memcpy(outgoing.data(), text_outgoing.c_str(),
            text_outgoing.length() + 1);
          reply.send(outgoing);
        }
      }
    }

    if (pollin[1].revents != 0) {
      zmq::message_t incoming;
      receiver.recv(&incoming);
      publisher.send(incoming);
    }

    if (pollin[2].revents != 0) {
      zmq::message_t message(2);
      memcpy(message.data(), "0", 2);
      publisher.send(message);

      zmq::message_t message_inproc(1);
      stop_forward.recv(&message_inproc);
      stop_blink_.send(message_inproc, ZMQ_DONTWAIT);
      stop_blink_.recv(&message_inproc);
      stop_forward.send(message_inproc, ZMQ_DONTWAIT);
    }
  }
}



Forwarder::~Forwarder() {
  thread_.quit();
  thread_.wait();
}
