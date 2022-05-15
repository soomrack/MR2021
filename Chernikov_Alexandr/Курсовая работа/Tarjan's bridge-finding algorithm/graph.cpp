#include<iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <cmath>
#include "graph.h"

Graph::Graph() {
    num_of_vertices = 0;
}

Graph::Graph(int num_of_vertices){
    this->num_of_vertices = num_of_vertices;
    adj = std::vector<std::list<int>>(num_of_vertices);
}

Graph::Graph(std::vector<std::list<int>> &adj){
    this->num_of_vertices = (int) adj.size();
    this->adj = adj;
}

Graph::Graph(const Graph &other) {
    num_of_vertices = other.num_of_vertices;
    adj = other.adj;
}

Graph::Graph(Graph &&other) noexcept {
    num_of_vertices = other.num_of_vertices;
    adj = other.adj;
}

void Graph::add_edge(int v, int w){
    adj[v].push_back(w);
    adj[w].push_back(v);
}

int Graph::get_number_of_edges(){
    int num = 0;
    for (auto & it : adj){
        num += it.size();
    }
    return num / 2; // each edge counts twice
}

int Graph::get_number_of_vertices() const{
    return num_of_vertices;
}

bool Graph::edge_is_in_graph(int v, int w){
    if (std::find(adj[v].begin(), adj[v].end(), w) != adj[v].end())
        return true;
    return false;
}

// DFS based function to find all bridges. It uses recursive function tarjan_s_bridge_finding_dfs
std::vector<std::pair<int, int>> Graph::find_bridges()
{
    // Mark all the vertices as not visited
    std::vector<bool> visited(num_of_vertices, false);

    std::vector<int> disc(num_of_vertices);
    std::vector<int> low(num_of_vertices);
    std::vector<int> parent(num_of_vertices, -1);

    std::vector<std::pair<int, int>> bridges;
    time = 0;

    // Call the recursive helper function to find Bridges
    // in DFS tree rooted with vertex 'i'
    for (int i = 0; i < num_of_vertices; i++)
        if (!visited[i])
            tarjan_s_bridge_finding_dfs(i, visited, disc, low, parent, bridges);

    return bridges;
}

// A recursive function that finds bridges using DFS traversal
void Graph::tarjan_s_bridge_finding_dfs(int u,
                                        std::vector<bool> &visited,
                                        std::vector<int> &disc,
                                        std::vector<int> &low,
                                        std::vector<int> &parent,
                                        std::vector<std::pair<int, int>> &bridges) {

    // Mark the current node as visited
    visited[u] = true;

    // Initialize discovery time and low value
    disc[u] = low[u] = ++time;

    // Go through all vertices adjacent to this
    for (auto & v : adj[u]) {

        // If v is not visited yet, then recur for it
        if (!visited[v]) {
            parent[v] = u;
            tarjan_s_bridge_finding_dfs(v, visited, disc, low, parent, bridges);

            // Check if the subtree rooted with v has a
            // connection to one of the ancestors of u
            low[u] = std::min(low[u], low[v]);

            // If the lowest vertex reachable from subtree
            // under v is  below u in DFS tree, then u-v
            // is a find_bridges
            if (low[v] > disc[u]){
                bridges.emplace_back(u, v);
            }
        }
        // Update low value of u for parent function calls.
        else if (v != parent[u])
            low[u]  = std::min(low[u], disc[v]);
    }
}

Graph create_random_graph(int sum_of_edges_and_vertices){

    // number of vertexes when every vertex joins with all others vertexes
    int min_number_of_vertices = (-1 + (int) ceil(sqrt(1 + 8.0 * sum_of_edges_and_vertices))) / 2;

    // number of vertexes when graph is a chain
    int max_number_of_vertexes = sum_of_edges_and_vertices / 2 + 1;

    // number of vertexes is somewhere between max and min values
    int number_of_vertices = min_number_of_vertices + rand() % (max_number_of_vertexes - min_number_of_vertices + 1);

    int number_of_edges = sum_of_edges_and_vertices - number_of_vertices;
    int number_of_added_edges = 0;

    Graph graph(number_of_vertices);
    for (int v = 0; v < number_of_vertices; v++){
        for (int w = 0; w < number_of_vertices; w++){
            if (v != w && rand() % number_of_edges >= number_of_added_edges){
                graph.add_edge(v, w);
                number_of_added_edges++;
            }
            if (number_of_added_edges == number_of_edges){
                return graph;
            }
        }
    }

    if (number_of_added_edges != number_of_edges){
        for (int v = 0; v < number_of_vertices; v++){
            for (int w = 0; w < number_of_vertices; w++){
                if (!graph.edge_is_in_graph(v, w)){
                    graph.add_edge(v, w);
                    number_of_added_edges++;
                }
                if (number_of_added_edges == number_of_edges){
                    return graph;
                }
            }
        }
    }
    return graph;
}

