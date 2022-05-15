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


EXPLICIT_INSTANTIATION(Edge);
EXPLICIT_INSTANTIATION(Vertex);
EXPLICIT_INSTANTIATION(BaseGraph);
EXPLICIT_INSTANTIATION(GraphTarjansBridges);
EXPLICIT_INSTANTIATION(GraphFloydWarshall);
EXPLICIT_INSTANTIATION(GraphDijkstra);
EXPLICIT_INSTANTIATION(GraphTraversal);
EXPLICIT_INSTANTIATION(Graph);


template <typename T>
Vertex<T>::Vertex(int id) {
    this->id = id;
    this->edges = std::list<Edge<T>>();
}


template <typename T>
Vertex<T>::Vertex(const Vertex &other) {
    id = other.id;
    edges = other.edges;
}


template <typename T>
void Vertex<T>::add_edge(Vertex<T>* neighbor, T distance) {
    for (auto it = edges.begin(); it != edges.end(); it++) {
        if (it->get_neighbor() == neighbor) {
            edges.erase(it);
            break;
        }
    }
    Edge<T> edge(neighbor, distance);       //
    edges.push_back(edge);
}

template<typename T>
void Vertex<T>::remove_edge(Vertex<T>* neighbor) {
    for (auto & it : edges) {
        if (it.get_neighbor() == neighbor) {
            edges.remove(it);           // change!!! It works, but very strange
            break;
        }
    }
}

template<typename T>
bool Edge<T>::operator== (const Edge<T> &other) {
    return (neighbor == other.neighbor) && (distance == other.distance);
}

template <typename T>
Edge<T>::Edge(Vertex<T>* neighbor, T distance) {
    this->neighbor = neighbor;
    this->distance = distance;
}



template <typename T>
BaseGraph<T>::BaseGraph(int num_of_vertices) {
    for (id_counter = 0; id_counter < num_of_vertices; id_counter++) {
        auto v = new Vertex<T>(id_counter);
        vertices.push_back(v);
    }
}


template <typename T>
BaseGraph<T>::BaseGraph(std::list<Vertex<T>*> &vertices) {
    this->vertices = vertices;
}

template <typename T>
BaseGraph<T>::BaseGraph(std::vector<std::vector<T>> &adjacency_matrix){
    this->adjacency_matrix = adjacency_matrix;
    this->id_counter = adjacency_matrix.size();

    for (int i = 0; i < adjacency_matrix.size(); i++) {
        auto v = new Vertex<T>(i);
        vertices.push_back(v);
    }
    for (int i = 0; i < adjacency_matrix.size(); i++) {
        for (int j = 0; j < adjacency_matrix.size(); j++) {
            if (adjacency_matrix[i][j] != INF<T>) {
                auto source = find_vertex(i);
                auto target = find_vertex(j);
                source->add_edge(target, adjacency_matrix[i][j]);
            }
        }
    }
}

