cmake_minimum_required(VERSION 3.20)
project(Graph)

set(CMAKE_CXX_STANDARD 14)
enable_testing()

add_executable(Graph main.cpp graph.cpp)

add_executable(empty_graph_test tests/GraphTarjansBridges_tests/empty_graph_test.cpp graph.cpp)
add_test(EmptyGraphTest empty_graph_test)

add_executable(graph_without_edges_test tests/GraphTarjansBridges_tests/graph_without_edges_test.cpp graph.cpp)
add_test(GraphWithoutEdgesTest graph_without_edges_test)

add_executable(chain_graph_test tests/GraphTarjansBridges_tests/chain_graph_test.cpp graph.cpp)
add_test(ChainGraphTest chain_graph_test)

