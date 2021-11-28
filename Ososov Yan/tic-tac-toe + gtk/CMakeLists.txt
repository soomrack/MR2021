cmake_minimum_required (VERSION 2.4)
project (untitled18)

find_package (PkgConfig REQUIRED)
pkg_check_modules (GTK2 REQUIRED gtk+-3.0)

include_directories (${GTK2_INCLUDE_DIRS})
link_directories (${GTK2_LIBRARY_DIRS})
add_executable (untitled18 main.c)
add_definitions (${GTK2_CFLAGS_OTHER})
target_link_libraries (untitled18 ${GTK2_LIBRARIES})
add_library(Bot Bot.c)
target_link_libraries(untitled18 Bot)