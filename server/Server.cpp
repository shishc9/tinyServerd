#include "Server.hpp"
#include "../utils/MyUtil.hpp"
#include "../http/HttpRequest.hpp"
#include "../http/HttpRequestParser.hpp"
#include "../http/HttpResponseWriter.hpp"
#include "../http/HttpRequestHandler.hpp"
#include "../common/Const.hpp"
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <cstdlib>
#include <string>
#include <cstring>

Server::Server() {
  server_ip   = "127.0.0.1";
  server_port = 9090;
  is_ready    = true;
}

Server::Server(const std::string host, const int port) {
  Server();
  server_ip = host;
  server_port = port;
}

int Server::bind_and_listen() {
  this->fd = socket(AF_INET, SOCK_STREAM, 0);
  if (this->fd == -1) {
    MyUtil::Echo("create socket fd failed!");
    return -1;
  }

  // set addr reusalbe
  if (setsockopt(this->fd, SOL_SOCKET, SO_REUSEADDR, "1", sizeof(int)) == -1) {
    MyUtil::Echo("set socket failed!");
    return -1;
  }

  struct sockaddr_in socket_in;
  bzero(&socket_in, sizeof(socket_in));
  socket_in.sin_family = AF_INET;
  // 十进制ip形式转为uint32_t
  socket_in.sin_addr.s_addr = inet_addr(this->get_server_ip().c_str());
  // host to network short 将主机序转换到网络序
  socket_in.sin_port = htons(this->get_server_port());

  if (::bind(this->fd, (struct sockaddr*)&socket_in, sizeof(socket_in)) < 0) {
    MyUtil::Echo("bind socket error!");
    return -1;
  }

  if (::listen(this->fd, 4) < 0) {
    MyUtil::Echo("listen error");
    return -1;
  }

  return 0;
}

void Server::set_signal_handler() {
  struct sigaction sa;
  sa.sa_handler = SIG_IGN;
  sa.sa_flags = SA_NOCLDWAIT;
  if (sigaction(SIGCHLD, &sa, NULL) == -1) {
    MyUtil::Echo("sigaction error");
    exit(1);
  }
}

HttpRequest Server::parse_http_request(int fd) {
  char buffer[Const::BUFFER_SIZE];
  int len = 0;
  if ((len = read(fd, buffer, sizeof(buffer))) < 0) {
    MyUtil::Echo("read http request error");
    exit(1);
  }

  std::string stringbuf(buffer);
  HttpRequest request = HttpRequestParser::parse2http(stringbuf);
  return request;
}

int Server::server_loop() {
  struct sockaddr_in client_address;
  socklen_t client_len = sizeof(client_address);
  int conn_fd, child_pid;
  // char buffer[128];

  while (true) {
    conn_fd = accept(this->fd, (struct sockaddr*)&client_address, &client_len);
    if (conn_fd < 0) {
      MyUtil::Echo("accept failed!");
      break;
    }
    // memset(buffer, 0, sizeof(buffer));

    if ((child_pid = fork()) < 0) {
      MyUtil::Echo("fork error");
      break;
    } else if (child_pid == 0) {
      close(fd);
      HttpRequest request = parse_http_request(conn_fd);
      HttpResponseWriter response(conn_fd);
      HttpRequestHandler::handler_request(request, response);
      exit(0);
    } else {
      close(conn_fd);
    }
    // if (recv(conn_fd, buffer, 128, 0) == -1) {
    //   MyUtil::Echo("recv failed!");
    //   break;
    // }

    // MyUtil::Echo("server recv: " + std::string(buffer));
    // close(conn_fd);
  }

  return 0;
}

int Server::start() {
  if (!get_ready()) {
    MyUtil::Echo("server is not ready, so can't start!");
    return -1;
  }

  if (bind_and_listen() < 0) {
    MyUtil::Echo("bind or listen failed...");
    return -1;
  }

  // MyUtil::Echo("hello, this is my serverd");
  this->is_ready = true;
  set_signal_handler();
  server_loop();
  return 0;
}

