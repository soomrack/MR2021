#ifndef TARJAN_S_BRIDGE_FINDING_ALGORITHM_GRAPH_H
#define TARJAN_S_BRIDGE_FINDING_ALGORITHM_GRAPH_H

#include <vector>

template<typename T>
T get_inf();

template <typename T>
class Graph {
private:
    std::vector<std::vector<T>> adjacency_matrix;   // Матрица смежности, которая содержит информацию о графе
    bool is_directed = false;                       // Переменная, показывающая, ориентированный ли граф
    T inf;                                          // Условная бесконечность, которая означает отсутствие ребра с таким весом

// Различные приватные переменные, которые могут использовать алгоритмы
// (лучше не захламлять конструкторы их инициализацией)
private:
    int tarjan_s_time = 0;
private:
    int vertices = 0;
    std::vector<std::vector<int>> restore_matrix;   // Матрица для восстановления кратчайшего пути
    std::vector<int> restored_path;                 // Вектор, в котором хранится путь восстановленный методом restore_path

// Конструкторы
public:
    Graph();
    explicit Graph(int num_of_vertices = 0, bool is_directed = false);
    explicit Graph(std::vector<std::vector<T>> &adjacency_matrix, bool is_directed = false);
    explicit Graph(std::vector<T> &adjacency_matrix, bool is_directed = false);
    Graph(const Graph &other);
    Graph(Graph &&other) noexcept;

// Методы для взаимодействия с графом (т.е. геттеры, сеттеры и т.д.)
public:
    void add_edge(int v, int w, int weight = 0);
    // ...

/* Далее следуют наши методы из курсовых работ */

// В качестве примера здесь уже вставлен алгоритм Тарьяна (для поиска мостов), Флойда и Дейкстры
// Список алгоритмов
// *** Место для алгоритмов *** //
public:
    std::vector<std::pair<int, int>> tarjans_find_bridges();
    std::vector<std::vector<T>> Floyd_Warshall();
    std::tuple<std::vector<std::vector<T>>, std::vector<std::vector<int>>> Floyd_Warshall_ways();
    std::vector<std::vector<T>> Dijkstra();

// *** Место для вспомогательных функций *** //
// Вспомогательная приватная рекурсивная функция для алгоритма Тарьяна
private:
    void tarjan_s_bridge_finding_dfs(int u,
                                     std::vector<bool> &visited,
                                     std::vector<int> &disc,
                                     std::vector<int> &low,
                                     std::vector<int> &parent,
                                     std::vector<std::pair<int, int>> &bridges);

// вспомогательные приватные функции для алгоритма Флойда
private:
    T min(int, int, int);
    bool check_adjacency_matrix();

// вспомогательные public функции для алгоритма Флойда
public:
    std::vector<int> restore_path(int from, int to);

// вспомогательные приватные функции для алгоритма Дейкстры
private:
    std::vector<T> Dijkstra_from_one_vertex(int origin);
};


#endif
