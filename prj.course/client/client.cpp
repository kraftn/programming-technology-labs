#include <iostream>
#include <cstring>
#include <string>
#include <zmq.hpp>

int main() {
  zmq::context_t context(1);

  std::cout << "Enter IP address of the server: ";
  char IP_address[15]("");
  std::cin >> IP_address;

  std::cout << "Enter ports of the receiver and the publisher: ";
  char port_rec[10]("");
  char port_pub[10]("");
  std::cin >> port_rec >> port_pub;

  std::cout << "Enter your name: ";
  std::string name;
  std::cin >> name;
  std::string head_letter(name + ": ");

  zmq::socket_t subscriber(context, ZMQ_SUB);
  char configure[50]("tcp://");
  strcat(strcat(strcat(configure, IP_address), ":"), port_pub);
  subscriber.connect(configure);
  int option(1);
  subscriber.setsockopt(ZMQ_INVERT_MATCHING, &option, sizeof(option));
  subscriber.setsockopt(ZMQ_SUBSCRIBE, head_letter.c_str(), head_letter.length());

  zmq::socket_t sender(context, ZMQ_DEALER);
  strcpy(configure, "tcp://");
  strcat(strcat(strcat(configure, IP_address), ":"), port_rec);
  sender.connect(configure);

  std::cout << name << " has connected to chat" << std::endl;
  std::string text_message(head_letter + name + " has connected to chat");
  zmq::message_t message(text_message.length() + 1);
  memcpy(message.data(), text_message.c_str(), text_message.length() + 1);
  sender.send(message, ZMQ_DONTWAIT);
  text_message = "";

  while (true) {
    zmq::message_t incoming;
    subscriber.recv(&incoming);
    std::cout << reinterpret_cast<char*>(incoming.data()) << std::endl;

    std::getline(std::cin, text_message);
    text_message = head_letter + text_message;
    zmq::message_t outgoing(text_message.length() + 1);
    memcpy(outgoing.data(), text_message.c_str(), text_message.length() + 1);
    sender.send(outgoing, ZMQ_DONTWAIT);
    text_message = "";
  }

  return 0;
}