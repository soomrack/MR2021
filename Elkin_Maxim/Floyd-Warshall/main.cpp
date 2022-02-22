#include <iostream>
#include <vector>
#include <cmath>
#include <tuple>
#include <random>

#define INF numeric_limits<int>::max()
using namespace std;

template<class T>
class Floyd {
public:
    explicit Floyd(vector<T> &);

    vector<T> FW_clear();

    tuple<vector<T>, vector<int>> FW_alg_ways();

    vector<int> restore_path(int, int);

    vector<T> get_paths_matrix() { return paths_matrix; };

    vector<int> get_restore_matrix() { return restore_matrix; };

    vector<int> get_restored_path() { return restored_path; };

    vector<T> get_dist_matrix() { return dist_matrix; };

    void print_restored_path();

private:
    int nodes;
    vector<T> dist_matrix;
    vector<T> paths_matrix;
    vector<int> restore_matrix;
    vector<int> restored_path;

    T min(int, int, int);
};

template<class T>
class Dijkstra {
public:
    explicit Dijkstra(vector<T> &);

    vector<T> Dijkstra_alg(int);

    vector<T> paths_matrix_Dij();

    vector<T> get_paths_matrix() { return paths_matrix; };

    vector<T> get_shortest_distances() { return shortest_distances; };

    vector<T> get_dist_matrix() { return dist_matrix; };
private:
    int nodes;
    vector<T> dist_matrix;
    vector<T> paths_matrix;
    vector<T> shortest_distances;
};

////////////////////////////////////////////////
////other functions
////////////////////////////////////////////////

template<typename T>
bool check_dist_matrix(vector<T> &grid) {
    //Checking matrix to be square
    if (grid.size() != pow((int) sqrt(grid.size()), 2)) {
        return false;
    }
    int nodes = (int) sqrt(grid.size());
    // Checking diagonal to be zero
    for (int node = 0; node < nodes; node++) {
        if (grid[(node * nodes) + node] != 0) {
            return false;
        }
    }
    return true;
}

template<typename T>
void print_paths_matrix(vector<T> grid) {
    int nodes = (int) sqrt(grid.size());
    if (nodes < 1) return;
    cout << "  || ";
    for (int i = 1; i <= nodes; i++) {
        cout << i << " | ";
    }
    cout << endl;
    for (int i = 0; i < grid.size(); i++) {
        if ((i % nodes) == 0) cout << endl << i / nodes + 1 << " || ";
        if (grid[i] == INF) cout << "#";
        else cout << grid[i];
        cout << " | ";
    }
    cout << endl;
}

vector<int> random_grid(int nodes, int lower, int upper) {
    uniform_int_distribution<int> distr(lower, upper);
    mt19937 generator;
    vector<int> grid(nodes * nodes, 0);
    for (int i = 0; i < grid.size(); i++) {
        grid[i] = distr(generator);
    }
    for (int i = 0; i < nodes; i++) {
        grid[i * nodes + i] = 0;
    }
    return grid;
}

void example() {
    //Examples of grids

    //0, 3, INF, 5,
    //INF, 0, INF, INF,
    //INF, -10, 0, -INF,
    //INF, INF, 2, 0

    //{0, 50, 45, 10, INF, INF,
    //INF, 0, 10, 15, INF, INF,
    //INF, INF, 0, INF, 30, INF,
    //10, INF, INF, 0, 15, INF,
    //INF, 20, 35, INF, 0, INF,
    //INF, INF, INF, INF, 3, 0};

    //0, 3, INF, 7,
    //8, 0, 2, INF,
    //5, INF, 0, 1,
    //2, INF, INF, 0

    vector<double> grid = {0, 50.5, 45, 10.09, INF, INF,
                           INF, 0, 10.7, 15, INF, INF,
                           INF, INF, 0, INF, 30.4, INF,
                           10, INF, INF, 0, 15.96, INF,
                           INF, 20.12, 35.62, INF, 0, INF,
                           INF, INF, INF, INF, 3.1, 0};

    cout << "==========================================" << endl;
    cout << "        FLoyd-Warshall algorithm" << endl;
    cout << "==========================================" << endl;
    Floyd map_floyd(grid);
    map_floyd.FW_alg_ways();
    cout << endl << "Paths matrix:" << endl;
    print_paths_matrix(map_floyd.get_paths_matrix());
    cout << endl << "Restore matrix:" << endl;
    print_paths_matrix(map_floyd.get_restore_matrix());
    map_floyd.restore_path(6, 1);
    cout << endl << "From node 6 to 1 ";
    map_floyd.print_restored_path();
    cout << endl;

    cout << "==========================================" << endl;
    cout << "           Dijkstra algorithm" << endl;
    cout << "==========================================" << endl;
    Dijkstra map_dijkstra(grid);
    map_dijkstra.paths_matrix_Dij();
    cout << endl << "Paths matrix:" << endl;
    print_paths_matrix(map_dijkstra.get_paths_matrix());
}

