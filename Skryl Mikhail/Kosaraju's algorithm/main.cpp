#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
using namespace std;

class Graph {
private:
    int vertices;
    int tout_counter = 0;
    vector<vector<int>> adj_list;
    vector<vector<int>> reversed;
    vector<bool> visited;
    vector<int> tout;
public:
    explicit Graph(int v);
    void adjacency_list(int u, int v);
    void DFS_recursive();
    bool is_connected(int u, int v);
public:
    void print_list();
private:
    int max_tout();
    void DFS(int u);
    void DFS_reversed(int u);
};

Graph::Graph(int v) {
    vertices = v;
    for (int i = 0; i < vertices; ++i) {
        visited.push_back(false);
        tout.push_back(0);
        adj_list.emplace_back();
        reversed.emplace_back();
    }
}

void Graph::adjacency_list(int u, int v) {
    adj_list[u].push_back(v);
    reversed[v].push_back(u);
}

void Graph::DFS_recursive() {
    for (int i = 0; i < vertices; ++i) {
        if (!visited[i]) {
            DFS(i);
        }
    }
    DFS_reversed(max_tout());
}

void Graph::DFS(int u) {
    tout_counter++;
    visited[u] = true;
    for (auto & i: adj_list[u]) {
        if (!visited[i]) {
            DFS(i);
            tout_counter++;
        }
    }
    tout[u] = tout_counter;
}

int Graph::max_tout() {
    int max = 0;
    int max_vert = 0;
    for (int i = 0; i < tout.size(); ++i) {
        if (tout[i] > max) {
            max = tout[i];
            max_vert = i;
        }
    }
    tout.erase(tout.begin() + max_vert);
    tout.insert(tout.begin() + max_vert, 0);
    return max_vert;
}

void Graph::DFS_reversed(int u) {
    visited[u] = false;
    cout << u << "  ";
    for (auto &i: reversed[u]) {
        if (visited[i]) {
            tout.erase(tout.begin() + i);
            tout.insert(tout.begin() + i, 0);
            DFS_reversed(i);
        }
    }
    for (auto const & i: visited) {
        if (i) {
            cout << endl;
            DFS_reversed(max_tout());
        }
    }
}

bool Graph::is_connected(int u, int v) {
    if (!adj_list[u].empty()) {
        if (find(adj_list[u].begin(), adj_list[u].end(), v) != adj_list[u].end()) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

void rand_list() {
    srand(time(nullptr));
    int vertices = rand() % 20;
    Graph g(vertices);
    int edges = rand() % (vertices);
    cout << endl << "V + E = " << edges + vertices << endl;
    for (int i = 0; i < edges; ++i) {
        int u = 0;
        int v = 0;
        do {
            u = rand() % vertices;
            v = rand() % vertices;
        } while ((u >= vertices) || (v >= vertices) || (u == v) || (g.is_connected(u,v)));
        g.adjacency_list(u, v);
    }
    g.print_list();
    //auto start = chrono::steady_clock::now();
    g.DFS_recursive();
    //g.DFS_reversed(g.max_tout());
    /*auto end = chrono::steady_clock::now();
    auto ms = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << endl << "Time: " << ms.count() << endl;
    cout << vertices << endl;
    cout << (double)((double)ms.count()/(vertices )) << endl;*/
}

void Graph::print_list() {
    for (int i = 0; i < vertices; ++i) {
        cout << i << "->";
        for (auto j: adj_list[i]) {
            cout << j << "->";
        }
        cout << endl;
    }
}

int main() {
    //rand_list();
    Graph gr(8);
    gr.adjacency_list(0, 1);
    gr.adjacency_list(1, 2);
    gr.adjacency_list(2, 3);
    gr.adjacency_list(3, 0);
    gr.adjacency_list(2, 4);
    gr.adjacency_list(4, 5);
    gr.adjacency_list(5, 6);
    gr.adjacency_list(6, 4);
    gr.adjacency_list(6, 7);
    gr.DFS_recursive();
    return 0;
}
