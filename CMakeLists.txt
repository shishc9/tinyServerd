cmake_minimum_required(VERSION 3.23.0)
project(tiny_serverd)

set(project_root ${CMAKE_CURRENT_SOURCE_DIR})
set(EXECUTABLE_OUTPUT_PATH "${project_root}/bin")
# 指定c++编译版本为C++11
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)

message("---- include all source dir... ----")
include_directories(
  ./
  ./utils
  ./server
  ./http
  ./common
)

message("---- find all source files... ----")
aux_source_directory(. SRC_DIR)
# client_test_template.cpp 编译时候不关注
list(REMOVE_ITEM SRC_DIR "./client_test_template.cpp")
# 包含其他的源文件
aux_source_directory(./utils SRC_DIR)
aux_source_directory(./server SRC_DIR)
aux_source_directory(./http SRC_DIR)
aux_source_directory(./common SRC_DIR)

message("---- create executable bin... ----")
add_executable(${PROJECT_NAME} ${SRC_DIR})