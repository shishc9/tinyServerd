#include "HttpRequestHandler.hpp"
#include "../utils/HttpUtil.hpp"
#include <iostream>

void HttpRequestHandler::handler_request(HttpRequest& request, HttpResponseWriter& response) {
  response.set_status_code(200);
  response.prepare_for_write();
  response.write_msg();
  print_log(request, response);
}

void HttpRequestHandler::print_log(HttpRequest& request, HttpResponseWriter& response) {
  std::cout << HttpUtil::get_http_method_name(request.method) << " " << request.uri << " ";
  std::cout << response.get_status_code() << " " << HttpUtil::get_http_status_string(response.get_status_code()) << std::endl;
}