template <typename T>
BaseGraph<T>::BaseGraph(std::vector<std::list<int>> &adjacency_list){
    this->adjacency_list = adjacency_list;
    this->id_counter = adjacency_list.size();

    for (int i = 0; i < adjacency_list.size(); i++) {
        auto v = new Vertex<T>(i);
        vertices.push_back(v);
    }
    for (int i = 0; i < adjacency_list.size(); i++) {
        for (int j = 0; j < adjacency_list.size(); j++) {
            auto it = std::find(adjacency_list[i].begin(), adjacency_list[i].end(), j);
            if (it != adjacency_list[i].end()) {
                auto source = find_vertex(i);
                auto target = find_vertex(j);
                source->add_edge(target, 0);
            }
        }
    }
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
BaseGraph<T>::~BaseGraph() {
    for (auto & v : vertices) {
        delete v;
    }
}

template <typename T>
int BaseGraph<T>::add_edge(int source_id, int target_id, int weight, EdgeType edge_type){

    // Edge, where start and end are the same vertex, is unexpected
    if (source_id == target_id) {
        return 1;
    }

    Vertex<T>* source = find_vertex(source_id);
    Vertex<T>* target = find_vertex(target_id);

    // If some vertex is not exists, then an error is considered
    if (source == nullptr || target == nullptr) {
        return 1;
    }


    switch (edge_type) {
        case UNDIRECTED:
            source->add_edge(target, weight);
            target->add_edge(source, weight);
            break;
        case DIRECTED:
            source->add_edge(target, weight);
            break;
        default:
            break;
    }

    return 0;
}

template <typename T>
int BaseGraph<T>::remove_edge(int source_id, int target_id, EdgeType edge_type) {

    // Edge, where start and end are the same vertex, is unexpected
    if (source_id == target_id) {
        return 1;
    }

    Vertex<T>* source = find_vertex(source_id);
    Vertex<T>* target = find_vertex(target_id);

    // If some vertex is not exists, then an error is considered
    if (source == nullptr || target == nullptr) {
        return 1;
    }

    switch (edge_type) {
        case UNDIRECTED:
            source->remove_edge(target);
            target->remove_edge(source);
            break;
        case DIRECTED:
            source->remove_edge(target);
            break;
        default:
            break;
    }

    return 0;
}


template <typename T>
int BaseGraph<T>::add_vertex() {
    auto v = new Vertex<T>(id_counter);
    vertices.push_back(v);
    id_counter++;
    return v->get_id();
}

template <typename T>
int BaseGraph<T>::remove_vertex(int id) {

    auto vtx = find_vertex(id);

    // if `vtx` is not in `vertices`, then just return
    if (vtx == nullptr) {
        return 1;
    }

    // delete all edges linking `vtx` with other vertices
    auto edges = vtx->get_edges();
    for (Edge<T> edge : edges) {
        Vertex<T>* neighbor = edge.get_neighbor();
        neighbor->remove_edge(vtx);
    }

    // delete `vtx` from list of all vertices
    auto it = std::find(vertices.begin(), vertices.end(), vtx);
    vertices.erase(it);

    return 0;
}


template <typename T>
Vertex<T>* BaseGraph<T>::find_vertex(int id) {
    for (auto v = vertices.begin(); v != vertices.end(); v++) {
        if ((*v)->id == id) {
            return *v;
        }
    }
    return nullptr;
}

template <typename T>
void BaseGraph<T>::actualize_adjacency_list() {
    adjacency_list = std::vector<std::list<int>>(id_counter, std::list<int>());

    for (int id = 0; id < id_counter; id++) {
        Vertex<T>* vtx = find_vertex(id);

        if (vtx == nullptr)
            continue;

        std::list<Edge<T>> edges = vtx->get_edges();
        for (Edge<T> edge : edges) {
            Vertex<T>* neighbor = edge.get_neighbor();
            adjacency_list[id].push_back(neighbor->get_id());
        }
    }
}

template <typename T>
void BaseGraph<T>::actualize_adjacency_matrix() {

    // initially adjacency_matrix is filled with infinities
    adjacency_matrix = std::vector<std::vector<T>>(id_counter, std::vector<T>(id_counter, INF<T>));

    for (int id = 0; id < id_counter; id++) {
        Vertex<T>* vtx = find_vertex(id);

        if (vtx == nullptr)
            continue;

        std::list<Edge<T>> edges = vtx->get_edges();
        for (Edge<T> edge : edges) {
            Vertex<T>* neighbor = edge.get_neighbor();
            T distance = edge.get_distance();
            adjacency_matrix[id][neighbor->get_id()] = distance;
        }
    }
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
void GraphTraversal<T>::print_vector(std::vector<T> vector_to_print) {
    std::cout << std::endl;
    for (int i = 0; i < vector_to_print.size(); i++) {
        std::cout << vector_to_print[i] << " ";
    }
}

template<typename T>
void GraphTraversal<T>::bfs_search() {
    int vertices = BaseGraph<T>::adjacency_list.size();
    std::cout << std::endl << "BFS search: ";
    std::vector<T> nodes(vertices, 0);
    std::queue<T> Queue;
    Queue.push(0);
    while (!Queue.empty()) {
        T node = Queue.front();
        Queue.pop();
        nodes[node] = 1;
        for (auto iter = BaseGraph<T>::adjacency_list[node].begin();
             iter != BaseGraph<T>::adjacency_list[node].end(); ++iter) {
            if (nodes[*iter] == 0) {
                Queue.push(*iter);
            }
        }
        std::cout << node << " ";
    }
}

template<typename T>
void GraphTraversal<T>::dfs_search() {
    int vertices = BaseGraph<T>::adjacency_list.size();
    std::cout << std::endl << "DFS search: ";
    std::vector<T> nodes(vertices, 0);
    std::stack<T> Stack;
    Stack.push(0);
    while (!Stack.empty()) {
        T node = Stack.top();
        Stack.pop();
        if (nodes[node] == 1) continue;
        nodes[node] = 1;
        for (auto iter = BaseGraph<T>::adjacency_list[node].rbegin();
             iter != BaseGraph<T>::adjacency_list[node].rend(); ++iter) {
            if (nodes[*iter] != 1) {
                Stack.push(*iter);
            }
        }
        std::cout << node << " ";
    }
}

template<typename T>
std::vector<T> GraphTraversal<T>::find_path(const T from, const T to) { // Find a path between two vertices
    int vertices = BaseGraph<T>::adjacency_list.size();
    if (from > vertices || to > vertices) {
        std::cout << "Find min path error. Index exceeds the number of vertices."
                     "Index must be not more " << vertices - 1 << "\n";
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
        for (auto iter = BaseGraph<T>::adjacency_list[node].begin();
             iter != BaseGraph<T>::adjacency_list[node].end(); ++iter) {
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
std::vector<T> GraphTraversal<T>::topological_sort() { // Topological sorting of a graph
    int vertices = BaseGraph<T>::adjacency_list.size();
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
                for (auto iter = BaseGraph<T>::adjacency_list[node].rbegin();
                     iter != BaseGraph<T>::adjacency_list[node].rend(); ++iter) {
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

template<typename T>
T get_inf() {
    T inf = std::numeric_limits<T>::infinity();
    if (inf == (T) 0) {
        return std::numeric_limits<T>::max();
    }
    return inf;
}
