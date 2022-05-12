#include<iostream>
#include "graph.h"
#include <ctime>
#include <vector>

void bfs_search_time(int sum_of_edges_and_vertices) {
    Graph a(sum_of_edges_and_vertices, RANDOM);
    a.get_adjacency_matrix();
    a.print_adjacency_matrix();
    int start = clock();
    a.bfs_search();
    int end = clock();
    std::cout << "sum of edges and vertices: " << a.get_number_of_edges() + a.get_number_of_vertices() << ", milliseconds: ";
    std::cout << (end - start) * 1000 / CLOCKS_PER_SEC << std::endl;
}

void dfs_search_time(int sum_of_edges_and_vertices) {
    Graph a(sum_of_edges_and_vertices, RANDOM);
    a.get_adjacency_matrix();
    a.print_adjacency_matrix();
    int start = clock();
    a.dfs_search();
    int end = clock();
    std::cout << "sum of edges and vertices: " << a.get_number_of_edges() + a.get_number_of_vertices() << ", milliseconds: ";
    std::cout << (end - start) * 1000 / CLOCKS_PER_SEC << std::endl;
}

int main() {
    ////тест BFS
    //std::cout << "BFS tests...\n";
    bfs_search_time(500);
    //bfs_search_time(2000000);
    //bfs_search_time(3000000);
    //bfs_search_time(4000000);
    //bfs_search_time(5000000);
    //bfs_search_time(6000000);
    //bfs_search_time(7000000);
    //bfs_search_time(8000000);
    //bfs_search_time(9000000);
    //bfs_search_time(10000000);

    ////тест DFS
    //std::cout << "\nDFS tests...\n";
    dfs_search_time(500);
    //dfs_search_time(2000000);
    //dfs_search_time(3000000);
    //dfs_search_time(4000000);
    //dfs_search_time(5000000);
    //dfs_search_time(6000000);
    //dfs_search_time(7000000);
    //dfs_search_time(8000000);
    //dfs_search_time(9000000);
    //dfs_search_time(10000000);


    //тест отдельных графов

    //std::vector<std::vector<int>> a_list_1 = { {1,2,3,6},
    //                                         {5,8},
    //                                         {9,10,14},
    //                                         {14,17},
    //                                         {11,16,19},
    //                                         {0,3},
    //                                         {0,14},
    //                                         {0,2,8},
    //                                         {},
    //                                         {11},
    //                                         {7},
    //                                         {12,16,19},
    //                                         {9},
    //                                         {2,11},
    //                                         {4,13},
    //                                         {19},
    //                                         {},
    //                                         {18},
    //                                         {4,14,15},
    //                                         {12} };

    //Graph aa(a_list_1);
    //aa.print_adjacency_list();
    //aa.get_adjacency_matrix();
    //aa.print_adjacency_matrix();
    //aa.find_path(0, 12);
    //aa.print_vector(aa.topological_sort());

    //Graph a(10);
    //a.print_adjacency_list();

    //std::vector<std::vector<int>> a_list_2 = { {2},
    //                                       {0,4,6},
    //                                       {5,7},
    //                                       {1,6},
    //                                       {2},
    //                                       {},
    //                                       {4,8},
    //                                       {5},
    //                                       {4,7} };
    //Graph a(a_list_2);
    //a.print_vector(a.topological_sort());
    //a.find_path(0, 3);

    return 0;
}