void time_compare() {
    cout << "===================" << endl;
    cout << "    Time Compare   " << endl;
    cout << "===================" << endl;
    cout << "it   F-W      Dijk " << endl;
    for (int i = 3; i <= 150; i++) {
        vector<int> grid = random_grid(i, 0, 1000);
        unsigned int start = 0;
        unsigned int end = 0;
        Floyd map_floyd(grid);
        Dijkstra map_dijkstra(grid);

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

////////////////////////////////////////////////
////Class Floyd
////////////////////////////////////////////////

template<typename T>
Floyd<T>::Floyd(vector<T> &grid) {
    dist_matrix = grid;
    nodes = (int) sqrt(grid.size());
}

//Floyd-Warshall algorithm without restore matrix
template<typename T>
vector<T> Floyd<T>::FW_clear() {
// Checking correct input of the matrix
    if (!check_dist_matrix(dist_matrix)) {
        vector<T> zero;
        return zero;
    }
    paths_matrix = dist_matrix;
    // Floyd-Warshall algorithm realization
    for (int intermediate = 0; intermediate < nodes; intermediate++) {
        for (int origin = 0; origin < nodes; origin++) {
            for (int destination = 0; destination < nodes; destination++) {
                //let paths_matrix = A, then
                //A(k)[x,y] = min(A(k-1)[x,y], A(k-1)[x,k] + A(k-1)[k,y])
                if (paths_matrix[origin * nodes + destination] > min(origin, destination, intermediate)) {
                    paths_matrix[origin * nodes + destination] = min(origin, destination, intermediate);
                }
            }
        }
    }
    return paths_matrix;
}

//Floyd-Warshall algorithm with restore matrix
template<typename T>
tuple<vector<T>, vector<int>> Floyd<T>::FW_alg_ways() {
    // Checking correct input of the matrix
    if (!check_dist_matrix(dist_matrix)) {
        vector<T> zero0;
        vector<int> zero;
        return make_tuple(zero0, zero);
    }
    paths_matrix = dist_matrix;
    //initializing vector to restore the paths
    restore_matrix.resize(dist_matrix.size());
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            if (paths_matrix[i * nodes + j] == INF) {
                restore_matrix[i * nodes + j] = 0;
            } else
                restore_matrix[i * nodes + j] = j + 1;
        }
    }
    // Floyd-Warshall algorithm realization
    for (int intermediate = 0; intermediate < nodes; intermediate++) {
        for (int origin = 0; origin < nodes; origin++) {
            for (int destination = 0; destination < nodes; destination++) {
                //let paths_matrix = A, then
                //A(k)[x,y] = min(A(k-1)[x,y], A(k-1)[x,k] + A(k-1)[k,y])
                if (paths_matrix[origin * nodes + destination] > min(origin, destination, intermediate)) {
                    paths_matrix[origin * nodes + destination] = min(origin, destination, intermediate);
                    //saving previous nodes to restore paths
                    restore_matrix[origin * nodes + destination] = restore_matrix[origin * nodes + intermediate];
                }
            }
        }
    }
    //Check for negative cycle
    for (int node = 0; node < nodes; node++) {
        if (paths_matrix[node * nodes + node] < 0) {
            paths_matrix.clear();
            vector<int> zero;
            cout << "negr" << endl;
            return make_tuple(paths_matrix, zero);
        }
    }
    return make_tuple(paths_matrix, restore_matrix);
}

