#include <iostream>
#include <vector>
#include <cmath>
#include <tuple>
#include <random>

#define INF numeric_limits<int>::max()
using namespace std;

template<class T>
class Graph {
public:
    explicit Graph(vector<T> &);
    explicit Graph(vector<vector<T>> &);
    Graph<T> & operator= (const Graph<T> &);
    ~Graph();
public:
    ////Floyd-Warshall methods
    //Floyd-Warshall algorithm without restore matrix
    vector<vector<T>> FW_clear();
    //Floyd-Warshall algorithm with restore matrix
    tuple<vector<vector<T>>, vector<vector<int>>> FW_alg_ways();
    //Uses restore_matrix from FW_alg to restore paths
    vector<int> restore_path(int, int);
public:
    ////Dijkstra methods
    //receives start node and finds the shortest distances from it
    vector<T> Dijkstra_alg(int);
    //Applies Dijkstra algorithm for every node to make paths matrix
    vector<vector<T>> paths_matrix_Dij();
public:
    ////auxiliary functions of class
    //getters
    vector<vector<T>> get_dist_matrix() { return dist_matrix; };
    vector<vector<T>> get_paths_matrix() { return paths_matrix; };
    vector<vector<int>> get_restore_matrix() { return restore_matrix; };
    vector<int> get_restored_path() { return restored_path; };
    vector<T> get_shortest_distances() { return shortest_distances; };
    //print functions
    void print_paths_matrix();
    void print_restored_path();

private:
    int nodes = 0;
    //initial matrix with direct distances between nodes
    vector<vector<T>> dist_matrix;
    //resulting matrix with the shortest paths between all nodes
    vector<vector<T>> paths_matrix;
    //matrix, used to restore paths with Floyd-Warshall algorithm modification
    vector<vector<int>> restore_matrix;
    //vector, used to store restored path
    vector<int> restored_path;
    //vector, used to store the shortest distances from one node in original Dijkstra algorithm
    vector<T> shortest_distances;
    //compares path from origin node to destination with path through intermediate node and returns the shortest
    T min(int, int, int);
    void clean();
};

template<typename T>
Graph<T>::Graph(vector<T> &grid) {
    //checking a size of input matrix
    if (grid.size() != pow((int) sqrt(grid.size()), 2)) {
        return;
    }
    //checking the main diagonal
    nodes = (int) sqrt(grid.size());
    for (int node = 0; node < nodes; node++) {
        if (grid[node * nodes + node] != 0) {
            nodes = 0;
            return;
        }
    }
    dist_matrix.assign(nodes, vector<T> (nodes));
    for (int row = 0; row < nodes; row++) {
        for (int col = 0; col < nodes; col++) {
            dist_matrix[row][col] = grid[row * nodes + col];
        }
    }
}

template<typename T>
Graph<T>::Graph(vector<vector<T>> &grid) {
    nodes = grid.size();
    //checking a size of input matrix
    for (int row = 0; row < nodes; row++) {
        if (grid[row].size() != nodes) {
            nodes = 0;
            return;
        }
    }
    //checking the main diagonal
    for (int node = 0; node < nodes; node++) {
        if (grid[node][node] != 0) {
            nodes = 0;
            return;
        }
    }
    dist_matrix = grid;
}

template<typename T>
Graph<T> & Graph<T>::operator= (const Graph<T> &other) {
    if (this == &other) {
        return *this;
    }
    this->nodes = other.nodes;
    this->paths_matrix = other.paths_matrix;
    this->shortest_distances = other.shortest_distances;
    this->restored_path = other.restored_path;
    this->restore_matrix = other.restore_matrix;
    this->dist_matrix = other.dist_matrix;
}

template<typename T>
Graph<T>::~Graph(){
    nodes = 0;
    clean();
}

template<typename T>
void Graph<T>::clean() {
    dist_matrix.clear();
    paths_matrix.clear();
    restore_matrix.clear();
    restored_path.clear();
    shortest_distances.clear();
}

////////////////////////////////////////////////
////Floyd-Warshall methods
////////////////////////////////////////////////

