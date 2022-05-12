#include<iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <cstdint>
#include <tuple>
#include "graph.h"

#define EXPLICIT_INSTANTIATION(CLASSNAME)   \
    template class CLASSNAME<int8_t>;       \
    template class CLASSNAME<int16_t>;      \
    template class CLASSNAME<int32_t>;      \
    template class CLASSNAME<int64_t>;      \
                                            \
    template class CLASSNAME<float>;        \
    template class CLASSNAME<double>;       \


EXPLICIT_INSTANTIATION(BaseGraph);
EXPLICIT_INSTANTIATION(GraphTarjansBridges);
EXPLICIT_INSTANTIATION(GraphFloydWarshall);
EXPLICIT_INSTANTIATION(GraphDijkstra);
EXPLICIT_INSTANTIATION(GraphTraversal);
EXPLICIT_INSTANTIATION(Graph);


template <typename T>
Node<T>::Node(int id) {
    this->id = id;
}


template <typename T>
void Node<T>::add_neighbor(Node<T>* neighbor, T distance) {
    Edge<T> edge(neighbor, distance);       //
    neighbors.push_back(edge);
}


template <typename T>
void Node<T>::remove_neighbor(Node<T>* neighbor) {
    auto it = std::find(neighbors.begin(), neighbors.end(), neighbor);
    if (it != neighbors.end()) {
        neighbors.remove(it);
    }
}


template <typename T>
Edge<T>::Edge(Node<T>* neighbor, T distance) {
    this->neighbor = neighbor;
    this->distance = distance;
}



template <typename T>
BaseGraph<T>::BaseGraph(int num_of_vertices){
    for (int i = 0; i < num_of_vertices; i++) {
        std::vector<T> row(num_of_vertices, INF<T>);
        row[i] = 0;
        adjacency_matrix.push_back(row);
    }
}

template <typename T>
BaseGraph<T>::BaseGraph(std::vector<std::vector<T>> &adjacency_matrix){
    this->adjacency_matrix = adjacency_matrix;
}

template <typename T>
BaseGraph<T>::BaseGraph(std::vector<std::list<T>> &adjacency_list){
    this->adjacency_list = adjacency_list;
}

template <typename T>
BaseGraph<T>::BaseGraph(const BaseGraph &other) {
    adjacency_matrix = other.adjacency_matrix;
    adjacency_list = other.adjacency_list;
}

template <typename T>
BaseGraph<T>::BaseGraph(BaseGraph &&other) noexcept {
    adjacency_matrix = other.adjacency_matrix;
    adjacency_list = other.adjacency_list;
}

template <typename T>
void BaseGraph<T>::add_edge(int source, int target, int weight, EdgeType edge_type){
    if (edge_type == UNDIRECTED) {
        adjacency_matrix[source][target] = weight;
        adjacency_matrix[target][source] = weight;
    } else {
        adjacency_matrix[source][target] = weight;
    }
}

template<typename T>
void BaseGraph<T>::synchronize_data(/*DataType source_data, DataType target_data*/) { // нужно позже реализовать
    adjacency_list.resize(adjacency_matrix.size());
    for (int orig = 0; orig < adjacency_matrix.size(); orig++) {
        for (int dest = 0; dest < adjacency_matrix[orig].size(); dest++) {
            if (orig != dest && adjacency_matrix[orig][dest] != INF<T>) {
                adjacency_list[orig].push_back(dest);
            }
        }
    }
    //Alternative method of realization
    /*switch (source_data) {
        case ADJACENCY_MATRIX:
            break;
        case ADJACENCY_LIST:
            break;
        default:
            break;
    }*/
}

