#pragma comment(linker, "/HEAP:400000000")
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
    std::cout << "BFS tests...\n ";
    bfs_search_time(10000);
    bfs_search_time(20000);
    bfs_search_time(30000);
    bfs_search_time(40000);
    bfs_search_time(50000);

    ////тест DFS
    std::cout << "\nDFS tests...\n ";
    dfs_search_time(10000);
    dfs_search_time(20000);
    dfs_search_time(30000);
    dfs_search_time(40000);
    dfs_search_time(50000);

    //тест отдельных графов
    bool a[6][6] = { 0,1,1,0,0,0,
        1,0,0,1,1,0,
        1,0,0,0,0,0,
        0,1,0,0,0,0,
        0,1,0,0,0,1,
        0,0,0,0,1,0 };

    Graph aa(6, *a);
    aa.bfs_search();
    aa.dfs_search();

    bool b[5][5] = { 0,0,1,1,0,
        0,0,1,0,0,
        1,1,0,0,1,
        1,0,0,0,1,
        0,0,1,1,0 };

    Graph bb(5, *b);
    bb.bfs_search();
    bb.dfs_search();

    return 0;
}




