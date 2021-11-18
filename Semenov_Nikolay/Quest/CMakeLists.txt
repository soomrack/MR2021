cmake_minimum_required(VERSION 3.20)
project(Q_Main)

set(CMAKE_CXX_STANDARD 14)

add_executable(Q_Main main.cpp)
add_library(Q_Data Q_Data.cpp)
add_library(Q_API Q_API.cpp)
target_link_libraries(Q_Main Q_Data)
target_link_libraries(Q_Main Q_API)