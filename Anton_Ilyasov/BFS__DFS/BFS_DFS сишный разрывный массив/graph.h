﻿#ifndef BFS_AND_DFS_H
#define BFS_AND_DFS_H
#include <string>
typedef enum {
    ZERO, RANDOM
} GraphType;

class Graph { //граф, представленный матрицей смежности
private:
    int** adjMatrix;
    int64_t numVertices;
public:
    Graph();
    Graph(int64_t numVertices, int* other_matrix);
    Graph(int64_t numVertices, GraphType type);
    ~Graph();
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
