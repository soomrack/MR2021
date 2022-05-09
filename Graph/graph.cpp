#include<iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <cstdint>
#include <cmath>
#include <tuple>
#include "graph.h"

// Explicit instantiation
template class Graph<int8_t>;
template class Graph<int16_t>;
template class Graph<int32_t>;
template class Graph<int64_t>;

template class Graph<float>;
template class Graph<double>;


template <typename T>
Graph<T>::Graph(int vertices){
    conditional_inf = get_inf<T>();
    for (int i = 0; i < vertices; i++) {
        std::vector<T> row(vertices, conditional_inf);
        row[i] = 0;
        adjacency_matrix.push_back(row);
    }
}

template <typename T>
Graph<T>::Graph(std::vector<std::vector<T>> &adjacency_matrix){
    vertices = adjacency_matrix.size();
    conditional_inf = get_inf<T>();
    this->adjacency_matrix = adjacency_matrix;
}

template <typename T>
Graph<T>::Graph(std::vector<std::list<T>> &adjacency_list){
    vertices = adjacency_list.size();
    conditional_inf = get_inf<T>();
    this->adjacency_list = adjacency_list;
}

template <typename T>
Graph<T>::Graph(const Graph &other) {
    conditional_inf = other.conditional_inf;
    adjacency_matrix = other.adjacency_matrix;
    adjacency_list = other.adjacency_list;
}

template <typename T>
Graph<T>::Graph(Graph &&other) noexcept {
    conditional_inf = other.conditional_inf;
    adjacency_matrix = other.adjacency_matrix;
    adjacency_list = other.adjacency_list;
}

template <typename T>
void Graph<T>::add_edge(int source, int target, int weight, EdgeType edge_type){
    if (edge_type == UNDIRECTED) {
        adjacency_matrix[source][target] = weight;
        adjacency_matrix[target][source] = weight;
    } else {
        adjacency_matrix[source][target] = weight;
    }
}

template<typename T>
void Graph<T>::synchronize_data(DataType source_data, DataType target_data) { // нужно позже реализовать
    switch (source_data) {
        case ADJACENCY_MATRIX:
            break;
        case ADJACENCY_LIST:
            break;
        default:
            break;
    }
}

template<typename T>
std::vector<std::vector<T>> Graph<T>::get_adjacency_matrix() { //получить матрицу смежности по списку смежности
    for (int v = 0; v < vertices; v++) {
        std::vector<T> row(vertices, 0);
        adjacency_matrix.push_back(row);
        for (auto iter = adjacency_list[v].begin(); iter != adjacency_list[v].end(); ++iter) {
            adjacency_matrix[v][*iter] = 1;
        }
    }
    return adjacency_matrix;
}

template<typename T>
void Graph<T>::print_adjacency_list() { //вывод списка смежности на экран
    for (int v = 0; v < adjacency_list.size(); v++) {
        std::cout << v << ": ";
        for (auto iter = adjacency_list[v].begin(); iter != adjacency_list[v].end(); ++iter) {
            std::cout << *iter << " ";
        }
        std::cout << std::endl;
    }
}

template<typename T>
void Graph<T>::print_adjacency_matrix() { //вывод матрицы смежности на экран
    if (adjacency_matrix.size() == 0) {
        std::cout << "Print adjacency matrix error. Adjacency matrix size must be more zero"
                     "To fix this mistake input x.get_adjacency_matrix()";
        return;
    }
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++)
            std::cout << adjacency_matrix[i][j] << " ";
        std::cout << "\n";
    }
}

template<typename T>
void Graph<T>::print_vector(std::vector<T> vector_to_print) { //вывод вектора
    std::cout << std::endl;
    for (int i = 0; i < vector_to_print.size(); i++) {
        std::cout << vector_to_print[i] << " ";
    }
}

