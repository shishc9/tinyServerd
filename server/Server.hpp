#ifndef TINY_SERVER_H
#define TINY_SERVER_H

#include <string>
#include "../http/HttpRequest.hpp"

class Server {
public:
  Server();
  Server(const std::string, const int port = 9090);

  int get_ready() const { return this->is_ready; }
  std::string get_server_ip() const { return this->server_ip; }
  int get_server_port() const { return this->server_port; }
  int get_fd() const { return this->fd; }
  void set_fd(int p_fd) { this->fd = p_fd;}

  int start();

private:
  int bind_and_listen();
  int server_loop();
  void set_signal_handler();
  HttpRequest parse_http_request(int);

private:
  std::string server_ip;
  int         server_port;
  bool        is_ready;
  int         fd;
};

#endif