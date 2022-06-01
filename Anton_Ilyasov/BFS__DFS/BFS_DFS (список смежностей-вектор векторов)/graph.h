#ifndef BFS_AND_DFS_H
#define BFS_AND_DFS_H
#include <vector>

typedef enum {
    RANDOM
} GraphType;

class Graph {
private:
    int num_of_vertices; //количество вершин
    int num_of_edges; //количество ребер
    std::vector<std::vector<int>> adjacency_list; //Список смежности
    std::vector<std::vector<int>> adjacency_matrix;//Матрица смежности
    std::vector<int> restored_path; //путь между двумя вершинами
    std::vector<int> topological_sorted_graph; //топологически отсортированный граф
public:
    Graph();
    Graph(int num_of_vertices);
    Graph(const std::vector<std::vector<int>>& other_list);
    Graph(int sum_of_edges_and_vertices, GraphType type);
    Graph(const Graph& other_list);
    Graph(Graph&& other_list);
    Graph& operator =(const Graph& other_matrix);
public:
    void add_edge(int from, int to);
    void remove_edge(int from, int to);
    void print_adjacency_list();
    void print_adjacency_matrix();
    void print_vector(std::vector<int> vector_to_print);
    bool is_edge(int from, int to);
    int get_number_of_vertices();
    int get_number_of_edges();
    std::vector<std::vector<int>> get_adjacency_matrix();
    std::vector<std::vector<int>> get_adjacency_list();
public:
    std::vector<int> bfs_search();
    std::vector<int> dfs_search();
    std::vector<int> find_path(int from, int to);
    std::vector<int> topological_sort();
};

#endif