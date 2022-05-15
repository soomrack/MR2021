#include <iostream>
#include "graph.h"
#include <queue>
#include <stack>
#include <vector>

Graph::Graph() {
    num_of_vertices = 0;
    num_of_edges = 0;
}

Graph::Graph(int num_of_vertices) { //пустой лист смежностей
    this->num_of_vertices = num_of_vertices;
    adjacency_list = std::vector<std::vector<int>>(num_of_vertices);
}

Graph::Graph(std::vector<std::vector<int>>& other_list) { //лист смежностей на основе исходного листа смежностей
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
        num_of_edges = sum_of_edges_and_vertices - num_of_vertices;

        int num_of_added_edges = 0; //всего ребер добавлено 

        adjacency_list = std::vector<std::vector<int>>(num_of_vertices);

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
            sort(adjacency_list[v].begin(), adjacency_list[v].end());
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
    sort(adjacency_list[from].begin(), adjacency_list[from].end());
}

void Graph::remove_edge(int from, int to) { //удаление однонаправленного ребра
    for (auto it = adjacency_list[from].begin(); it != adjacency_list[from].end(); )
    {
        if (*it == to)
        {
            it = adjacency_list[from].erase(it);
            break;
        }
        else
            ++it;
    }
}

bool Graph::is_edge(int from, int to) { //есть ли ребро между вершинами from и to
    for (int i = 0; i < adjacency_list[from].size(); ++i) {
        if (adjacency_list[from][i] == to) return true;
    }
    return false;
}

int Graph::get_number_of_vertices() { //количество вершин
    return num_of_vertices;
}

int Graph::get_number_of_edges() { //количество ребер
    return num_of_edges;
}

std::vector<std::vector<int>> Graph::get_adjacency_matrix() { //получить матрицу смежжности по списку смежности
    for (int v = 0; v < num_of_vertices; v++) {
        std::vector<int> row(num_of_vertices, 0);
        adjacency_matrix.push_back(row);
        for (int i = 0; i < adjacency_list[v].size(); ++i) {
            adjacency_matrix[v][adjacency_list[v][i]] = 1;
        }
    }
    return adjacency_matrix;
}

void Graph::print_adjacency_list() { //вывод списка смежности на экран
    for (int row_count = 0; row_count < adjacency_list.size(); row_count++) {
        std::cout << row_count << ": ";
        for (int i = 0; i < adjacency_list[row_count].size(); ++i) {
            std::cout << adjacency_list[row_count][i] << " ";
        }
        std::cout << std::endl;
    }
}

void Graph::print_adjacency_matrix() { //вывод списка смежности на экран
    if (adjacency_matrix.size() == 0) {
        std::cout << "Print adjacency matrix error. Adjacency matrix size must be more zero"
                     "To fix this mistake input x.get_adjacency_matrix()";
        return;
    }
    for (int i = 0; i < num_of_vertices; i++) {
        for (int j = 0; j < num_of_vertices; j++)
            std::cout << adjacency_matrix[i][j] << " ";
        std::cout << "\n";
    }
}

void Graph::print_vector(std::vector<int> vector_to_print) { //вывод вектора
    for (int i = 0; i < vector_to_print.size(); i++) {
        std::cout << vector_to_print[i] << " ";
    }
}

void Graph::bfs_search() {
    std::cout << std::endl << "BFS search: ";
    std::vector<int> nodes(num_of_vertices, 0); // вершины графа (0 - все вершины не рассмотрены)
    std::queue<int> Queue; // очередь для хранения смежных вершин
    Queue.push(0); // помещаем в очередь первую вершину
    while (!Queue.empty()) { // пока очередь не пуста
        int node = Queue.front(); // извлекаем вершину
        Queue.pop(); // удаляем вершину
        nodes[node] = 1; // отмечаем ее как посещенную
        for (int i = 0; i < adjacency_list[node].size(); ++i) { // выводим все смежные вершины
            if (nodes[adjacency_list[node][i]] == 0) { // если вершина смежная и не обнаружена
                Queue.push(adjacency_list[node][i]); // добавляем ее в очередь
            }
        }
        std::cout << node << " "; // выводим номер вершины
    }
}

void Graph::dfs_search() {
    std::cout << std::endl << "DFS search: ";
    std::vector<int> nodes(num_of_vertices, 0); // вершины графа (0 - все вершины не рассмотрены)
    std::stack<int> Stack; //стек для хранения смежных вершин
    Stack.push(0); // помещаем в стек первую вершину
    while (!Stack.empty()) { //перебираем все имеющиеся смежные вершины
        int node = Stack.top(); // извлекаем вершину
        Stack.pop(); // удаляем вершину
        if (nodes[node] == 1) continue; // если вершина была посещена, переходим к следующей
        nodes[node] = 1; // отмечаем ее как посещенную
        for (int i = adjacency_list[node].size() - 1; i >= 0; --i) { // выводим все смежные вершины
            if (nodes[adjacency_list[node][i]] != 1) { // если вершина смежная и не посещена
                Stack.push(adjacency_list[node][i]); // добавляем ее в cтек
            }
        }
        std::cout << node << " "; // выводим номер вершины
    }
}

