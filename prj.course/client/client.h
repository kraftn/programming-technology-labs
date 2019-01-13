#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <QMainWindow>
#include <QString>
#include <QThread>
#include <zmq.hpp>

#include "ui_client.h"

// Класс для описания логики работы клиентской части программы
class Client : public QMainWindow {
  Q_OBJECT

 public:
  Client(QWidget* parent = nullptr);
  ~Client();

 public slots:
  // Загрузка настроек чата из файла
  void DownloadSettings();
  // Поиск и выбор доступных серверов
  void SetSettings();
  // Сохранение настроек чата в файл
  void SaveSettings();
  // Метод для входа в чат
  void EnterChat();
  // Отправление письма остальным участникам чата
  void SendLetter();
  // Метод для выхода из чата
  void LeaveChat();
  // Получение входящих сообщений из побочного потока и вывод их на экран
  void GetResult(const char* result);

 signals:
  // Передача данных в побочный поток и начало приёма входящих сообщений в
  // побочном потоке
  void StartReceive(const QString& IP_address, const QString& port_publisher,
                    const QString& head_letter, zmq::context_t* context_inproc);

 private:
  Ui::MainWindow ui;
  // IP-адрес выбранного сервера
  std::string IP_address_{ "" };
  // Порт сервера, используемый при входе в чат
  std::string port_reply_{ "" };
  // Порт сервера для отправки исходящих сообщений
  std::string port_receiver_{ "" };
  // Имя пользователя
  QString name_{ "" };
  // Название выбранного чата
  std::string name_chat_{ "" };
  // Контекст для создания сокетов
  zmq::context_t context_{ 1 };
  // Сокет для отправки исходящих сообщений
  zmq::socket_t sender_{ context_, ZMQ_DEALER };
  // Сокет, используемый при входе в чат
  zmq::socket_t request_{ context_, ZMQ_REQ };
  // Сокет для остановки получения сообщений в побочном потоке
  zmq::socket_t stop_subscribe{ context_, ZMQ_DEALER };
  // Поток, ожидающий входящих сообщений
  QThread thread_;
};

#endif
