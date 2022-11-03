#include "Server.hpp"
#include "../utils/MyUtil.hpp"
#include <iostream>
#include <string>

Server::Server() {
  server_ip = "localhost";
  server_port = 9090;
}

int Server::Start() {
  MyUtil::Echo("hello, this is my serverd");
  return 0;
}

