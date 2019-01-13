#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include <QMainWindow>
#include <QString>
#include <QThread>
#include <zmq.hpp>

#include "ui_server.h"

// Класс для описания логики работы серверной части программы
class Server : public QMainWindow {
  Q_OBJECT

 public:
  Server(QWidget* parent = nullptr);
  ~Server();

 public slots:
  // Запуск сервера
  void Start();
  // Остановка сервера
  void Stop();
  // Обновление списка IP-адресов работающих интерфейсов
  void Update();

 signals:
  // Отправка данных в побочный поток для приёма заявок от программ-клиентов на
  // подключение к чату и пересылки сообщений от одного клиента всем остальным
  void StartForward(const QString& IP_address, const QString& name_chat,
                    zmq::context_t* context_inproc);

 private:
  Ui::MainWindow ui;
  // Список IP-адресов работающих интерфейсов
  std::vector<QString> IP_addresses_;
  // Поток для для приёма заявок от программ-клиентов на подключение к чату
  // и пересылки сообщений от одного клиента всем остальным
  QThread thread_;
  // Контекст для создания сокетов
  zmq::context_t context_inproc_{ 0 };
  // Сокет для остановки работы побочного потока
  zmq::socket_t stop_forward_{ context_inproc_, ZMQ_DEALER };
};

#endif
