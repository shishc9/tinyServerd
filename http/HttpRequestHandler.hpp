#ifndef HTTP_REQUEST_HANDLER_HPP
#define HTTP_REQUEST_HANDLER_HPP

#include "HttpRequest.hpp"
#include "HttpResponseWriter.hpp"

class HttpRequestHandler {
public:
  static void handler_request(HttpRequest&, HttpResponseWriter&);
private:
  static bool is_dic_request(const std::string&);
  static void print_log(HttpRequest&, HttpResponseWriter&);
};

#endif