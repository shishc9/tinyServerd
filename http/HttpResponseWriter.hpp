#ifndef HTTP_RESPONSE_WRITER_HPP
#define HTTP_RESPONSE_WRITER_HPP

#include <map>
#include <string>

class HttpResponseWriter {
public:
  HttpResponseWriter();
  HttpResponseWriter(int);

  int get_status_code() const { return status_code; }
  void set_status_code(int code) { status_code = code; }
  int prepare_for_write();
  int write_msg();
  void close_connect();
  
private:
  int                                fd;
  bool                               write_enable, closed;
  int                                status_code;
  std::map<std::string, std::string> headers;
};

#endif