cmake_minimum_required(VERSION 3.20)
project(Tic_Tac_Toe C)

set(CMAKE_C_STANDARD 99)

#include_directories(Graphics)
#include_directories(Graphics/include) # Graphics include
#include_directories(Graphics/lib) # Graphics lib

# "Tic_Tac_Toe/Graphics/dll/" for *.dll

add_executable(Tic_Tac_Toe main.c)
