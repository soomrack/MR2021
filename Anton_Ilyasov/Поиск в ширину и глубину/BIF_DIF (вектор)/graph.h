#ifndef BIF_AND_DIF_H
#define BIF_AND_DIF_H
#include <vector>

typedef enum {
    ZERO, RANDOM
} GraphType;

class Graph { //граф, представленный матрицей смежности
private:
    std::vector<std::vector<int>> adjMatrix;
    int64_t numVertices;
public:
    Graph();
    Graph(int64_t numVertices, std::vector<std::vector<int>>& other_matrix);
    Graph(int64_t numVertices, GraphType type);
public:
    void addEdge(int64_t i, int64_t j);
    void removeEdge(int64_t i, int64_t j);
    bool isEdge(int64_t i, int64_t j);
    void toString();
public:
    void bfs_search();
    void dfs_search();
};

#endif
