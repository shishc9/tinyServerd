#include "../utils/MyUtil.hpp"
#include "HttpRequestParser.hpp"
#include <sstream>
#include <iostream>

HttpMethod HttpRequestParser::parse_method(const std::string& token) {
  if (token == "HEAD") {
    return HttpMethod::HEAD;
  } else if (token == "GET") {
    return HttpMethod::GET;
  } else if (token == "POST") {
    return HttpMethod::POST;
  } else if (token == "PUT") {
    return HttpMethod::PUT;
  } else if (token == "PATCH") {
    return HttpMethod::PATCH;
  } else if (token == "DELETE") {
    return HttpMethod::DELETE;
  } else {
    return HttpMethod::UNKNOWN;
  }
}

void HttpRequestParser::parse_uri(HttpRequest& request, const std::string& token) {
  request.uri = token;

  size_t question_pos = token.find_first_of("?");
  if (question_pos != std::string::npos) {
    request.path = MyUtil::uri_decode(token.substr(0, question_pos));
    request.query_string = token.substr(question_pos + 1);
  } else {
    request.path = MyUtil::uri_decode(token);
    request.query_string = "";
  }
}

void HttpRequestParser::parse_header(HttpRequest& request, const std::string& str) {
  size_t colon_pos = str.find_first_of(":");
  std::string name = str.substr(0, colon_pos);
  std::string value = str.substr(colon_pos + 2);

  if (name == "Host") {
    request.host = value;
  } else {
    request.headers[name] = value;
  }
}

void HttpRequestParser::parse_first_line(HttpRequest& request, const std::string& str) {
  std::stringstream ss(str);
  std::string token;
  int token_no = 0;

  while (getline(ss, token, ' ')) {
    switch (token_no)
    {
    case 0: {
      request.method = parse_method(token);
      break;
    }
    case 1: {
      parse_uri(request, token);
      break;
    }
    default:
      break;
    }

    token_no ++;
  }
}

// GET /get_me?id=1 HTTP/1.1
// User-Agent: curl/7.29.0
// Host: 127.0.0.1:9090
// Accept: */*

// POST /login HTTP/1.1
// User-Agent: curl/7.29.0
// Host: 127.0.0.1:9090
// Accept: */*
// Content-Length: 27
// Content-Type: application/x-www-form-urlencoded

// login=emma＆password=123-XM
HttpRequest HttpRequestParser::parse2http(const std::string& data) {
  std::cout << "parse2http: data => " << data << std::endl;
  HttpRequest request;

  std::stringstream ss(data);
  std::string line;
  int line_no;
  bool in_content = false;

  while(getline(ss, line)) {
    std::cout << "parse2http: line => " << line << std::endl;
    MyUtil::trim_end(line);

    if (!in_content && line.length() == 0) {
      request.content = "";
      in_content = true;
      continue;
    }

    if (line_no == 0) {
      parse_first_line(request, line);
    } else if (in_content) {
      request.content += line;
      request.content += '\n';
    } else {
      parse_header(request, line);
    }

    line_no++;
  }

  if (request.content.length() > 0) {
    request.content.pop_back();
  }

  return request;
}