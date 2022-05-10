#include "../../graph.h"
#include <iostream>

void test_graph(int num_of_vertices) {
    GraphTarjansBridges<int> graph(num_of_vertices);
    auto bridges = graph.tarjans_find_bridges();

    if (!bridges.empty()) {
        std::cout << "Graph with " << num_of_vertices << "vertices ";
        std::cout << "and without edges incorrectly has non-zero bridges" << std::endl;
        exit(1);
    }
}

int main() {

    test_graph(1);
    test_graph(2);
    test_graph(3);
    test_graph(4);
    test_graph(5);

    std::cout << "No error with graph without edges" << std::endl;
}