//prints the shortest way from restored path
template<typename T>
void Floyd<T>::print_restored_path() {
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

//uses restore_matrix from FW_alg to restore paths
template<typename T>
vector<int> Floyd<T>::restore_path(int from, int to) {
    if ((nodes < from) || (nodes < to)) {
        vector<int> zero;
        return zero;
    }
    if (paths_matrix[from * nodes + to] == INF) {
        vector<int> zero;
        return zero;
    }
    //vector to store the path (nodes)
    int current = from - 1;
    int destination = to - 1;
    while (current != destination) {
        restored_path.push_back(current);
        current = restore_matrix[current * nodes + destination] - 1;
        if (current < 0) {
            restored_path.clear();
            return restored_path;
        }
    }
    restored_path.push_back(current);
    return restored_path;
}

template<typename T>
T Floyd<T>::min(int origin, int destination, int intermediate) {
    T actual = paths_matrix[origin * nodes + destination];
    T alternative = 0;
    if (paths_matrix[origin * nodes + intermediate] == INF || paths_matrix[nodes * intermediate + destination] == INF) {
        alternative = INF;
    } else alternative = paths_matrix[origin * nodes + intermediate] + paths_matrix[nodes * intermediate + destination];
    if (actual > alternative) return alternative;
    else return actual;
}

////////////////////////////////////////////////
////Class Dijkstra
////////////////////////////////////////////////

template<typename T>
Dijkstra<T>::Dijkstra(vector<T> &grid) {
    dist_matrix = grid;
    nodes = (int) sqrt(grid.size());
}

template<typename T>
vector<T> Dijkstra<T>::Dijkstra_alg(int origin) {
    origin--;
    // Checking correct input of the matrix and origin
    if ((!check_dist_matrix(dist_matrix)) || (origin > nodes)) {
        vector<T> zero;
        return zero;
    }
    //vector to store passed nodes
    vector<int> passed;
    //vector to store the shortest distance from origin to all nodes
    shortest_distances.resize(nodes);
    //initializing vectors
    passed.push_back(origin + 1);
    for (int node = 0; node < nodes; node++) {
        shortest_distances[node] = dist_matrix[origin * nodes + node];
    }
    //Dijkstra algorithm realization
    for (int in_cln = 1; in_cln < nodes; in_cln++) {
        int min = INF;
        int next_node = -1;
        //Finding the nearest node
        for (int node = 0; node < nodes; node++) {
            //We can't go through passed nodes
            bool skip = false;
            for (const auto i: passed) {
                if ((node + 1) == i) {
                    skip = true;
                }
            }
            if (!skip) {
                if (min > shortest_distances[node]) {
                    min = shortest_distances[node];
                    next_node = node + 1;
                }
            }
        }
        if (next_node == -1) return shortest_distances;
        passed.push_back(next_node);
        //Finding the shortest paths through this node
        for (int node = 0; node < nodes; node++) {
            // We can't go through passed nodes
            bool skip = false;
            for (const auto i: passed) {
                if ((node + 1) == i) {
                    skip = true;
                }
            }
            if (!skip) {
                if (dist_matrix[(next_node - 1) * nodes + node] != INF) {
                    if (min + dist_matrix[(next_node - 1) * nodes + node] < shortest_distances[node]) {
                        shortest_distances[node] = min + dist_matrix[(next_node - 1) * nodes + node];
                    }
                }
            }
        }
    }
    return shortest_distances;
}

//Performs Dijkstra algorithm for every node to make paths matrix
template<typename T>
vector<T> Dijkstra<T>::paths_matrix_Dij() {
    for (int i = 1; i <= nodes; i++) {
        Dijkstra_alg(i);
        paths_matrix.insert(paths_matrix.end(), shortest_distances.begin(), shortest_distances.end());
    }
    return paths_matrix;
}

int main() {
    example();
    return 0;
}