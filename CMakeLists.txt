cmake_minimum_required(VERSION 3.23.0)
project(tiny_serverd)

set(project_root ${CMAKE_CURRENT_SOURCE_DIR})
set(EXECUTABLE_OUTPUT_PATH "${project_root}/bin")

message("---- include all source dir... ----")
include_directories(
  ./
  ./utils
  ./server
)

message("---- find all source files... ----")
aux_source_directory(. SRC_DIR)
list(REMOVE_ITEM SRC_DIR "./client_test_template.cpp")
aux_source_directory(./utils SRC_DIR)
aux_source_directory(./server SRC_DIR)

message("---- create executable bin... ----")
add_executable(${PROJECT_NAME} ${SRC_DIR})