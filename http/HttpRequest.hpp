#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include <string>
#include <map>
#include "../common/Const.hpp"

class HttpRequest {
public:

public:
  std::string   content;
  std::string   uri;
  std::string   path;
  std::string   host;
  std::string   query_string;
  HttpMethod    method;
  std::map<std::string, std::string> headers;
};

#endif