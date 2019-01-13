#ifndef BEACON_H
#define BEACON_H

#include <QObject>
#include <QString>
#include <zmq.hpp>

// Класс для постоянной отправки сообщений для обнаружения программы-сервера
// программами-клиентами
class Beacon: public QObject {
  Q_OBJECT

 public:
  Beacon() {}
  ~Beacon() {}

 public slots:
  // Получение данных из главного потока и начало рассылки сообщений
  void StartBlink(const QString& IP_address, const QString& port_reply,
                  const QString& name_chat, zmq::context_t* context_inproc);
};

#endif
