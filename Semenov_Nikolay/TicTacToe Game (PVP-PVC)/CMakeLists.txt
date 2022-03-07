cmake_minimum_required(VERSION 3.20)
project(TicTacToe_PVP-PVC_2)

set(CMAKE_CXX_STANDARD 14)

add_executable(TicTacToe_PVP-PVC_2 main.cpp)
add_library(T-T-T_Algorithm_Lib T-T-T_Algorithm_Lib.cpp)
target_link_libraries(TicTacToe_PVP-PVC_2 T-T-T_Algorithm_Lib)