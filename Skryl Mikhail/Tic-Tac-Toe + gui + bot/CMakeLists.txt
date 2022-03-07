cmake_minimum_required(VERSION 3.20)
project(untitled85 C)

find_package (PkgConfig REQUIRED)
pkg_check_modules (GTK2 REQUIRED gtk+-3.0)

set(CMAKE_C_STANDARD 99)

include_directories (${GTK2_INCLUDE_DIRS})
link_directories (${GTK2_LIBRARY_DIRS})

add_library(Bot Bot.c)
add_executable (untitled85 main.c)
add_definitions (${GTK2_CFLAGS_OTHER})
target_link_libraries (untitled85 ${GTK2_LIBRARIES})
target_link_libraries(untitled85 Bot)
