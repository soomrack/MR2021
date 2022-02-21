#include <iostream>
#include <vector>
#include <cmath>
#include <tuple>
#include <ctime>

#define INF numeric_limits<int>::max()
using namespace std;

class Floyd {
public:
    explicit Floyd(vector<int> &);

    vector<int> FW_clear();

    tuple<vector<int>, vector<int>> FW_alg_ways();

    vector<int> restore_path(int, int);

    vector<int> get_paths_matrix() { return paths_matrix; };

    vector<int> get_restore_matrix() { return restore_matrix; };

    void print_restored_path();

private:
    int nodes;
    vector<int> dist_matrix;
    vector<int> paths_matrix;
    vector<int> restore_matrix;
    vector<int> restored_path;

    int min(int, int, int);
};

class Dijkstra {
public:
    explicit Dijkstra(vector<int> &);

    vector<int> Dijkstra_alg(int);

    vector<int> paths_matrix_Dij();

    vector<int> get_paths_matrix() { return paths_matrix; };

    vector<int> get_shortest_distances() { return shortest_distances; };
private:
    int nodes;
    vector<int> dist_matrix;
    vector<int> paths_matrix;
    vector<int> shortest_distances;
};

////////////////////////////////////////////////
////other functions
////////////////////////////////////////////////

bool check_dist_matrix(vector<int> &grid) {
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

void print_paths_matrix(vector<int> grid) {
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

vector<int> random_grid(int nodes) {
    vector<int> grid(nodes * nodes, 0);
    srand(time(nullptr));
    for (int i = 0; i < grid.size(); i++) {
        grid[i] = rand() % 100;
    }
    for (int i = 0; i < nodes; i++) {
        grid[i * nodes + i] = 0;
    }
    return grid;
}

void example() {
    vector<int> grid = {0, 50, 45, 10, INF, INF,
                        INF, 0, 10, 15, INF, INF,
                        INF, INF, 0, INF, 30, INF,
                        10, INF, INF, 0, 15, INF,
                        INF, 20, 35, INF, 0, INF,
                        INF, INF, INF, INF, 3, 0};

    cout << "==========================================" << endl;
    cout << "        FLoyd-Warshall algorithm" << endl;
    cout << "==========================================" << endl;
    Floyd map_floyd(grid);
    map_floyd.FW_alg_ways();
    map_floyd.restore_path(6, 1);
    cout << endl << "Paths matrix:" << endl;
    print_paths_matrix(map_floyd.get_paths_matrix());
    cout << endl << "Restore matrix:" << endl;
    print_paths_matrix(map_floyd.get_restore_matrix());
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
        vector<int> grid = random_grid(i);
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

Floyd::Floyd(vector<int> &grid) {
    dist_matrix = grid;
    nodes = (int) sqrt(grid.size());
}

//Floyd-Warshall algorithm without restore matrix
vector<int> Floyd::FW_clear() {
// Checking correct input of the matrix
    if (!check_dist_matrix(dist_matrix)) {
        vector<int> zero;
        return zero;
    }
    paths_matrix = dist_matrix;
    // Floyd-Warshall algorithm realization
    for (int intermediate = 0; intermediate < nodes; intermediate++) {
        for (int origin = 0; origin < nodes; origin++) {
            for (int destination = 0; destination < nodes; destination++) {
                //let paths_matrix = A, then
                //A(k)[x,y] = min(A(k-1)[x,y], A(k-1)[x,k] + A(k-1)[k,y])
                paths_matrix[origin * nodes + destination] = min(destination, origin, intermediate);
            }
        }
    }
    return paths_matrix;
}

//Floyd-Warshall algorithm with restore matrix
tuple<vector<int>, vector<int>> Floyd::FW_alg_ways() {
    // Checking correct input of the matrix
    if (!check_dist_matrix(dist_matrix)) {
        vector<int> zero;
        return make_tuple(zero, zero);
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
            cout << "negr" << endl;
            return make_tuple(paths_matrix, paths_matrix);
        }
    }
    return make_tuple(paths_matrix, restore_matrix);
}

//prints the shortest way from restored path
void Floyd::print_restored_path() {
    if (restored_path.empty()) {
        cout << "No way" << endl;
        return;
    }
    cout << "The way is";
    for (int i = 0; i < restored_path.size(); i++) {
        cout << " - " << restored_path[i] + 1;
    }
    cout << endl;
}

//uses restore_matrix from FW_alg to restore paths
vector<int> Floyd::restore_path(int from, int to) {
    if ((nodes < from) || (nodes < to)) {
        restored_path.clear();
        return restored_path;
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

int Floyd::min(int origin, int destination, int intermediate) {
    int actual = paths_matrix[origin * nodes + destination];
    int alternative = 0;
    if (paths_matrix[origin * nodes + intermediate] == INF || paths_matrix[nodes * intermediate + destination] == INF) {
        alternative = INF;
    } else alternative = paths_matrix[origin * nodes + intermediate] + paths_matrix[nodes * intermediate + destination];
    if (actual > alternative) return alternative;
    else return actual;
}

////////////////////////////////////////////////
////Class Dijkstra
////////////////////////////////////////////////

Dijkstra::Dijkstra(vector<int> &grid) {
    dist_matrix = grid;
    nodes = (int) sqrt(grid.size());
}

vector<int> Dijkstra::Dijkstra_alg(int origin) {
    origin--;
    // Checking correct input of the matrix and origin
    if ((!check_dist_matrix(dist_matrix)) || (origin > nodes)) {
        vector<int> zero;
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
            for (int i = 0; i < passed.size(); i++) {
                if ((node + 1) == passed[i]) {
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
            for (int i = 0; i < passed.size(); i++) {
                if ((node + 1) == passed[i]) {
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
vector<int> Dijkstra::paths_matrix_Dij() {
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