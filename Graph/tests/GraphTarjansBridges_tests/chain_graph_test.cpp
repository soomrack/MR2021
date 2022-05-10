#include "../../graph.h"
#include <iostream>

int main() {

    GraphTarjansBridges<int> graph(3);
    graph.add_edge(0, 1);
    graph.add_edge(1, 2);

    auto bridges = graph.tarjans_find_bridges();

    if (bridges.size() == 2) {
        std::cout << "Graph correctly has 2 bridges" << std::endl;
        return 0;
    }

    std::cout << "Error with empty graph" << std::endl;
    return 1;
}

