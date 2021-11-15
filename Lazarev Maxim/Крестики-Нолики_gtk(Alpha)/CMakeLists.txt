cmake_minimum_required(VERSION 3.20)
project(XO_gtk_edition)

find_package (PkgConfig REQUIRED)
pkg_check_modules (GTK3 REQUIRED gtk+-3.0)

include_directories (${GTK3_INCLUDE_DIRS})
link_directories (${GTK3_LIBRARY_DIRS})

add_library(XOHeader XOHeader.cpp)
add_library(BotIO BotIO.cpp)
add_library(gtk_lm gtk_lm.cpp)
add_library(gui gui.cpp)
add_executable(XO_gtk_edition main.cpp)

add_definitions (${GTK3_CFLAGS_OTHER})

target_link_libraries(gui  gtk_lm  XOHeader BotIO)
target_link_libraries(BotIO XOHeader )
target_link_libraries(gtk_lm ${GTK3_LIBRARIES})
target_link_libraries (XO_gtk_edition ${GTK3_LIBRARIES} XOHeader  BotIO gtk_lm gui)



set(CMAKE_CXX_STANDARD 14)