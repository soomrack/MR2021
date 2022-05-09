#ifndef BFS_AND_DFS_H
#define BFS_AND_DFS_H
#include <vector>
#include <list>

typedef enum {
    RANDOM
} GraphType;

class Graph {
private:
    std::vector<std::list<int>> adjacency_list; //Список смежности
    int num_of_vertices;
public:
    Graph();
    Graph(int num_of_vertices);
    Graph(std::vector<std::list<int>>& other_list);
    Graph(int sum_of_edges_and_vertices, GraphType type);
    Graph(const Graph& other_list);
    Graph(Graph&& other_list);
public:
    void add_reverse_edge(int from, int to);
    void add_edge(int from, int to);
    void remove_edge(int from, int to);
    void remove_reverse_edge(int from, int to);
    bool is_edge(int from, int to);
    int get_number_of_vertices();
    int get_number_of_edges();
    void print();
public:
    void bfs_search();
    void dfs_search();
};

#endif