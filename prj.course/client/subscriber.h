#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include <QObject>
#include <QString>
#include <zmq.hpp>

// Класс для приёма входящих сообщений программой-клиентом
class Subscriber: public QObject {
  Q_OBJECT

 public:
  Subscriber() {}
  ~Subscriber() {}

 public slots:
  // Получение данных из главного потока и начало приёма входящих сообщений
  void StartReceive(const QString& IP_address, const QString& port_publisher,
                    const QString& head_letter, zmq::context_t* context_inproc);

 signals:
  // Отправка входящего сообщения в главный поток
  void SendResult(const char* result);
};

#endif
