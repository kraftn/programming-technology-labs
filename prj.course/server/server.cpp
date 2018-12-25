#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <zmq.hpp>

int main() {
  zmq::context_t context(1);

  std::string IP_address("");
  std::cout << "Enter IP address: ";
  std::cin >> IP_address;
  char configure[50]("tcp://");
  strcat(strcat(configure, IP_address.c_str()), ":*");

  zmq::socket_t reply(context, ZMQ_REP);
  reply.bind(configure);

  zmq::socket_t receiver(context, ZMQ_DEALER);
  receiver.bind(configure);

  zmq::socket_t publisher(context, ZMQ_PUB);
  int option(1);
  publisher.bind(configure);
  publisher.setsockopt(ZMQ_INVERT_MATCHING, &option, sizeof(option));

  strcpy(configure, "");
  size_t size = sizeof(configure);
  reply.getsockopt(ZMQ_LAST_ENDPOINT, configure, &size);
  std::string port_rep(configure);
  port_rep.erase(0, port_rep.find_last_of(':') + 1);
  std::cout << "Port 1: " << port_rep << std::endl;

  strcpy(configure, "");
  receiver.getsockopt(ZMQ_LAST_ENDPOINT, configure, &size);
  std::string port_rec(configure);
  port_rec.erase(0, port_rec.find_last_of(':') + 1);
  std::cout << "Port 2: " << port_rec << std::endl;

  strcpy(configure, "");
  publisher.getsockopt(ZMQ_LAST_ENDPOINT, configure, &size);
  std::string port_pub(configure);
  port_pub.erase(0, port_pub.find_last_of(':') + 1);
  std::cout << "Port 3: " << port_pub << std::endl;

  std::vector<std::string> names;

  zmq_pollitem_t pollin[2];
  pollin[0].socket = (void*)(reply);
  pollin[0].events = ZMQ_POLLIN;
  pollin[1].socket = (void*)(receiver);
  pollin[1].events = ZMQ_POLLIN;

  while (true) {
    zmq::poll(pollin, 2);

    if (pollin[0].revents != 0) {
      zmq::message_t incoming;
      reply.recv(&incoming);
      std::string text_incoming(reinterpret_cast<char*>(incoming.data()));

      std::cout << text_incoming << std::endl;


      int i_names(0);
      while (i_names < names.size() && names[i_names] != text_incoming) {
        ++i_names;
      }
      if (i_names != names.size()) {
        std::cout << "old name" << std::endl;


        zmq::message_t outgoing(2);
        memcpy(outgoing.data(), "0", 2);
        reply.send(outgoing, ZMQ_DONTWAIT);



      }
      else {




        names.push_back(text_incoming);

        std::string text_outgoing = "1 " + port_rec + " " + port_pub;
        zmq::message_t outgoing(text_outgoing.length() + 1);
        memcpy(outgoing.data(), text_outgoing.c_str(), text_outgoing.length() + 1);
        reply.send(outgoing, ZMQ_DONTWAIT);
        std::cout << "new name" << std::endl;

      }
    }

    else {

      std::cout << "pub" << std::endl;
      zmq::message_t incoming;
      receiver.recv(&incoming);
      publisher.send(incoming);


    }
  }

  return 0;
}