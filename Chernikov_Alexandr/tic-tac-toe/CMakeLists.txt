cmake_minimum_required(VERSION 3.20)
project(tic_tac_toe C)

set(CMAKE_C_STANDARD 99)

add_library(game_logic game_logic.c)
add_library(bot bot.c)

add_executable(tic_tac_toe main.c game_logic.h bot.h)

target_link_libraries(tic_tac_toe PUBLIC game_logic)
target_link_libraries(tic_tac_toe PUBLIC bot)