// DFS based function to find all bridges. It uses recursive function tarjan_s_bridge_finding_dfs
template <typename T>
std::vector<std::pair<int, int>> GraphTarjansBridges<T>::tarjans_find_bridges()
{
    int num_of_vertices = BaseGraph<T>::adjacency_matrix.size();

    // Mark all the vertices as not visited
    std::vector<bool> visited(num_of_vertices, false);

    std::vector<int> disc(num_of_vertices);
    std::vector<int> low(num_of_vertices);

    // initially parents are not specified
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
void GraphTarjansBridges<T>::tarjan_s_bridge_finding_dfs(int u,
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
    for (int v = 0; v < BaseGraph<T>::adjacency_matrix.size(); v++) {

        // if the edge between U and V does not exist, then skip it
        if (BaseGraph<T>::adjacency_matrix[u][v] == INF<T>) {
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
std::vector<std::vector<T>> GraphFloydWarshall<T>::floyd_warshall() {
    int vertices = BaseGraph<T>::adjacency_matrix.size();
    // Floyd-Warshall algorithm realization
    for (int intermediate = 0; intermediate < vertices; intermediate++) {
        for (int origin = 0; origin < vertices; origin++) {
            for (int destination = 0; destination < vertices; destination++) {
                //let paths_matrix = A, then
                //A(k)[x,y] = min(A(k-1)[x,y], A(k-1)[x,k] + A(k-1)[k,y])
                BaseGraph<T>::adjacency_matrix[origin][destination] = min(origin, destination, intermediate);
            }
        }
    }
    return BaseGraph<T>::adjacency_matrix;
}

//Floyd-Warshall algorithm with restore matrix
template<typename T>
std::tuple<std::vector<std::vector<T>>, std::vector<std::vector<int>>> GraphFloydWarshall<T>::floyd_warshall_ways() {
    int vertices = BaseGraph<T>::adjacency_matrix.size();
    //initializing vector to restore the paths
    restore_matrix.assign(vertices, std::vector<int> (vertices));
    for (int row = 0; row < vertices; row++) {
        for (int col = 0; col < vertices; col++) {
            if (BaseGraph<T>::adjacency_matrix[row][col] == INF<T>) {
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
                if (BaseGraph<T>::adjacency_matrix[origin][destination] > min(origin, destination, intermediate)) {
                    BaseGraph<T>::adjacency_matrix[origin][destination] = min(origin, destination, intermediate);
                    //saving previous nodes to restore paths
                    restore_matrix[origin][destination] = restore_matrix[origin][intermediate];
                }
            }
        }
    }
    //Check for negative cycle
    for (int node = 0; node < vertices; node++) {
        if (BaseGraph<T>::adjacency_matrix[node][node] != 0) {
            BaseGraph<T>::adjacency_matrix.clear();
            restore_matrix.clear();
        }
    }
    return make_tuple(BaseGraph<T>::adjacency_matrix, restore_matrix);
}

//Uses restore_matrix from Floyd_Warshall_ways to restore paths
template<typename T>
std::vector<int> GraphFloydWarshall<T>::restore_path(int from, int to) {
    int vertices = BaseGraph<T>::adjacency_matrix.size();
    restored_path.clear();
    if ((vertices < from) || (vertices < to)) return restored_path;
    if (restore_matrix.empty()) return restored_path;
    int current = from - 1;
    int destination = to - 1;
    if (BaseGraph<T>::adjacency_matrix[current][destination] == INF<T>) return restored_path;
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
T GraphFloydWarshall<T>::min(int orig, int dest, int med) {
    T actual = BaseGraph<T>::adjacency_matrix[orig][dest];
    T alternative = 0;
    if (BaseGraph<T>::adjacency_matrix[orig][med] == INF<T> || BaseGraph<T>::adjacency_matrix[med][dest] == INF<T>) {
        alternative = INF<T>;
    }
    else {
        alternative = BaseGraph<T>::adjacency_matrix[orig][med] + BaseGraph<T>::adjacency_matrix[med][dest];
    }
    if (actual > alternative) return alternative;
    else return actual;
}

//receives start node and finds the shortest distances from it
template<typename T>
std::vector<T> GraphDijkstra<T>::dijkstra_from_one_vertex(int origin) {
    int vertices = BaseGraph<T>::adjacency_matrix.size();
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
        shortest_distances[node] = BaseGraph<T>::adjacency_matrix[origin][node];
    }
    //Dijkstra algorithm realization
    for (int in_cln = 1; in_cln < vertices; in_cln++) {
        T min = INF<T>;
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
                if (BaseGraph<T>::adjacency_matrix[next_node][node] != INF<T>) {
                    if (min + BaseGraph<T>::adjacency_matrix[next_node][node] < shortest_distances[node]) {
                        shortest_distances[node] = min + BaseGraph<T>::adjacency_matrix[next_node][node];
                    }
                }
            }
        }
    }
    return shortest_distances;
}

//Applies Dijkstra algorithm for every node to make paths matrix
template<typename T>
std::vector<std::vector<T>> GraphDijkstra<T>::dijkstra() {
    int vertices = BaseGraph<T>::adjacency_matrix.size();
    std::vector<std::vector<T>> paths_matrix (vertices, std::vector<T> (vertices));
    for (int i = 1; i <= vertices; i++) {
        paths_matrix[i-1] = dijkstra_from_one_vertex(i);
    }
    BaseGraph<T>::adjacency_matrix = paths_matrix;
    return BaseGraph<T>::adjacency_matrix;
}

template<typename T>
void GraphTraversal<T>::bfs_search_to_find_min_path(int vertice_1, int vertice_2)
{
    int vertices = BaseGraph<T>::adjacency_matrix.size();
    int* nodes = new int[vertices];
    for (int i = 0; i < vertices; i++) {
        nodes[i] = 0;
    }

    std::queue<int> Queue;
    std::stack<int> Path;
    struct Edge {
        int begin;
        int end;
    };
    std::stack<Edge> Edges;
    Edge e;

    Queue.push(vertice_1);
    while (!Queue.empty())
    {
        int node = Queue.front();
        Queue.pop();
        nodes[node] = 2;
        for (int j = 0; j < vertices; j++)
        {
            if (BaseGraph<T>::adjacency_matrix[node][j] == 1 && nodes[j] == 0)
            {
                Queue.push(j);
                nodes[j] = 1;
                e.begin = node; e.end = j;
                Edges.push(e);
                if (node == vertice_2) break;
            }
        }
    }
    while (!Edges.empty()) {
        e = Edges.top();
        Edges.pop();
        if (e.end == vertice_2) {
            vertice_2 = e.begin;
            Path.push(e.end);
        }
    }
    std::cout << vertice_2;
    while (!Path.empty()) {
        std::cout << "->" << Path.top();
        Path.pop();
    }
    delete[] nodes;
    nodes = nullptr;
}

template<typename T>
void GraphTraversal<T>::dfs_search_for_topological_sort()
{
    int vertices = BaseGraph<T>::adjacency_matrix.size();
    int* nodes = new int[vertices];
    for (int i = 0; i < vertices; i++) {
        nodes[i] = 0;
    }

    std::stack<int> Stack;
    std::stack<int> Topological_Sorted;

    for (int i = 0; i < vertices; i++)
    {
        if (nodes[i] == 0)
        {
            Stack.push(i);
            while (!Stack.empty())
            {
                int node = Stack.top();
                while (nodes[node] == 2)
                {
                    Stack.pop();
                    node = Stack.top();
                }

                if (nodes[node] == 0)
                {
                    nodes[node] = 1;
                    bool has_edge = false;
                    int j = vertices - 1;
                    for (; j >= 0; j--) {
                        if (BaseGraph<T>::adjacency_matrix[node][j] and nodes[j] != 2)
                        {
                            Stack.push(j);
                            has_edge = true;
                        }
                    }
                    if (!has_edge and j < 0)
                    {
                        nodes[node] = 2;
                        Stack.pop();
                        Topological_Sorted.push(node);
                    }
                }
                else
                {
                    nodes[node] = 2;
                    Stack.pop();
                    Topological_Sorted.push(node);
                }
            }
        }
    }

    std::cout << std::endl;
    while (!Topological_Sorted.empty())
    {
        std::cout << Topological_Sorted.top() << " ";
        Topological_Sorted.pop();
    }

    delete[] nodes;
    nodes = nullptr;
}

template<typename T>
T get_inf() {
    T inf = std::numeric_limits<T>::infinity();
    if (inf == (T) 0) {
        return std::numeric_limits<T>::max();
    }
    return inf;
}
