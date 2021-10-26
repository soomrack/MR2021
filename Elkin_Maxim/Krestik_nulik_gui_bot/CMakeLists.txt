cmake_minimum_required(VERSION 3.20)
project(gtk_test C)

find_package (PkgConfig REQUIRED)
pkg_check_modules (GTK3 REQUIRED gtk+-3.0)

set(CMAKE_C_STANDARD 99)

include_directories (${GTK3_INCLUDE_DIRS})
link_directories (${GTK3_LIBRARY_DIRS})

add_library(BotXO BotXO.c)
add_executable(gtk_test main.c BotXO.h)
add_definitions (${GTK3_CFLAGS_OTHER})
target_link_libraries (gtk_test ${GTK3_LIBRARIES})
target_link_libraries(gtk_test BotXO)