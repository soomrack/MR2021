cmake_minimum_required(VERSION 3.20)
project(untitled24)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled24 main.cpp)
add_library(library library.cpp)
target_link_libraries(untitled24 library)