#ifndef BIF_AND_DIF_H
#define BIF_AND_DIF_H
#include <string>

class Graph { //граф, представленный матрицей смежности
private:
    bool** adjMatrix;
    int numVertices;
public:
    Graph();
    Graph(int numVertices);
    Graph(int numVertices, std::string type);
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