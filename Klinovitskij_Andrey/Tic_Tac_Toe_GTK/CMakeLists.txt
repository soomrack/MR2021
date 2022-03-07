cmake_minimum_required (VERSION 2.4)
project (Tic_Tac_Toe_GTK)

find_package (PkgConfig REQUIRED)
pkg_check_modules (GTK REQUIRED gtk+-3.0)

include_directories (${GTK_INCLUDE_DIRS})
link_directories (${GTK_LIBRARY_DIRS})
add_executable (Tic_Tac_Toe_GTK main.c)
add_definitions (${GTK_CFLAGS_OTHER})
target_link_libraries (Tic_Tac_Toe_GTK ${GTK_LIBRARIES})