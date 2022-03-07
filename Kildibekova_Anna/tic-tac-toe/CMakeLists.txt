cmake_minimum_required(VERSION 3.20)
project(tic-tac-toe C)

set(CMAKE_C_STANDARD 99)

add_library(Bot tic-tac-toe_bot.c)
add_executable(tic-tac-toe main.c)
target_link_libraries(tic-tac-toe Bot)