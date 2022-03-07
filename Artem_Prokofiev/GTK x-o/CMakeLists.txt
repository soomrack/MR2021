cmake_minimum_required (VERSION 3.20.2)
project (gtk-test)

find_package (PkgConfig REQUIRED)
pkg_check_modules (GTK3 REQUIRED gtk+-3.0)

include_directories (${GTK3_INCLUDE_DIRS})
link_directories (${GTK3_LIBRARY_DIRS})
add_executable (gtk-test main.c)
add_definitions (${GTK3_CFLAGS_OTHER})
target_link_libraries (gtk-test ${GTK3_LIBRARIES})