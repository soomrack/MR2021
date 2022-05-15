cmake_minimum_required(VERSION 3.20)
project(Graph)

set(CMAKE_CXX_STANDARD 14)

enable_testing()

add_library(graphlib graph.cpp)

add_executable(Graph main.cpp)
target_link_libraries(Graph graphlib)

add_executable(vertex_test tests/Vertex_tests.cpp)
target_link_libraries(vertex_test graphlib)
add_test(VertexTest vertex_test)

add_executable(base_graph_test tests/BaseGraph_tests.cpp)
target_link_libraries(base_graph_test graphlib)
add_test(BaseGraphTest base_graph_test)

add_executable(graph_tarjans_bridges_test tests/GraphTarjansBridges_tests.cpp)
target_link_libraries(graph_tarjans_bridges_test graphlib)
add_test(GraphTarjansBridgesTest graph_tarjans_bridges_test)