template<typename T>
void Graph<T>::bfs_search() {
    std::cout << std::endl << "BFS search: ";
    std::vector<T> nodes(vertices, 0);
    std::queue<T> Queue;
    Queue.push(0);
    while (!Queue.empty()) {
        T node = Queue.front();
        Queue.pop();
        nodes[node] = 1;
        for (auto iter = adjacency_list[node].begin(); iter != adjacency_list[node].end(); ++iter) {
            if (nodes[*iter] == 0) {
                Queue.push(*iter);
            }
        }
        std::cout << node << " ";
    }
}

template<typename T>
void Graph<T>::dfs_search() {
    std::cout << std::endl << "DFS search: ";
    std::vector<T> nodes(vertices, 0);
    std::stack<T> Stack;
    Stack.push(0);
    while (!Stack.empty()) {
        T node = Stack.top();
        Stack.pop();
        if (nodes[node] == 1) continue;
        nodes[node] = 1;
        for (auto iter = adjacency_list[node].rbegin(); iter != adjacency_list[node].rend(); ++iter) {
            if (nodes[*iter] != 1) {
                Stack.push(*iter);
            }
        }
        std::cout << node << " ";
    }
}

template<typename T>
std::vector<T> Graph<T>::find_path(const T from, const T to) { // Find a path between two vertices
    if (from > vertices || to > vertices) {
        std::cout << "Find min path error. Index exceeds the number of vertices. Index must be not more " << vertices - 1 << "\n";
        return restored_path;
    }
    if (from == to) {
        std::cout << "Find min path error. Check entrance and exit.";
        return restored_path;
    }
    std::vector<T> nodes(vertices, 0);
    std::queue<T> Queue;
    struct Edge {
        T begin;
        T end;
    };
    Edge Edge_beetween_two_vertices;
    std::stack<Edge> Edges;
    Queue.push(from);
    bool find = false;
    while (!Queue.empty() && !find) {
        T node = Queue.front();
        Queue.pop();
        nodes[node] = 1;
        for (auto iter = adjacency_list[node].begin(); iter != adjacency_list[node].end(); ++iter) {
            if (nodes[*iter] == 0) {
                Queue.push(*iter);
                Edge_beetween_two_vertices.begin = node;
                Edge_beetween_two_vertices.end = *iter;
                Edges.push(Edge_beetween_two_vertices);
                if (*iter == to) {
                    find = true;
                    break;
                }
            }
        }
    }
    if (find) {
        T update_to = to;
        while (update_to != from && !Edges.empty()) {
            Edge_beetween_two_vertices = Edges.top();
            Edges.pop();
            if (Edge_beetween_two_vertices.end == update_to) {
                update_to = Edge_beetween_two_vertices.begin;
                restored_path.push_back(Edge_beetween_two_vertices.end);
            }
        }
        restored_path.push_back(from);
        std::reverse(restored_path.begin(), restored_path.end());
    }
    else {
        std::cout << "No path from " << from << " to " << to << ".";
    }
    return restored_path;
}

template<typename T>
std::vector<T> Graph<T>::topological_sort() { // Topological sorting of a graph
    std::vector<T> nodes(vertices, 0);
    std::stack<T> Stack;
    for (int i = 0; i < vertices; ++i) {
        if (nodes[i] == 0) {
            Stack.push(i);
            while (!Stack.empty()) {
                T node = Stack.top();
                if (nodes[node] == 1) {
                    topological_sorted_graph.push_back(node);
                    Stack.pop();
                    continue;
                }
                nodes[node] = 1;
                bool has_edge = false;
                for (auto iter = adjacency_list[node].rbegin(); iter != adjacency_list[node].rend(); ++iter) {
                    if (nodes[*iter] != 1) {
                        Stack.push(*iter);
                        has_edge = true;
                    }
                }
                if (!has_edge) {
                    topological_sorted_graph.push_back(node);
                    Stack.pop();
                }
            }
        }
    }
    std::reverse(topological_sorted_graph.begin(), topological_sorted_graph.end());
    return topological_sorted_graph;
}


