#include <iostream>
#include <cstring>
#include <zmq.hpp>

int main() {
  zmq::context_t context(1);

  char IP_address[15]("");
  std::cout << "Enter IP address: ";
  std::cin >> IP_address;
  char configure[50]("tcp://");
  strcat(strcat(configure, IP_address), ":*");

  zmq::socket_t receiver(context, ZMQ_DEALER);
  receiver.bind(configure);

  zmq::socket_t publisher(context, ZMQ_PUB);
  int option(1);
  publisher.setsockopt(ZMQ_INVERT_MATCHING, &option, sizeof(option));
  publisher.bind(configure);

  strcpy(configure, "");
  size_t size = sizeof(configure);
  receiver.getsockopt(ZMQ_LAST_ENDPOINT, configure, &size);
  char port[10]("");
  strncpy(port, strrchr(configure, ':') + 1, strchr(configure,
                                                    '\0') - strrchr(configure, ':'));
  std::cout << "Port 1: " << port << std::endl;

  strcpy(configure, "");
  publisher.getsockopt(ZMQ_LAST_ENDPOINT, configure, &size);
  strcpy(port, "");
  strncpy(port, strrchr(configure, ':') + 1, strchr(configure,
                                                    '\0') - strrchr(configure, ':'));
  std::cout << "Port 2: " << port << std::endl;

  while (true) {
    zmq::message_t message;
    receiver.recv(&message);
    //std::cout << reinterpret_cast<char*>(message.data()) << std::endl;
    publisher.send(message);
  }

  return 0;
}