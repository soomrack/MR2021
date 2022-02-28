#ifndef TARJAN_S_BRIDGE_FINDING_ALGORITHM_GRAPH_H
#define TARJAN_S_BRIDGE_FINDING_ALGORITHM_GRAPH_H

#include <vector>

// A class that represents an undirected graph
class Graph{
private:
    int num_of_vertices;
    std::vector<std::list<int>> adj; // adjacency vector
private:
    int time;
public:
    Graph();
    explicit Graph(int num_of_vertices);
    explicit Graph(std::vector<std::list<int>> &adj);
    void add_edge(int v, int w);
    int get_number_of_edges();
    int get_number_of_vertices() const;
    bool edge_is_in_graph(int v, int w);
    void find_bridges();
private:
    void bridge_dfs(int u,
                    std::vector<bool> &visited,
                    std::vector<int> &disc,
                    std::vector<int> &low,
                    std::vector<int> &parent,
                    std::vector<std::pair<int, int>> &bridges);
};

Graph create_random_graph(int sum_of_edges_and_vertices);

#endif