std::vector<int> Graph::find_path(const int from, const int to) {
    if (from > num_of_vertices || to > num_of_vertices) { //ошибка, если такой вершины нет
        std::cout << "Find min path error. Index exceeds the number of vertices. Index must be not more " << num_of_vertices - 1 << "\n";
        return restored_path;
    }
    if (from == to) { //ошибка, если вход = выход
        std::cout << "Find min path error. Check entrance and exit.";
        return restored_path;
    }
    std::vector<int> nodes(num_of_vertices, 0); // вершины графа (0 - все вершины не рассмотрены)
    std::queue<int> Queue; //здесь хранятся все смежные вершины
    struct Edge { //структура для ребра
        int begin;
        int end;
    };
    Edge Edge_beetween_two_vertices; //ребро с двумя параметрами
    std::stack<Edge> Edges; //список ребер
    Queue.push(from); //заносим исходную вершину
    bool find = false; //изначально путь не найден
    while (!Queue.empty() && !find) { //пока есть смежные вершины и путь не найден
        int node = Queue.front();
        Queue.pop();
        nodes[node] = 1; //вершина посещена
        for (int i = 0; i < adjacency_list[node].size(); ++i) { //перебираем смежные вершины для текущей
            if (nodes[adjacency_list[node][i]] == 0) { //если вершина не была посещена
                Queue.push(adjacency_list[node][i]); //заносим вершину в очередь
                Edge_beetween_two_vertices.begin = node; //заносим начало ребра
                Edge_beetween_two_vertices.end = adjacency_list[node][i]; //заносим конец ребра
                Edges.push(Edge_beetween_two_vertices); //заносим ребро в стек ребер
                if (adjacency_list[node][i] == to) { //если добрались до нужной вершины, останавливаем перебор вершин
                    find = true; //нашли требуемую вершину
                    break; //выходим из цикла
                }
            }
        }
    }
    //здесь путь собирается
    if (find) {
        int update_to = to;
        while (update_to != from && !Edges.empty()) { //перебираем все имеющиеся ребра
            Edge_beetween_two_vertices = Edges.top(); //извлекаем крайнее ребро
            Edges.pop(); //удаляем крайнее ребро
            if (Edge_beetween_two_vertices.end == update_to) { //если конец ребра ведет в искомую вершину
                update_to = Edge_beetween_two_vertices.begin; //теперь искомая вершина - начало этого ребра
                restored_path.push_back(Edge_beetween_two_vertices.end); //заносим конец ребра в вектор ответа
            }
        }
        restored_path.push_back(from); //заносим начало пути в вектор ребра
        std::reverse(restored_path.begin(), restored_path.end()); //реверс, чтобы путь шел от from к to
        //вывод пути на экран
        std::cout << "Min path from " << from << " to " << to << " : ";
        for (int i = 0; i < restored_path.size(); ++i) {
            std::cout << restored_path[i] << " ";
        }
        std::cout << "\n";
    }
    //вывод сообщения, если пути нет
    else {
        std::cout << "No path from " << from << " to " << to << ".";
    }
    return restored_path;
}

std::vector<int> Graph::topological_sort() {
    std::vector<int> nodes(num_of_vertices, 0); // вершины графа (0 - все вершины не рассмотрены)
    std::stack<int> Stack; // стек для хранения смежных вершин

    for (int i = 0; i < num_of_vertices; ++i) { // перебираем все вершины графа
        if (nodes[i] == 0) { // если вершина не была посещена
            Stack.push(i); // посещаем вершину
            while (!Stack.empty()) { // перебираем все имеющиеся смежные вершины
                int node = Stack.top(); // извлекаем вершину
                if (nodes[node] == 1) { // если вершина была посещена...
                    topological_sorted_graph.push_back(node);
                    Stack.pop(); // удаляем вершину,
                    continue; // переходим к следующей;
                }
                nodes[node] = 1; // отмечаем виршину как посещенную
                bool has_edge = false; // изначально из текущей вершины нет ребер
                for (int i = adjacency_list[node].size() - 1; i >= 0; --i) { // выводим все смежные вершины
                    if (nodes[adjacency_list[node][i]] != 1) { // если вершина смежная и не посещена
                        Stack.push(adjacency_list[node][i]); // добавляем ее в cтек
                        has_edge = true; // есть ребро
                    }
                }
                if (!has_edge) { // если из текущей вершины нет ребра
                    topological_sorted_graph.push_back(node);
                    Stack.pop(); // удаляем вершину
                }
            }
        }
    }
    std::reverse(topological_sorted_graph.begin(), topological_sorted_graph.end());
    return topological_sorted_graph;
}