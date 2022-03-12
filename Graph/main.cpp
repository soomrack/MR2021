#include <iostream>
#include "graph.h"
#include <tuple>

int main() {
    Graph<int> g1(5);
    g1.add_edge(1, 0);
    g1.add_edge(0, 2);
    g1.add_edge(2, 1);
    g1.add_edge(0, 3);
    g1.add_edge(3, 4);
    g1.tarjans_find_bridges();
    std::cout << "Hello, World!" << std::endl;

    std::vector<int> grid = {0,3,88,7,
                             8,0,2,22,
                             5,99,0,1,
                             2,49,54,0};
    Graph dij(grid);
    dij.Dijkstra();

    Graph fw(grid);
    fw.Floyd_Warshall_ways();
    fw.restore_path(2, 4);
    return 0;
}
