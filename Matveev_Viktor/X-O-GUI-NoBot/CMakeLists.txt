cmake_minimum_required(VERSION 3.20)
project(GTK_X_O C)

find_package (PkgConfig REQUIRED)
pkg_check_modules (GTK3 REQUIRED gtk+-3.0)

set(CMAKE_C_STANDARD 99)

include_directories (${GTK3_INCLUDE_DIRS})
link_directories (${GTK3_LIBRARY_DIRS})

add_library(Bot_Strategy Bot_Strategy.c)
add_executable(GTK_X_O main.c Bot_Strategy.h)
add_definitions (${GTK3_CFLAGS_OTHER})
target_link_libraries (GTK_X_O ${GTK3_LIBRARIES})
target_link_libraries(GTK_X_O Bot_Strategy)