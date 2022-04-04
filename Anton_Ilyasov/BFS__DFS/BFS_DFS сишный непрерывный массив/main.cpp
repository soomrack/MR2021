#include<iostream>
#include "graph.h"
#include <ctime>


void bfs_search_time(int64_t numVertices) {
    Graph a(numVertices, RANDOM);
    int start = clock();
    a.bfs_search();
    int end = clock();
    std::cout << "elements: " << numVertices << ", milliseconds: ";
    std::cout << (end - start) * 1000 / CLOCKS_PER_SEC << std::endl;
}

void dfs_search_time(int64_t numVertices) {
    Graph a(numVertices, RANDOM);
    int start = clock();
    a.dfs_search();
    int end = clock();
    std::cout << "elements: " << numVertices << ", milliseconds: ";
    std::cout << (end - start) * 1000 / CLOCKS_PER_SEC << std::endl;
}

int main() {
    //тест BFS
    std::cout << "BFS tests...\n";
    bfs_search_time(1000);
    bfs_search_time(2500);
    bfs_search_time(5000);
    bfs_search_time(7500);
    bfs_search_time(10000);
    bfs_search_time(15000);

    //тест DFS
    std::cout << "\nDFS tests...\n ";
    dfs_search_time(1000);
    dfs_search_time(2500);
    dfs_search_time(5000);
    dfs_search_time(7500);
    dfs_search_time(10000);
    dfs_search_time(15000);

    ////тест отдельных графов
    //int a[6][6] = { 0,1,1,0,0,0,
    //                1,0,0,1,1,0,
    //                1,0,0,0,0,0,
    //                0,1,0,0,0,0,
    //                0,1,0,0,0,1,
    //                0,0,0,0,1,0 };

    //Graph aa(6, *a);
    //aa.bfs_search();
    //aa.dfs_search();


    return 0;
}