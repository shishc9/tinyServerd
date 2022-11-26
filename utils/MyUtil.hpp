#ifndef MY_UTIL_H
#define MY_UTIL_H

#include <string>

class MyUtil {
public:
  static void Echo(const std::string&);
  static void trim_end(std::string&);
  static std::string uri_decode(const std::string& uri);
};

#endif