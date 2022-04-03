#include <iostream>
#include <tuple>
#include <algorithm>
#include "graph.h"

void test_tarjan_s_find_bridges() {
    Graph<int> g1(6);
    g1.add_edge(1, 0);
    g1.add_edge(0, 2);
    g1.add_edge(2, 1);
    g1.add_edge(0, 3);
    g1.add_edge(3, 4);
    g1.add_edge(4, 5, get_inf<int>());
    auto bridges = g1.tarjans_find_bridges();
    for (auto & bridge : bridges) {
        std::cout << bridge.first << ' ' << bridge.second << '\n';
    }
}

void test_floyd_warshall_ways() {
    std::vector<std::vector<int>> grid = {{0,3,88,7},
                                          {8,0,2,22},
                                          {5,99,0,1},
                                          {2,49,54,0}};
    Graph<int> dij(grid);
    dij.dijkstra();

    Graph<int> fw(grid);
    fw.floyd_warshall_ways();
    fw.restore_path(2, 4);
}

// Просьба организовывать свои тесты методов в функции, чтобы не сильно нагружать функцию main
int main() {

    test_tarjan_s_find_bridges();
    test_floyd_warshall_ways();

    return 0;
}
