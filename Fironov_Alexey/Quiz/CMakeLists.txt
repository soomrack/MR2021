cmake_minimum_required(VERSION 3.20)
project(Quiz)

set(CMAKE_CXX_STANDARD 14)

add_executable(Quiz main.cpp team.cpp team.h question.cpp question.h)
