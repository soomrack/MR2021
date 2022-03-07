cmake_minimum_required(VERSION 3.20)
project(Matrix)

set(CMAKE_CXX_STANDARD 14)

add_library(Matrix_liba Matrix_liba.cpp)
add_executable(Matrix main.cpp Matrix_liba.h)

target_link_libraries(Matrix PUBLIC Matrix_liba)