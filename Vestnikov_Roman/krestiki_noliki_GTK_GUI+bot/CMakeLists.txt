cmake_minimum_required (VERSION 2.4)
project (gtk-test)

find_package (PkgConfig REQUIRED)
pkg_check_modules (GTK2 REQUIRED gtk+-3.0)

include_directories (${GTK2_INCLUDE_DIRS})
link_directories (${GTK2_LIBRARY_DIRS})
add_executable (gtk-test main.c check_library.c bot.c types.h)
add_definitions (${GTK2_CFLAGS_OTHER})
target_link_libraries (gtk-test ${GTK2_LIBRARIES})