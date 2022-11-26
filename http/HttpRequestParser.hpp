#ifndef HTTP_REQUEST_PARSER_HPP
#define HTTP_REQUEST_PARSER_HPP

#include <string>
#include "HttpRequest.hpp"
#include "../common/Const.hpp"

class HttpRequestParser {
public:
  static HttpRequest parse2http(const std::string& data);
private:
  static void parse_first_line(HttpRequest&, const std::string&);
  static void parse_uri(HttpRequest&, const std::string&);
  static void parse_header(HttpRequest&, const std::string&);
  static HttpMethod parse_method(const std::string&);
};

#endif