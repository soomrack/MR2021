#ifndef BFS_AND_DFS_H
#define BFS_AND_DFS_H
#include <vector>

typedef enum {
    ZERO, RANDOM
} GraphType;

class Graph { //граф, представленный матрицей смежности
private:
    std::vector<std::vector<int>> adjacency_matrix;
    int num_of_vertices;
    int num_of_edges;
public:
    Graph();
    Graph(int num_of_vertices);
    Graph(std::vector<std::vector<int>>& other_matrix);
    Graph(int sum_of_edges_and_vertices, GraphType type);
    Graph(const Graph& other_matrix);
    Graph(Graph&& other_matrix);
public:
    void addEdge(int from, int to);
    void removeEdge(int from, int to);
    bool isEdge(int from, int to);
    int get_number_of_vertices();
    int get_number_of_edges();
    void print();
public:
    void bfs_search();
    void dfs_search();
};

#endif