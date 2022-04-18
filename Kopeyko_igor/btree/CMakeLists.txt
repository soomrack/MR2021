cmake_minimum_required(VERSION 3.20)
project(btree)

set(CMAKE_CXX_STANDARD 14)

add_executable(btree main.cpp b_tree.cpp b_tree.h)
