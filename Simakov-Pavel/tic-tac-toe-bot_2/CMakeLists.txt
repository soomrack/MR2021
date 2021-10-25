cmake_minimum_required(VERSION 3.20)
project(untitled2 C)

set(CMAKE_C_STANDARD 99)

add_library(library library.c)
add_executable(untitled2 main.c library.h)

target_link_libraries(untitled2 PUBLIC library)
