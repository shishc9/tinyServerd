#include <iostream>
#include <string>
#include "server/Server.hpp"

int main(int argc, char** argv) {

  Server server;
  if (server.start() < 0) {
    return -1;
  }

  return 0;
}