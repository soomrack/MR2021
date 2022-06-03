#ifndef KAHN_S_TOPOLOGICAL_SORTING_GRAPH_H
#define KAHN_S_TOPOLOGICAL_SORTING_GRAPH_H
#include <vector>

typedef enum {
    RANDOM_DAG
} Type;

class Graph {
private:
    std::vector<std::vector<int>> adjList;
    int sumVertices;
    int sumEdges;
public:
    Graph();
    Graph(int sumVertices);
    Graph(std::vector<std::vector<int>>& other_list);
    Graph(int sumEV, Type type);
    Graph(const Graph& other_list);
    Graph(Graph&& other_list);
public:
    int get_SumVertices();
    int get_sumEdges();
    int get_adjList();
    void print_adjList();
    void print_path(std::vector<int> path);
public:
    std::vector<int> doTopologicalSort();
};

#endif