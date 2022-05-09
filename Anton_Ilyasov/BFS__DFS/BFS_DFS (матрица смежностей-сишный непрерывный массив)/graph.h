#ifndef BFS_AND_DFS_H
#define BFS_AND_DFS_H
#include <string>
typedef enum {
    ZERO, RANDOM
} GraphType;

class Graph { //граф, представленный матрицей смежности
private:
    int** adjacency_matrix;
    int* data;
    int num_of_vertices;
public:
    Graph();
    Graph(int num_of_vertices);
    Graph(int num_of_vertices, const int* other_matrix);
    Graph(int sum_of_edges_and_vertices, GraphType type);
    Graph(const Graph& other_matrix);
    Graph(Graph&& other_matrix);
    ~Graph();
public:
    void addEdge(int i, int j);
    void removeEdge(int i, int j);
    bool isEdge(int i, int j);
    int get_number_of_vertices();
    int get_number_of_edges();
    void print();
public:
    void bfs_search();
    void dfs_search();
};

#endif
