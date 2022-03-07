#include <iostream>
#include "graph.h"

int main() {

    Graph<int> g1(5);
    g1.add_edge(1, 0);
    g1.add_edge(0, 2);
    g1.add_edge(2, 1);
    g1.add_edge(0, 3);
    g1.add_edge(3, 4);
    g1.tarjans_find_bridges();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