template<typename T>
vector<vector<T>> Graph<T>::FW_clear() {
    paths_matrix = dist_matrix;
    // Floyd-Warshall algorithm realization
    for (int intermediate = 0; intermediate < nodes; intermediate++) {
        for (int origin = 0; origin < nodes; origin++) {
            for (int destination = 0; destination < nodes; destination++) {
                //let paths_matrix = A, then
                //A(k)[x,y] = min(A(k-1)[x,y], A(k-1)[x,k] + A(k-1)[k,y])
                paths_matrix[origin][destination] = min(origin, destination, intermediate);
            }
        }
    }
    return paths_matrix;
}

template<typename T>
tuple<vector<vector<T>>, vector<vector<int>>> Graph<T>::FW_alg_ways() {
    paths_matrix = dist_matrix;
    //initializing vector to restore the paths
    restore_matrix.assign(nodes, vector<int> (nodes));
    for (int row = 0; row < nodes; row++) {
        for (int col = 0; col < nodes; col++) {
            if (paths_matrix[row][col] == INF) {
                restore_matrix[row][col] = 0;
            } else
                restore_matrix[row][col] = col + 1;
        }
    }
    // Floyd-Warshall algorithm realization
    for (int intermediate = 0; intermediate < nodes; intermediate++) {
        for (int origin = 0; origin < nodes; origin++) {
            for (int destination = 0; destination < nodes; destination++) {
                //let paths_matrix = A, then
                //A(k)[x,y] = min(A(k-1)[x,y], A(k-1)[x,k] + A(k-1)[k,y])
                if (paths_matrix[origin][destination] > min(origin, destination, intermediate)) {
                    paths_matrix[origin][destination] = min(origin, destination, intermediate);
                    //saving previous nodes to restore paths
                    restore_matrix[origin][destination] = restore_matrix[origin][intermediate];
                }
            }
        }
    }
    //Check for negative cycle
    for (int node = 0; node < nodes; node++) {
        if (paths_matrix[node][node] != 0) {
            paths_matrix.clear();
            restore_matrix.clear();
            cout << "negative cycle" << endl;
        }
    }
    return make_tuple(paths_matrix, restore_matrix);
}

