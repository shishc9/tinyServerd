#ifndef CONST_HPP
#define CONST_HPP

class Const {
public:
  static const int BUFFER_SIZE = 4096;

};

enum class HttpMethod {
  HEAD, GET, POST, PUT, PATCH, DELETE, UNKNOWN
};

#endif