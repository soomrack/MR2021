#include <iostream>
#include "graph.h"
#include <queue>
#include <stack>
#include <vector>
#include <list>

Graph::Graph() {
    num_of_vertices = 0;
}

Graph::Graph(int num_of_vertices) { //пустой лист смежностей
    this->num_of_vertices = num_of_vertices;
    adjacency_list = std::vector<std::list<int>>(num_of_vertices);
}

Graph::Graph(std::vector<std::list<int>>& other_list) { //лист смежностей на основе исходного листа смежностей
    num_of_vertices = other_list.size();
    adjacency_list = other_list;
}

Graph::Graph(int sum_of_edges_and_vertices, GraphType type) { //лист смежностей с разными данными
    switch (type)
    {
    case RANDOM: //случайный список смежностей
        srand(time(NULL));
        //будем рассматривать плотный граф
        num_of_vertices = (-1 + (int)ceil(sqrt(1 + 8.0 * sum_of_edges_and_vertices))) / 2;

        int num_of_edges = sum_of_edges_and_vertices - num_of_vertices;
        int num_of_added_edges = 0; //всего ребер добавлено 

        adjacency_list = std::vector<std::list<int>>(num_of_vertices);

        //равномерное заполнение списка смежностей
        int num_edge_from_vertices_count = num_of_edges / num_of_vertices + 1;
        bool num_of_add_edges_less_num_of_edges = true;

        for (int v = 0; v < num_of_vertices && num_of_add_edges_less_num_of_edges; v++) {
            int num_of_added_row_edges = 0; //добавлено ребер для вершины
            bool num_of_added_in_row_edges_less_num_edge_from_vertices_count = true;
            for (int w = (rand() % num_of_vertices); num_of_added_in_row_edges_less_num_edge_from_vertices_count && num_of_add_edges_less_num_of_edges;) {
                if (v != w && !(std::find(adjacency_list[v].begin(), adjacency_list[v].end(), w) != adjacency_list[v].end())) {
                    adjacency_list[v].push_back(w);
                    num_of_added_edges++;
                    num_of_added_row_edges++;
                    num_of_add_edges_less_num_of_edges = num_of_added_edges < num_of_edges;
                    num_of_added_in_row_edges_less_num_edge_from_vertices_count = num_of_added_row_edges < num_edge_from_vertices_count;
                }
                w = (rand() % num_of_vertices);
            }
            adjacency_list[v].sort();
        }
    }
}

Graph::Graph(const Graph& other_list) { //конструктор копирования
    num_of_vertices = other_list.num_of_vertices;
    adjacency_list = other_list.adjacency_list;
}

Graph::Graph(Graph&& other_list) { //конструктор перемещения
    num_of_vertices = other_list.num_of_vertices;
    adjacency_list = other_list.adjacency_list;
}

void Graph::add_edge(int from, int to) { //добавление однонаправленного ребра
    adjacency_list[from].push_back(to);
    adjacency_list[from].sort();
}

void Graph::add_reverse_edge(int from, int to) { //добавление двунаправленного ребра
    adjacency_list[from].push_back(to);
    adjacency_list[to].push_back(from);
    adjacency_list[from].sort();
    adjacency_list[to].sort();
}

void Graph::remove_edge(int from, int to) { //удаление однонаправленного ребра
    adjacency_list[from].remove(to);
}

void Graph::remove_reverse_edge(int from, int to) { //удаление двунаправленного ребра
    adjacency_list[from].remove(to);
    adjacency_list[to].remove(from);
}

bool Graph::is_edge(int from, int to) { //есть ли ребро между вершинами from и to
    for (auto iter = adjacency_list[from].begin(); iter != adjacency_list[from].end(); ++iter) {
        if (*iter == to) return true;
    }
    return false;
}

int Graph::get_number_of_vertices() { //количество вершин
    return num_of_vertices;
}

int Graph::get_number_of_edges() { //количество ребер
    int get_number_of_edges = 0;
    for (int row_count = 0; row_count < adjacency_list.size(); row_count++) {
        for (auto iter = adjacency_list[row_count].begin(); iter != adjacency_list[row_count].end(); ++iter) {
            get_number_of_edges++;
        }
    }
    return get_number_of_edges;
}

void Graph::print() { //вывод списка смежности на экран
    for (int row_count = 0; row_count < adjacency_list.size(); row_count++) {
        std::cout << row_count << ": ";
        for (auto iter = adjacency_list[row_count].begin(); iter != adjacency_list[row_count].end(); ++iter) {
            std::cout << *iter << " ";
        }
        std::cout << std::endl;
    }
}

void Graph::bfs_search() {
    //std::cout << std::endl << "BFS search: ";
    std::vector<int> nodes(num_of_vertices, 0); // вершины графа (0 - все вершины не рассмотрены)
    std::queue<int> Queue;
    Queue.push(0); // помещаем в очередь первую вершину
    while (!Queue.empty()) { // пока очередь не пуста
        int node = Queue.front(); // извлекаем вершину
        Queue.pop();
        nodes[node] = 1; // отмечаем ее как посещенную
        for (auto iter = adjacency_list[node].begin(); iter != adjacency_list[node].end(); ++iter) { // выводим все смежные вершины
            if (nodes[*iter] == 0) { // если вершина смежная и не обнаружена
                Queue.push(*iter); // добавляем ее в очередь
            }
        }
        //std::cout << node << " "; // выводим номер вершины
    }
}

void Graph::dfs_search() {
    //std::cout << std::endl << "DFS search: ";
    std::vector<int> nodes(num_of_vertices, 0); // вершины графа (0 - все вершины не рассмотрены)
    std::stack<int> Stack;
    Stack.push(0); // помещаем в стек первую вершину
    while (!Stack.empty()) {
        int node = Stack.top(); // извлекаем вершину
        Stack.pop();
        if (nodes[node] == 1) continue;
        nodes[node] = 1; // отмечаем ее как посещенную
        for (auto iter = adjacency_list[node].rbegin(); iter != adjacency_list[node].rend(); ++iter) { // выводим все смежные вершины
            if (nodes[*iter] != 1) { // если вершина смежная и не посещена
                Stack.push(*iter); // добавляем ее в cтек
            }
        }
        //std::cout << node << " "; // выводим номер вершины
    }
}