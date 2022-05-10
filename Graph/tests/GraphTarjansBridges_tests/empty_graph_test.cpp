#include "../../graph.h"
#include <iostream>

int main() {

    GraphTarjansBridges<int> graph;
    auto bridges = graph.tarjans_find_bridges();

    if (bridges.empty()) {
        std::cout << "Empty graph correctly has zero bridges" << std::endl;
        return 0;
    }

    std::cout << "Error with empty graph" << std::endl;
    return 1;
}