// DFS based function to find all bridges. It uses recursive function tarjan_s_bridge_finding_dfs
template <typename T>
std::vector<std::pair<int, int>> Graph<T>::tarjans_find_bridges()
{
    int vertices = adjacency_matrix.size();

    // Mark all the vertices as not visited
    std::vector<bool> visited(vertices, false);

    std::vector<int> disc(vertices);
    std::vector<int> low(vertices);

    // initially parents are not specified
    std::vector<int> parent(vertices, -1);

    std::vector<std::pair<int, int>> bridges;
    tarjan_s_time = 0;

    // Call the recursive helper function to find Bridges
    // in DFS tree rooted with vertex 'i'
    for (int i = 0; i < vertices; i++) {
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
        if (adjacency_matrix[u][v] == conditional_inf) {
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
            }
        }
            // Update low value of u for parent function calls.
        else if (v != parent[u])
            low[u]  = std::min(low[u], disc[v]);
    }
}

//Floyd-Warshall algorithm without restore matrix
template<typename T>
std::vector<std::vector<T>> Graph<T>::floyd_warshall() {
    if (!check_adjacency_matrix()){
        std::vector<std::vector<T>> zero;
        return zero;
    }
    // Floyd-Warshall algorithm realization
    for (int intermediate = 0; intermediate < vertices; intermediate++) {
        for (int origin = 0; origin < vertices; origin++) {
            for (int destination = 0; destination < vertices; destination++) {
                //let paths_matrix = A, then
                //A(k)[x,y] = min(A(k-1)[x,y], A(k-1)[x,k] + A(k-1)[k,y])
                adjacency_matrix[origin][destination] = min(origin, destination, intermediate);
            }
        }
    }
    return adjacency_matrix;
}

//Floyd-Warshall algorithm with restore matrix
template<typename T>
std::tuple<std::vector<std::vector<T>>, std::vector<std::vector<int>>> Graph<T>::floyd_warshall_ways() {
    if (!check_adjacency_matrix()) {
        adjacency_matrix.clear();
        restore_matrix.clear();
        return std::make_tuple(adjacency_matrix, restore_matrix);
    }
    //initializing vector to restore the paths
    restore_matrix.assign(vertices, std::vector<int> (vertices));
    for (int row = 0; row < vertices; row++) {
        for (int col = 0; col < vertices; col++) {
            if (adjacency_matrix[row][col] == conditional_inf) {
                restore_matrix[row][col] = 0;
            } else
                restore_matrix[row][col] = col + 1;
        }
    }
    // Floyd-Warshall algorithm realization
    for (int intermediate = 0; intermediate < vertices; intermediate++) {
        for (int origin = 0; origin < vertices; origin++) {
            for (int destination = 0; destination < vertices; destination++) {
                //let paths_matrix = A, then
                //A(k)[x,y] = min(A(k-1)[x,y], A(k-1)[x,k] + A(k-1)[k,y])
                if (adjacency_matrix[origin][destination] > min(origin, destination, intermediate)) {
                    adjacency_matrix[origin][destination] = min(origin, destination, intermediate);
                    //saving previous nodes to restore paths
                    restore_matrix[origin][destination] = restore_matrix[origin][intermediate];
                }
            }
        }
    }
    //Check for negative cycle
    for (int node = 0; node < vertices; node++) {
        if (adjacency_matrix[node][node] != 0) {
            adjacency_matrix.clear();
            restore_matrix.clear();
        }
    }
    return make_tuple(adjacency_matrix, restore_matrix);
}

