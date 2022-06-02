cmake_minimum_required(VERSION 3.20)
project(dijkstra)

set(CMAKE_CXX_STANDARD 14)

add_executable(dijkstra main.cpp graph.h graph.cpp)
