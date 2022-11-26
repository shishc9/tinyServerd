#ifndef HTTP_UTIL_HPP
#define HTTP_UTIL_HPP

#include <string>
#include "../common/Const.hpp"

class HttpUtil {
public:
  static std::string get_http_method_name(HttpMethod method) {
    switch (method) {
      case HttpMethod::HEAD: return "HEAD";
      case HttpMethod::GET: return "GET";
      case HttpMethod::POST: return "POST";
      case HttpMethod::PUT: return "PUT";
      case HttpMethod::PATCH: return "PATCH";
      case HttpMethod::DELETE: return "DELETE";
      case HttpMethod::UNKNOWN: default: return "UNKNOWN";
    }
  }

  static std::string get_http_status_string(int code) {
    switch (code) {
      case 200: return "ok";
      default: return "unknown";
    }
  }
};

#endif