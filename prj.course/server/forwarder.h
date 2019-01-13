#ifndef FORWARDER_H
#define FORWARDER_H

#include <QObject>
#include <QString>
#include <QThread>
#include <zmq.hpp>

// Класс для приёма заявок от программ-клиентов на подключение к чату
// и пересылки сообщений от одного клиента всем остальным
class Forwarder: public QObject {
  Q_OBJECT

 public:
  Forwarder() {}
  ~Forwarder();

 public slots:
  // Получение данных из главного потока и начало приёма заявок на подключение
  // и пересылки сообщений
  void StartForward(const QString& IP_address, const QString& name_chat,
                    zmq::context_t* context_inproc);

 signals:
  // Передача данных в побочный поток и начало рассылки сообщений с целью
  // нахождения сервера клиентами
  void StartBlink(const QString& IP_address, const QString& port_reply,
                  const QString& name_chat, zmq::context_t* context_inproc);

 private:
  // Поток для широковещания
  QThread thread_;
  // Контекст для создания сокетов
  zmq::context_t context_inproc_{ 0 };
  // Сокет для остановки работы побочного потока
  zmq::socket_t stop_blink_{ context_inproc_, ZMQ_DEALER };
};

#endif
