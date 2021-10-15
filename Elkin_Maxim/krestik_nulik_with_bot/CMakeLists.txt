cmake_minimum_required(VERSION 3.20)
project(XObot C)

set(CMAKE_C_STANDARD 99)

add_library(BotXO BotXO.c)

add_executable(XObot main.c BotXO.h)

target_link_libraries(XObot PUBLIC BotXO)


