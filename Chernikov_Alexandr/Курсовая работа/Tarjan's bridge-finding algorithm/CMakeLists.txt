cmake_minimum_required(VERSION 3.20)
project(Tarjan_s_bridge_finding_algorithm)

set(CMAKE_CXX_STANDARD 14)

find_package (GTest REQUIRED)

include_directories (${GTest_INCLUDE_DIRS})
link_directories (${GTest_LIBRARY_DIRS})

add_executable (Tarjan_s_bridge_finding_algorithm main.cpp graph.cpp)

add_definitions (${GTest_CFLAGS_OTHER})
target_link_libraries (Tarjan_s_bridge_finding_algorithm ${GTest_LIBRARIES})

