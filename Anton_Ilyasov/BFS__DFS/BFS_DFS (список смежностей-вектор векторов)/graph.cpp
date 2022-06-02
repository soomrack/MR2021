//#include "pch.h"
#include <iostream>
#include "graph.h"
#include <queue>
#include <stack>
#include <vector>
#include <stdexcept>

Graph::Graph() {
    num_of_vertices = 0;
    num_of_edges = 0;
}

Graph::Graph(int num_of_vertices) { //пустой лист смежностей
    this->num_of_vertices = num_of_vertices;
    adjacency_list = std::vector<std::vector<int>>(num_of_vertices);
}

Graph::Graph(const std::vector<std::vector<int>> &other_list) { //список смежности на основе исходного листа смежности
    num_of_vertices = other_list.size();
    adjacency_list = other_list;
}

Graph::Graph(int sum_of_edges_and_vertices, GraphType type) { //список смежности с разными данными
    if (sum_of_edges_and_vertices <= 0) {
        num_of_edges = 0;
        num_of_vertices = 0;
        adjacency_list = std::vector<std::vector<int>>(0);
    } else if (sum_of_edges_and_vertices == 1) {
        num_of_edges = 0;
        num_of_vertices = 1;
        adjacency_list = std::vector<std::vector<int>>(1);
    } else if (sum_of_edges_and_vertices == 2) {
        num_of_edges = 0;
        num_of_vertices = 2;
        adjacency_list = std::vector<std::vector<int>>(2);
    } else {
        switch (type) {
            case RANDOM: //случайный список смежностей
                //srand(time(NULL));
                srand(1);
                //будем рассматривать плотный граф
                num_of_vertices = (-1 + (int) ceil(sqrt(1 + 8.0 * sum_of_edges_and_vertices))) / 2;
                num_of_edges = sum_of_edges_and_vertices - num_of_vertices;

                int add_edge = 0; //всего ребер добавлено

                adjacency_list = std::vector<std::vector<int>>(num_of_vertices);

                //равномерное заполнение списка смежностей
                int vertice_edge = num_of_edges / num_of_vertices + 1;
                bool add_edge_less_num_edge = true;

                for (int v = 0; v < num_of_vertices && add_edge_less_num_edge; v++) {
                    int add_vertice_edge = 0; //добавлено ребер для вершины
                    bool add_vertice_edge_less_vertice_edge = true;
                    for (int w = (rand() % num_of_vertices);
                         add_vertice_edge_less_vertice_edge && add_edge_less_num_edge;) {
                        if (v != w && !(std::find(adjacency_list[v].begin(), adjacency_list[v].end(), w) !=
                                        adjacency_list[v].end())) {
                            adjacency_list[v].push_back(w);
                            add_edge++;
                            add_vertice_edge++;
                            add_edge_less_num_edge = add_edge < num_of_edges;
                            add_vertice_edge_less_vertice_edge = add_vertice_edge < vertice_edge;
                        }
                        w = (rand() % num_of_vertices);
                    }
                    sort(adjacency_list[v].begin(), adjacency_list[v].end());
                }
        }
    }
}

Graph::Graph(const Graph &other_list) { //конструктор копирования
    num_of_vertices = other_list.num_of_vertices;
    num_of_edges = other_list.num_of_edges;
    adjacency_list = other_list.adjacency_list;
    adjacency_matrix = other_list.adjacency_matrix;
}

Graph::Graph(Graph &&other_list) { //конструктор перемещения
    num_of_vertices = other_list.num_of_vertices;
    num_of_edges = other_list.num_of_edges;
    adjacency_list = other_list.adjacency_list;
    adjacency_matrix = other_list.adjacency_matrix;
}

Graph &Graph::operator=(const Graph &other_list) { //перегрузка оператора присваивания
    if (&other_list == this) {
        return *this;
    }
    num_of_vertices = other_list.num_of_vertices;
    num_of_edges = other_list.num_of_edges;
    adjacency_list = other_list.adjacency_list;
    adjacency_matrix = other_list.adjacency_matrix;
    return *this;
}

void Graph::add_edge(int from, int to) { //добавление однонаправленного ребра
    adjacency_list[from].push_back(to);
    sort(adjacency_list[from].begin(), adjacency_list[from].end());
    num_of_edges++;
}

