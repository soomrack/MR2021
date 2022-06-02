#include <iostream>
#include <chrono>
#include <vector>
#include "graph.h"

void test_dijkstra_log(std::vector<std::vector<int>> grid)
{
    Graph<int> ways(grid);
    int answer = ways.dijkstra_log(1,2);
    std:: cout << answer << "done" << std::endl;
}

std::vector<std::vector<int>> random_graph(int v)
{
    srand(400);
    std::vector<std::vector<int>> graph(v, std::vector <int> (v));
    for (int i = 0; i < v; i++)
    {
        for (int j = 0; j < v; j++)
        {
            graph[i][j] = rand()%100+1;
        }
    }
    return graph;
}

int main()
{
    std::vector<std::vector<int>> grid = random_graph(300);
    std::cout << "im here" << std::endl;
    auto begin = std::chrono::steady_clock::now();
    test_dijkstra_log(grid);
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time: " << elapsed_ms.count() << " ms"  << std::endl;
    return 0;
};