//Uses restore_matrix from Floyd_Warshall_ways to restore paths
template<typename T>
std::vector<T> Graph<T>::restore_path(int from, int to) {
    restored_path.clear();
    if ((vertices < from) || (vertices < to)) return restored_path;
    if (restore_matrix.empty()) return restored_path;
    int current = from - 1;
    int destination = to - 1;
    if (adjacency_matrix[current][destination] == conditional_inf) return restored_path;
    while (current != destination) {
        restored_path.push_back(current);
        current = restore_matrix[current][destination] - 1;
        if (current < 0) {
            restored_path.clear();
            return restored_path;
        }
    }
    restored_path.push_back(current);
    return restored_path;
}

//method finds if the way through an intermediate vertex is the shortest or not
template<typename T>
T Graph<T>::min(int origin, int destination, int intermediate) {
    T actual = adjacency_matrix[origin][destination];
    T alternative = 0;
    if (adjacency_matrix[origin][intermediate] == conditional_inf || adjacency_matrix[intermediate][destination] == conditional_inf) alternative = conditional_inf;
    else alternative = adjacency_matrix[origin][intermediate] + adjacency_matrix[intermediate][destination];
    if (actual > alternative) return alternative;
    else return actual;
}

//check matrix to prevent undefined behaviour
template<typename T>
bool Graph<T>::check_adjacency_matrix() {
    vertices = adjacency_matrix.size();
    //checking a size of input matrix
    for (int row = 0; row < vertices; row++) {
        if (adjacency_matrix[row].size() != vertices) {
            vertices = 0;
            return false;
        }
    }
    //checking the main diagonal
    for (int node = 0; node < vertices; node++) {
        if (adjacency_matrix[node][node] != 0) {
            vertices = 0;
            return false;
        }
    }
    return true;
}

//receives start node and finds the shortest distances from it
template<typename T>
std::vector<T> Graph<T>::dijkstra_from_one_vertex(int origin) {
    origin--;
    std::vector<T> shortest_distances;
    // Checking correct input of the matrix and origin
    if (origin > vertices) return shortest_distances;
    //vector to store passed nodes
    std::vector<bool> passed(vertices);
    //vector to store the shortest distance from origin to all nodes
    shortest_distances.resize(vertices);
    //initializing vectors
    passed[origin] = true;
    for (int node = 0; node < vertices; node++) {
        shortest_distances[node] = adjacency_matrix[origin][node];
    }
    //Dijkstra algorithm realization
    for (int in_cln = 1; in_cln < vertices; in_cln++) {
        T min = conditional_inf;
        int next_node = -1;
        //Finding the nearest node
        for (int node = 0; node < vertices; node++) {
            //We can't go through passed nodes
            if (!passed[node]) {
                if (min > shortest_distances[node]) {
                    min = shortest_distances[node];
                    next_node = node;
                }
            }
        }
        if (next_node == -1) return shortest_distances;
        passed[next_node] = true;
        //Finding the shortest paths through this node
        for (int node = 0; node < vertices; node++) {
            // We can't go through passed nodes
            if (!passed[node]) {
                if (adjacency_matrix[next_node][node] != conditional_inf) {
                    if (min + adjacency_matrix[next_node][node] < shortest_distances[node]) {
                        shortest_distances[node] = min + adjacency_matrix[next_node][node];
                    }
                }
            }
        }
    }
    return shortest_distances;
}

//Applies Dijkstra algorithm for every node to make paths matrix
template<typename T>
std::vector<std::vector<T>> Graph<T>::dijkstra() {
    if (!check_adjacency_matrix()) {
        std::vector<std::vector<T>> zero;
        return zero;
    }
    std::vector<std::vector<T>> paths_matrix (vertices, std::vector<T> (vertices));
    for (int i = 1; i <= vertices; i++) {
        paths_matrix[i-1] = dijkstra_from_one_vertex(i);
    }
    adjacency_matrix = paths_matrix;
    return adjacency_matrix;
}

template<typename T>
T get_inf() {
    T inf = std::numeric_limits<T>::infinity();
    if (inf == (T) 0) {
        return std::numeric_limits<T>::max();
    }
    return inf;
}