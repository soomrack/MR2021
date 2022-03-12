#ifndef TARJAN_S_BRIDGE_FINDING_ALGORITHM_GRAPH_H
#define TARJAN_S_BRIDGE_FINDING_ALGORITHM_GRAPH_H

#include <vector>

template<typename T>
T get_inf();

template <typename T>
class Graph {
private:
    std::vector<std::vector<T>> adjacency_matrix;   // Матрица смежности, которая содержит информацию о графе
    T inf;                                          // Условная бесконечность, которая означает отсутствие ребра
private:
    //матрица для восстановления кратчайшего пути
    std::vector<std::vector<int>> restore_matrix;
    //вектор, в котором хранится путь восстановленный методом restore_path
    std::vector<int> restored_path;

// Различные приватные переменные, которые могут использовать алгоритмы
private:
    int tarjan_s_time = 0;
    int vertices = 0;
    // ...

// Конструкторы
public:
    Graph();
    explicit Graph(int num_of_vertices);
    explicit Graph(std::vector<std::vector<T>> &adjacency_matrix);
    explicit Graph(std::vector<T> &adjacency_matrix);
    Graph(const Graph &other);
    Graph(Graph &&other) noexcept;

// Методы для взаимодействия с графом (т.е. геттеры, сеттеры и т.д.)
public:
    void add_edge(int v, int w, int weight = 0);
    // ...

/* Далее следуют наши методы из курсовых работ */

// В качестве примера здесь уже вставлен алгоритм Тарьяна (для поиска мостов), Флойда и Дейкстры
// Список алгоритмов
// *** Место для ваших алгоритмов *** //
public:
    std::vector<std::pair<int, int>> tarjans_find_bridges();
    std::vector<std::vector<T>> Floyd_Warshall();
    std::tuple<std::vector<std::vector<T>>, std::vector<std::vector<int>>> Floyd_Warshall_ways();
    std::vector<std::vector<T>> Dijkstra();

// *** Место для ваших вспомогательных функций *** //
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