void Graph::remove_edge(int from, int to) { //удаление однонаправленного ребра
    for (auto it = adjacency_list[from].begin(); it != adjacency_list[from].end();) {
        if (*it == to) {
            it = adjacency_list[from].erase(it);
            break;
        } else
            ++it;
    }
    num_of_edges--;
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
    num_of_edges = 0;
    for (int row_count = 0; row_count < adjacency_list.size(); row_count++) {
        for (int i = 0; i < adjacency_list[row_count].size(); ++i) {
            num_of_edges++;
        }
    }
    return num_of_edges;
}

std::vector<std::vector<int>> Graph::get_adjacency_matrix() { //получить матрицу смежжности по списку смежности
    for (int v = 0; v < num_of_vertices; v++) {
        std::vector<int> row(num_of_vertices, 0);
        for (int i = 0; i < adjacency_list[v].size(); ++i) {
            row[adjacency_list[v][i]] = 1;
        }
        adjacency_matrix.push_back(row);
    }
    return adjacency_matrix;
}

std::vector<std::vector<int>> Graph::get_adjacency_list() { //получить список смежжности
    return adjacency_list;
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

void Graph::print_adjacency_matrix() { //вывод матрицы смежности на экран
    if (adjacency_matrix.size() == 0) {
        std::cout << "Print adjacency matrix error. Adjacency matrix size must be more zero. "
                     "To fix this mistake input x.get_adjacency_matrix(). ";
        return;
    }
    for (int i = 0; i < num_of_vertices; i++) {
        for (int j = 0; j < num_of_vertices; j++)
            std::cout << adjacency_matrix[i][j] << " ";
        std::cout << "\n";
    }
}

void Graph::print_vector(const std::vector<int> vector_to_print) { //вывод вектора
    for (int i = 0; i < vector_to_print.size(); i++) {
        std::cout << vector_to_print[i] << " ";
    }
}

std::vector<int> Graph::bfs_search() {
    std::vector<int> bfs_search;
    std::vector<int> nodes(num_of_vertices, 0); // вершины графа (0 - все вершины не рассмотрены)
    std::queue<int> Queue; // очередь для хранения смежных вершин
    Queue.push(0); // помещаем в очередь первую вершину
    while (!Queue.empty()) { // пока очередь не пуста
        int node = Queue.front(); // извлекаем вершину
        Queue.pop(); // удаляем вершину
        nodes[node] = 2; // отмечаем ее как посещенную
        for (int i = 0; i < adjacency_list[node].size(); ++i) { // выводим все смежные вершины
            if (nodes[adjacency_list[node][i]] == 0) { // если вершина смежная и не обнаружена
                Queue.push(adjacency_list[node][i]); // добавляем ее в очередь
                nodes[adjacency_list[node][i]] = 1; // отмечаем ее как обнаруженную
            }
        }
        bfs_search.push_back(node);
    }
    return bfs_search;
}

std::vector<int> Graph::dfs_search() {
    std::vector<int> dfs_search;
    std::vector<int> nodes(num_of_vertices, 0); // вершины графа (0 - все вершины не рассмотрены)
    std::stack<int> Stack; //стек для хранения смежных вершин
    Stack.push(0); // помещаем в стек первую вершину
    while (!Stack.empty()) { //пока стек не пуст
        int node = Stack.top(); // извлекаем вершину
        Stack.pop(); // удаляем вершину
        if (nodes[node] == 2) continue; // если вершина была посещена, переходим к следующей
        nodes[node] = 2; // отмечаем ее как посещенную
        for (int i = adjacency_list[node].size() - 1; i >= 0; --i) { // проверяем для нее все смежные вершины
            if (nodes[adjacency_list[node][i]] != 2) { // если вершина смежная и не посещена
                Stack.push(adjacency_list[node][i]); // добавляем ее в cтек
                nodes[adjacency_list[node][i]] = 1; // отмечаем вершину как обнаруженную
            }
        }
        dfs_search.push_back(node);
    }
    return dfs_search;
}

std::vector<int> Graph::find_path(int from, int to) {
    if (from >= num_of_vertices || to >= num_of_vertices) { //ошибка, если такой вершины нет
        std::cout << "Find min path error. Index exceeds the number of vertices. Index must be not more "
                  << num_of_vertices - 1 << "\n";
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
    bool path_found = false; //изначально путь не найден
    //здесь путь ищется
    while (!Queue.empty() && !path_found) { //пока есть вершины и путь не найден
        int node = Queue.front();
        Queue.pop();
        nodes[node] = 2; //отмечаем вершину как посещенную
        for (int i = 0; i < adjacency_list[node].size(); ++i) { //перебираем смежные вершины для текущей
            if (nodes[adjacency_list[node][i]] == 0) { // если вершина смежная и не обнаружена
                nodes[adjacency_list[node][i]] = 1; // отмечаем вершину как обнаруженную
                Queue.push(adjacency_list[node][i]); //заносим вершину в очередь
                Edge_beetween_two_vertices.begin = node; //заносим начало ребра
                Edge_beetween_two_vertices.end = adjacency_list[node][i]; //заносим конец ребра
                Edges.push(Edge_beetween_two_vertices); //заносим ребро в стек ребер
                if (adjacency_list[node][i] == to) { //если добрались до нужной вершины, останавливаем перебор вершин
                    path_found = true; //нашли требуемую вершину
                    break; //выходим из цикла
                }
            }
        }
    }
    //здесь путь собирается
    if (path_found) {
        while (to != from) { //перебираем все имеющиеся ребра
            Edge_beetween_two_vertices = Edges.top(); //извлекаем крайнее ребро
            Edges.pop(); //удаляем крайнее ребро
            if (Edge_beetween_two_vertices.end == to) { //если конец ребра ведет в искомую вершину
                to = Edge_beetween_two_vertices.begin; //теперь искомая вершина - начало этого ребра
                restored_path.push_back(Edge_beetween_two_vertices.end); //заносим конец ребра в вектор ответа
            }
        }
        restored_path.push_back(from); //заносим начало пути в вектор ребра
        std::reverse(restored_path.begin(), restored_path.end()); //реверс, чтобы путь шел от from к to
    }
        //вывод сообщения, если пути нет
    else {
        std::cout << "No path from " << from << " to " << to << ".";
    }
    return restored_path;
}

std::vector<int> Graph::topological_sort() {
    //!!!ЗДЕСЬ ТРЕБУЕТСЯ ПРОВЕРКА НА АЦИКЛИЧНОСТЬ ГРАФА!!!

    std::vector<int> nodes(num_of_vertices, 0); // вершины графа (0 - все вершины не рассмотрены)
    std::stack<int> Stack; // стек для хранения смежных вершин
    for (int i = 0; i < num_of_vertices; ++i) { // перебираем все вершины графа
        Stack.push(i); // помещаем в стек вершину
        while (!Stack.empty()) { //пока стек не пуст
            int node = Stack.top(); // извлекаем вершину
            if (nodes[node] == 2) { //если вершина посещена
                Stack.pop(); // удаляем вершину,
                continue; // переходим к следующей;
            }
            if (nodes[node] == 1) { // если вершина была обнаружена
                topological_sorted_graph.push_back(node);
                Stack.pop(); // удаляем вершину,
                nodes[node] = 2; //помечаем как посещенную
                continue; // переходим к следующей;
            }
            nodes[node] = 1; // отмечаем ее как обнаруженную
            bool has_edge = false; // изначально из текущей вершины нет ребер
            for (int i = adjacency_list[node].size() - 1; i >= 0; --i) { // проверяем для нее все смежные вершины
                if (nodes[adjacency_list[node][i]] != 2) { // если вершина смежная и не посещена
                    Stack.push(adjacency_list[node][i]); // добавляем ее в cтек
                    has_edge = true; // есть ребро
                }
            }
            if (!has_edge) { // если из текущей вершины нет ребра
                topological_sorted_graph.push_back(node);
                Stack.pop(); // удаляем вершину
                nodes[node] = 2; //помечаем как посещенную
            }
        }
    }
    std::reverse(topological_sorted_graph.begin(), topological_sorted_graph.end());
    return topological_sorted_graph;
}