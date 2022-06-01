#include <iostream>
#include "graph.h"
#include <queue> // очередь
#include <stack> // стек

Graph::Graph() {
    num_of_vertices = 0;
}

Graph::Graph(int num_of_vertices) { //пустая матрица смежностей
    this->num_of_vertices = num_of_vertices;
    std::vector<int> row(num_of_vertices, 0);
    for (int i = 0; i < num_of_vertices; ++i) {
        adjacency_matrix.push_back(row);
    }
}

Graph::Graph(std::vector<std::vector<int>>& other_matrix) { //матрица смежности создается на основе исходной матрицы
    num_of_vertices = other_matrix.size();
    adjacency_matrix = other_matrix;
}

Graph::Graph(int sum_of_edges_and_vertices, GraphType type) { //матрица смежностей с разными данными
    switch (type) {
    case RANDOM: //случайная матрица смежностей
        srand(time(NULL));
        // будем рассматривать плотный граф
        num_of_vertices = (-1 + (int)ceil(sqrt(1 + 8.0 * sum_of_edges_and_vertices))) / 2;
        num_of_edges = sum_of_edges_and_vertices - num_of_vertices;

        int num_of_added_edges = 0; //всего ребер добавлено 

        //равномерное заполнение матрицы смежностей
        int num_edge_from_vertices_count = num_of_edges / num_of_vertices + 1;

        for (int v = 0; v < num_of_vertices; v++) {
            std::vector<int> row(num_of_vertices, 0);
            adjacency_matrix.push_back(row);
            for (int w = 0; w < num_edge_from_vertices_count && num_of_added_edges < num_of_edges;) {
                int insert = rand() % num_of_vertices;
                if (adjacency_matrix[v][insert] == 0) {
                    adjacency_matrix[v][insert] = 1;
                    ++w;
                    ++num_of_added_edges;
                }
            }
        }
    }
}

Graph::Graph(const Graph& other_matrix)  //конструктор копирования
{
    num_of_vertices = other_matrix.num_of_vertices;
    adjacency_matrix = other_matrix.adjacency_matrix;
}

Graph::Graph(Graph&& other_matrix) //конструктор перемещения
{
    num_of_vertices = other_matrix.num_of_vertices;
    adjacency_matrix = other_matrix.adjacency_matrix;
}

void Graph::addEdge(int from, int to) {
    adjacency_matrix[from][to] = 1;
    adjacency_matrix[to][from] = 1;
}

void Graph::removeEdge(int from, int to) {
    adjacency_matrix[from][to] = 0;
    adjacency_matrix[to][from] = 0;
}

bool Graph::isEdge(int from, int to) {
    return adjacency_matrix[from][to];
}

int Graph::get_number_of_vertices() { //количество вершин
    return num_of_vertices;
}

int Graph::get_number_of_edges() { //количество ребер
    return num_of_edges;
}

void Graph::print() {
    for (int i = 0; i < num_of_vertices; i++) {
        for (int j = 0; j < num_of_vertices; j++)
            std::cout << adjacency_matrix[i][j] << " ";
        std::cout << "\n";
    }
}

void Graph::bfs_search() {
    //std::cout << "BFS search: ";
    std::vector<int> nodes(num_of_vertices, 0); // вершины графа (0 - все вершины не рассмотрены)
    std::queue<int> Queue;
    Queue.push(0); // помещаем в очередь первую вершину
    while (!Queue.empty()) { // пока очередь не пуста
        int node = Queue.front(); // извлекаем вершину
        Queue.pop();
        nodes[node] = 2; // отмечаем ее как посещенную
        for (int j = 0; j < num_of_vertices; j++) { // проверяем для нее все смежные вершины
            if (adjacency_matrix[node][j] == 1 && nodes[j] == 0) { // если вершина смежная и не обнаружена
                Queue.push(j); // добавляем ее в очередь
                nodes[j] = 1; // отмечаем вершину как обнаруженную
            }
        }
        //std::cout << node << " "; // выводим номер вершины
    }
}

void Graph::dfs_search() {
    //std::cout << "DFS search: ";
    std::vector<int> nodes(num_of_vertices, 0); // вершины графа (0 - все вершины не рассмотрены)
    std::stack<int> Stack;
    Stack.push(0); // помещаем в стек первую вершину
    while (!Stack.empty()) {
        int node = Stack.top(); // извлекаем вершину
        Stack.pop();
        if (nodes[node] == 2) continue;
        nodes[node] = 2; // отмечаем ее как посещенную
        for (int j = num_of_vertices - 1; j >= 0; j--) { // проверяем для нее все смежные вершины
            if (adjacency_matrix[node][j] == 1 && nodes[j] != 2) { // если вершина смежная и не обнаружена
                Stack.push(j); // добавляем ее в cтек
                nodes[j] = 1; // отмечаем вершину как обнаруженную
            }
        }
        //std::cout << node << " "; // выводим номер вершины
    }
}