#ifndef TARJAN_S_BRIDGE_FINDING_ALGORITHM_GRAPH_H
#define TARJAN_S_BRIDGE_FINDING_ALGORITHM_GRAPH_H

#include <vector>

class Graph {
// Матрица смежности, которая содержит информацию о графе
private:
    std::vector<std::vector<int>> adjacency_matrix;

// Различные приватные переменные, которые могут использовать алгоритмы
private:
    int tarjan_s_time = 0;
    // ...

// Конструкторы
public:
    Graph();
    explicit Graph(int num_of_vertices);
    explicit Graph(std::vector<std::vector<int>> &adjacency_matrix);
    Graph(const Graph &other);
    Graph(Graph &&other) noexcept;

// Методы для взаимодействия с графом (т.е. геттеры, сеттеры и т.д.)
public:
    void add_edge(int v, int w, int weight = 0);
    // ...

/* Далее следуют наши методы из курсовых работ */

// В качестве примера здесь уже вставлен алгоритм Тарьяна для поиска мостов,
// а также вспомогательная приватная рекурсивная функция
public:
    std::vector<std::pair<int, int>> tarjans_find_bridges();
private:
    void tarjan_s_bridge_finding_dfs(int u,
                                     std::vector<bool> &visited,
                                     std::vector<int> &disc,
                                     std::vector<int> &low,
                                     std::vector<int> &parent,
                                     std::vector<std::pair<int, int>> &bridges);

// *** Место для ваших алгоритмов *** //
};

#endif
