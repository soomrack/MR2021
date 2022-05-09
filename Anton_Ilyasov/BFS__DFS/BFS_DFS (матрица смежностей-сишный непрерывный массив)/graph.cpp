#include <iostream>
#include "graph.h"
#include <queue> // очередь
#include <stack> // стек

Graph::Graph() {
    num_of_vertices = 0;
    adjacency_matrix = nullptr;
    data = nullptr;
}

Graph::Graph(int num_of_vertices) { //пустая матрица смежностей
    this->num_of_vertices = num_of_vertices;
    data = new int[num_of_vertices * num_of_vertices];
    adjacency_matrix = new int* [num_of_vertices];
    for (int i = 0; i < num_of_vertices; i++) {
        adjacency_matrix[i] = &data[i * num_of_vertices];
    }
    for (int i = 0; i < num_of_vertices * num_of_vertices; i++) {
        data[i] = 0;
    }
}

Graph::Graph(int num_of_vertices, const int* other_matrix) { //матрица смежности создается на основе исходной матрицы
    this->num_of_vertices = num_of_vertices;
    data = new int[num_of_vertices * num_of_vertices];
    adjacency_matrix = new int* [num_of_vertices];
    for (int i = 0; i < num_of_vertices; i++) {
        adjacency_matrix[i] = &data[i * num_of_vertices];
    }
    memcpy(data, other_matrix, num_of_vertices * num_of_vertices * sizeof(int));
}

Graph::Graph(int sum_of_edges_and_vertices, GraphType type) { //матрица смежности с разными данными
    switch (type) {
    case RANDOM:
        srand(time(NULL));
        // будем рассматривать плотный граф
        num_of_vertices = (-1 + (int)ceil(sqrt(1 + 8.0 * sum_of_edges_and_vertices))) / 2;

        int num_of_edges = sum_of_edges_and_vertices - num_of_vertices;
        int num_of_added_edges = 0; //всего ребер добавлено 

        //равномерное заполнение матрицы смежностей
        int num_edge_from_vertices_count = num_of_edges / num_of_vertices + 1;

        data = new int[num_of_vertices * num_of_vertices];
        adjacency_matrix = new int* [num_of_vertices];
        for (int i = 0; i < num_of_vertices; i++) {
            adjacency_matrix[i] = &data[i * num_of_vertices];
            for (int j = 0; j < num_of_vertices; j++) {
                adjacency_matrix[i][j] = 0;
            }
            for (int w = 0; w < num_edge_from_vertices_count && num_of_added_edges < num_of_edges;) {
                int insert = rand() % num_of_vertices;
                if (adjacency_matrix[i][insert] == 0) {
                    adjacency_matrix[i][insert] = 1;
                    ++w;
                    ++num_of_added_edges;
                }
            }
        }
    }
}

Graph::Graph(const Graph& other_matrix) { //конструктор копирования
    num_of_vertices = other_matrix.num_of_vertices;
    data = new int[num_of_vertices * num_of_vertices];
    memcpy(data, other_matrix.data, sizeof(int) * num_of_vertices * num_of_vertices);
    adjacency_matrix = new int* [num_of_vertices];
    for (int i = 0; i < num_of_vertices; i++) {
        adjacency_matrix[i] = &data[i * num_of_vertices];
    }
}

Graph::Graph(Graph&& other_matrix) { //Конструктор перемещения
    num_of_vertices = other_matrix.num_of_vertices;
    data = other_matrix.data;
    adjacency_matrix = other_matrix.adjacency_matrix;
    other_matrix.num_of_vertices = 0;
    other_matrix.data = nullptr;
    other_matrix.adjacency_matrix = nullptr;
}

void Graph::addEdge(int i, int j) {
    adjacency_matrix[i][j] = 1;
    adjacency_matrix[j][i] = 1;
}

void Graph::removeEdge(int i, int j) {
    adjacency_matrix[i][j] = 0;
    adjacency_matrix[j][i] = 0;
}

bool Graph::isEdge(int i, int j) {
    return adjacency_matrix[i][j];
}

int Graph::get_number_of_vertices() { //количество вершин
    return num_of_vertices;
}

int Graph::get_number_of_edges() { //количество ребер
    int get_number_of_edges = 0;
    for (int i = 0; i < num_of_vertices; ++i) {
        for (int j = 0; j < num_of_vertices; ++j) {
            if (adjacency_matrix[i][j] == 1) {
                get_number_of_edges++;
            }
        }
    }
    return get_number_of_edges;
}

void Graph::print() {
    for (int i = 0; i < num_of_vertices; i++) {
        for (int j = 0; j < num_of_vertices; j++)
            std::cout << adjacency_matrix[i][j] << " ";
        std::cout << "\n";
    }
}

void Graph::bfs_search() {
    //std::cout << "BFS search:";
    int* nodes = new int[num_of_vertices]; // вершины графа (0 - все вершины не рассмотрены)
    for (int i = 0; i < num_of_vertices; i++) {
        nodes[i] = 0;
    }
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
    delete[] nodes;
    nodes = nullptr;
}

void Graph::dfs_search() {
    //std::cout << "DFS search:";
    int* nodes = new int[num_of_vertices]; // вершины графа (0 - все вершины не рассмотрены)
    for (int i = 0; i < num_of_vertices; i++) {
        nodes[i] = 0;
    }
    std::stack<int> Stack;
    Stack.push(0); // помещаем в стек первую вершину
    while (!Stack.empty()) {
        int node = Stack.top(); // извлекаем вершину
        Stack.pop();
        if (nodes[node] == 2) continue;
        nodes[node] = 2; // отмечаем ее как посещенную
        for (int j = num_of_vertices - 1; j >= 0; j--) { // проверяем для нее все смежные вершины
            if (adjacency_matrix[node][j] == 1 && nodes[j] != 2) { // если вершина смежная и не посещена
                Stack.push(j); // добавляем ее в cтек
                nodes[j] = 1; // отмечаем вершину как обнаруженную
            }
        }
        //::cout << node << " "; // выводим номер вершины
    }
    delete[] nodes;
    nodes = nullptr;
}

Graph::~Graph() {
    delete[] data;
    delete[] adjacency_matrix;
    data = nullptr;
    adjacency_matrix = nullptr;
}