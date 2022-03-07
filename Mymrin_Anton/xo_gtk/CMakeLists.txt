cmake_minimum_required (VERSION 2.4)
project (xo_gtk)

find_package (PkgConfig REQUIRED)
pkg_check_modules (GTK REQUIRED gtk+-3.0)

include_directories (${GTK_INCLUDE_DIRS})
link_directories (${GTK_LIBRARY_DIRS})
add_executable (xo_gtk main.c)
add_definitions (${GTK_CFLAGS_OTHER})
target_link_libraries (xo_gtk ${GTK_LIBRARIES})
