#ifndef BFS_AND_DFS_H
#define BFS_AND_DFS_H
#include <string>
typedef enum {
    ZERO, RANDOM
} GraphType;

class Graph { //граф, представленный матрицей смежности
private:
    int** adjMatrix;
    int* data;
    int numVertices;
public:
    Graph();
    Graph(int numVertices, const int* other_matrix);
    Graph(int numVertices, GraphType type);
    Graph(const Graph& other_matrix);
    Graph(Graph&& other_matrix);
    ~Graph();
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
