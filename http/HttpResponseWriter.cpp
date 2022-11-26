#include "HttpResponseWriter.hpp"
#include "../utils/HttpUtil.hpp"
#include "../utils/MyUtil.hpp"
#include <unistd.h>
#include <sys/socket.h>

HttpResponseWriter::HttpResponseWriter() {
  write_enable = false;
  closed = false;
}

HttpResponseWriter::HttpResponseWriter(int p_fd) {
  HttpResponseWriter();
  fd = p_fd;
}

int HttpResponseWriter::write_msg() {
  if (!write_enable) {
    MyUtil::Echo("write_enable is false!");
    exit(1);
  }

  int len = 0;
  std::string msg("success handler\r\n");
  if ((len = write(fd, msg.c_str(), msg.length())) < 0) {
    MyUtil::Echo("server write msg error! exit_");
    exit(1);
  }

  return 0;
}

void HttpResponseWriter::close_connect() {
  if (closed) {
    return ;
  }

  shutdown(fd, 2);
  close(fd);
  write_enable = false;
  closed = true;
}

int HttpResponseWriter::prepare_for_write() {
  if (closed) {
    return -1;
  }

  std::string buffer;
  int len;

  buffer = "HTTP/1.1 " + std::to_string(status_code) + " " +
            HttpUtil::get_http_status_string(status_code) + "\r\n";
  if ((len = write(fd, buffer.c_str(), buffer.length())) < 0) {
    MyUtil::Echo("server write response code error! exit_");
    exit(1);
  }

  for (auto item : headers) {
    buffer = item.first + ": " + item.second + "\r\n";
    if ((len = write(fd, buffer.c_str(), buffer.length())) < 0) {
      MyUtil::Echo("server write response header error! exit_");
      exit(1);
    }
  }

  if ((len = write(fd, "\r\n", 2)) < 0) {
    MyUtil::Echo("server write response foot error! exit_");
    exit(1);
  }

  write_enable = true;
  return 0;
}

