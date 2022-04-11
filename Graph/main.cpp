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

void test_dijkstra() {
    std::vector<std::vector<int>> grid = {{0, 3,  88, 7},
                                          {8, 0,  2,  22},
                                          {5, 99, 0,  1},
                                          {2, 49, 54, 0}};
    Graph<int> dij(grid);
    std::vector<std::vector<int>> ans1 = dij.dijkstra();

    for (int i = 0; i < ans1.size(); i++) {
        for (int j = 0; j < ans1.size(); j++) {
            std::cout << ans1[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void test_floyd_warshall_ways() {
    std::vector<std::vector<int>> grid = {{0, 3,  88, 7},
                                          {8, 0,  2,  22},
                                          {5, 99, 0,  1},
                                          {2, 49, 54, 0}};
    Graph<int> fw(grid);
    std::vector<std::vector<int>> ans2;
    std::vector<std::vector<int>> ans3;
    std::tie(ans2, ans3) = fw.floyd_warshall_ways();
    fw.restore_path(2, 4);

    for(int i = 0; i < ans2.size(); i++) {
        for (int j = 0; j < ans2.size(); j++) {
            std::cout << ans2[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void test_bfs_search_to_find_min_path() {
    std::vector<std::vector<int>> grid = { {0,0,0,1,1},
                                           {0,0,1,1,0},
                                           {0,1,0,0,1},
                                           {1,1,0,0,0},
                                           {1,0,0,0,0} };
    Graph<int> grid_1(grid);
    grid_1.bfs_search_to_find_min_path(4, 1);
}

void test_dfs_search_for_topological_sort() {
    std::vector<std::vector<int>> grid = { {0,0,0,0,0,0},
                                           {0,0,0,0,0,0},
                                           {0,0,0,1,0,0},
                                           {0,1,0,0,0,0},
                                           {1,1,0,0,0,0},
                                           {1,0,1,0,0,0} };
    Graph<int> grid_1(grid);
    grid_1.dfs_search_for_topological_sort();
}

// Просьба организовывать свои тесты методов в функции, чтобы не сильно нагружать функцию main
int main() {
    test_tarjan_s_find_bridges();
    test_dijkstra();
    test_floyd_warshall_ways();
    test_bfs_search_to_find_min_path();
    test_dfs_search_for_topological_sort();
    return 0;
}
