#include<iostream>
#include <vector>
#include <algorithm>
#include <cstdint>
#include "graph.h"

#define INF std::numeric_limits<T>::max()

template <typename T>
Graph<T>::Graph() = default;

template <typename T>
Graph<T>::Graph(int num_of_vertices){
    for (int i = 0; i < num_of_vertices; i++) {
        std::vector<T> row(num_of_vertices, INF);
        row[i] = 0;
        adjacency_matrix.push_back(row);
    }
}

template <typename T>
Graph<T>::Graph(std::vector<std::vector<T>> &adjacency_matrix){
    this->adjacency_matrix = adjacency_matrix;
}

template <typename T>
Graph<T>::Graph(const Graph &other) {
    adjacency_matrix = other.adjacency_matrix;
}

template <typename T>
Graph<T>::Graph(Graph &&other) noexcept {
    adjacency_matrix = other.adjacency_matrix;
}

template <typename T>
void Graph<T>::add_edge(int u, int v, int weight){
    adjacency_matrix[u][v] = weight;
    adjacency_matrix[v][u] = weight;
}


// DFS based function to find all bridges. It uses recursive function tarjan_s_bridge_finding_dfs
template <typename T>
std::vector<std::pair<int, int>> Graph<T>::tarjans_find_bridges()
{
    int num_of_vertices = adjacency_matrix.size();
    // Mark all the vertices as not visited
    std::vector<bool> visited(num_of_vertices, false);

    std::vector<int> disc(num_of_vertices);
    std::vector<int> low(num_of_vertices);
    std::vector<int> parent(num_of_vertices, -1);

    std::vector<std::pair<int, int>> bridges;
    tarjan_s_time = 0;

    // Call the recursive helper function to find Bridges
    // in DFS tree rooted with vertex 'i'
    for (int i = 0; i < num_of_vertices; i++) {
        if (!visited[i])
            tarjan_s_bridge_finding_dfs(i, visited, disc, low, parent, bridges);
    }

    return bridges;
}

// A recursive function that finds bridges using DFS traversal
template <typename T>
void Graph<T>::tarjan_s_bridge_finding_dfs(int u,
                                        std::vector<bool> &visited,
                                        std::vector<int> &disc,
                                        std::vector<int> &low,
                                        std::vector<int> &parent,
                                        std::vector<std::pair<int, int>> &bridges) {

    // Mark the current node as visited
    visited[u] = true;

    // Initialize discovery tarjan_s_time and low value
    disc[u] = low[u] = ++tarjan_s_time;

    // Go through all vertices adjacent to this adjacency_matrix[u]
    for (int v = 0; v < adjacency_matrix.size(); v++) {

        // if the edge between U and V does not exist, then skip it
        if (adjacency_matrix[u][v] == INF) {
            continue;
        }

        // If v is not visited yet, then recur for it
        if (!visited[v]) {
            parent[v] = u;
            tarjan_s_bridge_finding_dfs(v, visited, disc, low, parent, bridges);

            // Check if the subtree rooted with v has a
            // connection to one of the ancestors of u
            low[u] = std::min(low[u], low[v]);

            // If the lowest vertex reachable from subtree
            // under v is  below u in DFS tree, then u-v
            // is a tarjans_find_bridges
            if (low[v] > disc[u]){
                bridges.emplace_back(u, v);
                std::cout << u << ' ' << v << '\n';
            }
        }
        // Update low value of u for parent function calls.
        else if (v != parent[u])
            low[u]  = std::min(low[u], disc[v]);
    }
}


// Explicit instantiation

template class Graph<int8_t>;
template class Graph<int16_t>;
template class Graph<int32_t>;
template class Graph<int64_t>;

template class Graph<float>;
template class Graph<double>;