cmake_minimum_required(VERSION 3.20)
project(Matrica)

set(CMAKE_CXX_STANDARD 14)

add_library(matrix_lib matrix_lib.cpp)
add_executable(Matrica main.cpp matrix_lib.h)

target_link_libraries(Matrica PUBLIC matrix_lib)
