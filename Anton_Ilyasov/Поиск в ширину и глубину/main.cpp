#include<iostream>
#include "graph.h"
#include <queue> // очередь
#include <stack> // стек
#include <ctime>

void bfs_search_time(int numVertices) {
    Graph a(numVertices, "rand");

    int start = clock();
    a.bfs_search();
    int end = clock();
    std::cout << "elements: " << numVertices << ", milliseconds: ";
    std::cout << (end - start) * 1000 / CLOCKS_PER_SEC << std::endl;
}

void dfs_search_time(int numVertices) {
    Graph a(numVertices, "rand");

    int start = clock();
    a.dfs_search();
    int end = clock();
    std::cout << "elements: " << numVertices << ", milliseconds: ";
    std::cout << (end - start) * 1000 / CLOCKS_PER_SEC << std::endl;
}

int main() {
    //тест BFS
    std::cout << "BFS tests...\n ";
    bfs_search_time(1);
    bfs_search_time(10);
    bfs_search_time(100);
    bfs_search_time(500);
    bfs_search_time(1000);
    bfs_search_time(3000);
    bfs_search_time(5000);
    bfs_search_time(8000);
    bfs_search_time(10000);

    //тест DFS
    std::cout << "\nDFS tests...\n ";
    dfs_search_time(1);
    dfs_search_time(10);
    dfs_search_time(100);
    dfs_search_time(500);
    dfs_search_time(1000);
    dfs_search_time(3000);
    dfs_search_time(5000);
    dfs_search_time(8000);
    dfs_search_time(10000);

    return 0;
}