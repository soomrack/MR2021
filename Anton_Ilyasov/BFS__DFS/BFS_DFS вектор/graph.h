#ifndef BFS_AND_DFS_H
#define BFS_AND_DFS_H
#include <vector>

typedef enum {
    ZERO, RANDOM
} GraphType;

class Graph { //граф, представленный матрицей смежности
private:
    std::vector<std::vector<int>> adjMatrix;
    int numVertices;
public:
    Graph();
    Graph(std::vector<std::vector<int>>& other_matrix);
    Graph(int numVertices, GraphType type);
    Graph(const Graph& other_matrix);
    Graph(Graph&& other_matrix);

public:
    void addEdge(int i, int j);
    void removeEdge(int i, int j);
    bool isEdge(int i, int j);
    void toString();
public:
    void bfs_search();
    void dfs_search();
};

#endif