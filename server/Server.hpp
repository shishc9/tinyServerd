#ifndef TINY_SERVER_H
#define TINY_SERVER_H

#include <string>

class Server {
public:
  Server();
  Server(std::string, const int port = 9090);

  int Start();
private:
  std::string server_ip;
  int         server_port;
};

#endif