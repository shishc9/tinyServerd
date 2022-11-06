/* 
  一个客户端测试文件，不参与编译
  compile: g++ client_test_template.cpp
  run:     ./a.out
 */
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main() {
  const std::string server_ip = "127.0.0.1";
  const int server_port = 9090;
  int fd = 0;
  struct sockaddr_in server_addr;

  if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("socket");
    exit(-1);
  }

  bzero(&server_addr, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr(server_ip.c_str());
  server_addr.sin_port = htons(server_port);

  if (connect(fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
    perror("connect");
    exit(-1);
  }

  const std::string msg = "hello, server";
  send(fd, msg.c_str(), sizeof(msg), 0);

  close(fd);
  return 0;
}