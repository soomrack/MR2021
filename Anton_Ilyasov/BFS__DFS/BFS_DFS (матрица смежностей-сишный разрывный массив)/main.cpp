#include<iostream>
#include "graph.h"
#include <ctime>


void bfs_search_time(int sum_of_edges_and_vertices) {
    Graph a(sum_of_edges_and_vertices, RANDOM);
    int start = clock();
    a.bfs_search();
    int end = clock();
    std::cout << "sum of edges and vertices: " << a.get_number_of_edges() + a.get_number_of_vertices() << ", milliseconds: ";
    std::cout << (end - start) * 1000 / CLOCKS_PER_SEC << std::endl;
}

void dfs_search_time(int sum_of_edges_and_vertices) {
    Graph a(sum_of_edges_and_vertices, RANDOM);
    int start = clock();
    a.dfs_search();
    int end = clock();
    std::cout << "sum of edges and vertices: " << a.get_number_of_edges() + a.get_number_of_vertices() << ", milliseconds: ";
    std::cout << (end - start) * 1000 / CLOCKS_PER_SEC << std::endl;
}

int main() {
    //тест BFS
    std::cout << "BFS tests...\n";
    bfs_search_time(1000000);
    bfs_search_time(2000000);
    bfs_search_time(3000000);
    bfs_search_time(4000000);
    bfs_search_time(5000000);
    bfs_search_time(6000000);
    bfs_search_time(7000000);
    bfs_search_time(8000000);
    bfs_search_time(9000000);
    bfs_search_time(10000000);

    //ест DFS
    std::cout << "\nDFS tests...\n";
    dfs_search_time(1000000);
    dfs_search_time(2000000);
    dfs_search_time(3000000);
    dfs_search_time(4000000);
    dfs_search_time(5000000);
    dfs_search_time(6000000);
    dfs_search_time(7000000);
    dfs_search_time(8000000);
    dfs_search_time(9000000);
    dfs_search_time(10000000);

    //тест отдельных графов
    //int a[6][6] = { 0,1,1,0,0,0,
    //                1,0,0,1,1,0,
    //                1,0,0,0,0,0,
    //                0,1,0,0,0,0,
    //                0,1,0,0,0,1,
    //                0,0,0,0,1,0 };

    //Graph aa(6, a);
    //aa.print();
    //aa.bfs_search();
    //aa.dfs_search();

    return 0;
}