template<typename T>
vector<int> Graph<T>::restore_path(int from, int to) {
    restored_path.clear();
    if ((nodes < from) || (nodes < to)) return restored_path;
    if (restore_matrix.empty()) return restored_path;
    int current = from - 1;
    int destination = to - 1;
    if (paths_matrix[current][destination] == INF) return restored_path;
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

template<typename T>
T Graph<T>::min(int origin, int destination, int intermediate) {
    T actual = paths_matrix[origin][destination];
    T alternative = 0;
    if (paths_matrix[origin][intermediate] == INF || paths_matrix[intermediate][destination] == INF) alternative = INF;
    else alternative = paths_matrix[origin][intermediate] + paths_matrix[intermediate][destination];
    if (actual > alternative) return alternative;
    else return actual;
}

////////////////////////////////////////////////
////Dijkstra methods
////////////////////////////////////////////////

template<typename T>
vector<T> Graph<T>::Dijkstra_alg(int origin) {
    origin--;
    shortest_distances.clear();
    // Checking correct input of the matrix and origin
    if (origin > nodes) return shortest_distances;
    //vector to store passed nodes
    vector<bool> passed(nodes);
    //vector to store the shortest distance from origin to all nodes
    shortest_distances.resize(nodes);
    //initializing vectors
    passed[origin] = true;
    for (int node = 0; node < nodes; node++) {
        shortest_distances[node] = dist_matrix[origin][node];
    }
    //Dijkstra algorithm realization
    for (int in_cln = 1; in_cln < nodes; in_cln++) {
        int min = INF;
        int next_node = -1;
        //Finding the nearest node
        for (int node = 0; node < nodes; node++) {
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
        for (int node = 0; node < nodes; node++) {
            // We can't go through passed nodes
            if (!passed[node]) {
                if (dist_matrix[next_node][node] != INF) {
                    if (min + dist_matrix[next_node][node] < shortest_distances[node]) {
                        shortest_distances[node] = min + dist_matrix[next_node][node];
                    }
                }
            }
        }
    }
    return shortest_distances;
}

template<typename T>
vector<vector<T>> Graph<T>::paths_matrix_Dij() {
    paths_matrix.assign(nodes, vector<T> (nodes));
    for (int i = 1; i <= nodes; i++) {
        Dijkstra_alg(i);
        paths_matrix[i-1] = shortest_distances;
    }
    return paths_matrix;
}

////////////////////////////////////////////////
////auxiliary functions of class
////////////////////////////////////////////////

template<typename T>
void Graph<T>::print_paths_matrix() {
    if (nodes < 1) return;
    cout << "0  || ";
    for (int i = 1; i <= nodes; i++) {
        cout << i << " | ";
    }
    for (int row = 0; row < nodes; row++) {
        cout << endl << row + 1 << " || ";
        for (int col = 0; col < nodes; col++) {
            if (paths_matrix[row][col] == INF) cout << "#";
            else cout << paths_matrix[row][col];
            cout << " | ";
        }
    }
    cout << endl;
}

template<typename T>
void Graph<T>::print_restored_path() {
    if (restored_path.empty()) {
        cout << "No way" << endl;
        return;
    }
    cout << "The way is";
    for (const auto &i: restored_path) {
        cout << " - " << i + 1;
    }
    cout << endl;
}

////////////////////////////////////////////////
////other functions
////////////////////////////////////////////////

vector<int> random_grid(int nodes, int lower, int upper) {
    uniform_int_distribution<int> distr(lower, upper);
    mt19937 generator;
    vector<int> grid(nodes * nodes);
    for (int i = 0; i < grid.size(); i++) {
        grid[i] = distr(generator);
    }
    for (int i = 0; i < nodes; i++) {
        grid[i * nodes + i] = 0;
    }
    return grid;
}

void example() {
    vector<double> grid = {0, 50.5, 45, 10.09, INF, INF,
                           INF, 0, 10.7, 15, INF, INF,
                           INF, INF, 0, INF, 30.4, INF,
                           10, INF, INF, 0, 15.96, INF,
                           INF, 20.12, 35.62, INF, 0, INF,
                           INF, INF, INF, INF, 3.1, 0};

    cout << "==========================================" << endl;
    cout << "        FLoyd-Warshall algorithm" << endl;
    cout << "==========================================" << endl;
    Graph map_floyd(grid);
    map_floyd.FW_alg_ways();
    cout << endl << "Paths matrix:" << endl;
    map_floyd.print_paths_matrix();
    map_floyd.restore_path(6, 1);
    cout << endl << "From node 6 to 1 ";
    map_floyd.print_restored_path();
    cout << endl;

    cout << "==========================================" << endl;
    cout << "           Dijkstra algorithm" << endl;
    cout << "==========================================" << endl;
    Graph map_dijkstra(grid);
    map_dijkstra.paths_matrix_Dij();
    cout << endl << "Paths matrix:" << endl;
    map_dijkstra.print_paths_matrix();
}

void time_compare() {
    cout << "===================" << endl;
    cout << "    Time Compare   " << endl;
    cout << "===================" << endl;
    cout << "it   F-W      Dijk " << endl;
    for (int i = 3; i <= 250; i++) {
        vector<int> grid = random_grid(i, 0, 1000);
        unsigned int start = 0;
        unsigned int end = 0;
        Graph map_floyd(grid);
        Graph map_dijkstra(grid);

        //measuring time for Floyd-Warshall algorithm
        start = clock();
        map_floyd.FW_clear();
        end = clock();
        unsigned int FW_time = end - start;

        //measuring time for Dijkstra algorithm
        start = clock();
        map_dijkstra.paths_matrix_Dij();
        end = clock();
        unsigned int Dij_time = end - start;
        cout << i << "    " << FW_time << "        " << Dij_time << endl;
    }
}

int main() {

    return 0;
}

