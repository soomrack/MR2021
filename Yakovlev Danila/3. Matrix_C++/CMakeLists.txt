cmake_minimum_required(VERSION 3.20)
project(3__Matrix_C__)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(3__Matrix_C__
        library.cpp
        library.h
        main.cpp)
