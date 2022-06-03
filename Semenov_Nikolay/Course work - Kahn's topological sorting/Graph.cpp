#include "Graph.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <ctime>

Graph::Graph() {
    sumVertices = 0;
    sumEdges = 0;
}

Graph::Graph(int sumVertices) {                                                            // Конструктор пустого листа смежностей
    this->sumVertices = sumVertices;
    adjList = std::vector<std::vector<int>>(sumVertices);
}

Graph::Graph(std::vector<std::vector<int>> &other_list) {                                  // Конструктор листа смежностей на основе
    sumVertices = other_list.size();                                                       // исходного листа смежностей
    adjList = other_list;
}

Graph::Graph(const Graph& other_list) {                                                    // Конструктор копирования
    sumVertices = other_list.sumVertices;
    adjList = other_list.adjList;
}

Graph::Graph(Graph&& other_list) {                                                         // Конструктор перемещения
    sumVertices = other_list.sumVertices;
    adjList = other_list.adjList;
}

Graph::Graph(int sumEV, Type type) {                                                       // Конструктор листа смежностей
    switch (type) {                                                                        // ацикличного ориентированного графа
        case RANDOM_DAG:                                                                   // на основе случайных данных
            srand(time(nullptr));
            sumVertices = (-1 + (int) ceil(sqrt(1 + 8.0 * sumEV))) / 2;                    // Высчитываем количество вершин (плотный граф)
            sumEdges = sumEV - sumVertices;                                                // Количество рёбер графа
            adjList = std::vector<std::vector<int>>(sumVertices);                          // Создаём лист смежностей нужного объёма
            int sumEdges_MAX_ON_VERTICE = sumEdges / sumVertices + 1;                      // Максимальное количество исходящих рёбер для вершины
            int sumEdges_ADDED = 0;                                                        // Всего рёбер добавлено
            int sumEdges_ADDED_ON_VERTICE = 0;                                             // Рёбер добавлено для одной вершины
            int ON_TARGET = 0;                                                             // Инициализируем переменную для записи целевой вершины ребра
            for (int row = 0; row < sumVertices && sumEdges_ADDED < sumEdges; row++) {     // Пробегаемся по каждой вершине пока рёбра не закончатся
                    sumEdges_ADDED_ON_VERTICE = 0;                                         // Обнуляем счётчик рёбер для одной вершины
                    std::vector<int> TARGET (sumVertices - row - 1);                       // Создаём вектор возможных целей для рёбер текущей вершины
                    ON_TARGET = 0;                                                         // Обнуляем переменную для записи целевой вершины ребра
                    for (int i = row + 1; i < sumVertices; i++){                           // Генерируем вектор целей для текущей вершины
                        TARGET[i - row - 1] =  i;                                          // Т.к. всегда хотим получать DAG, то цели - из последующих вершин
                    }                                                                      // Не забываем про смещение элементов на строке выше
                    random_shuffle(TARGET.begin(), TARGET.end());                          // Перемешиваем цели для случайной выборки далее
                    for (int col=0; col < TARGET.size() && sumEdges_ADDED_ON_VERTICE       // Пробегаемся по текущей вершине, пока рёбра или цели не закончатся
                            < sumEdges_MAX_ON_VERTICE; col++) {
                        ON_TARGET = TARGET[col];                                           // Выбираем случайную цель
                        adjList[row].push_back(ON_TARGET);                                 // Вносим в список смежностей
                        sumEdges_ADDED++;                                                  // Увеличиваем счётчики рёбер
                        sumEdges_ADDED_ON_VERTICE++;
                    }
                    sort(adjList[row].begin(), adjList[row].end());                        // Сортируем перечень целей рёбер текущей вершины в списке смежностей
            }
    }
}

std::vector<int> Graph::doTopologicalSort(){
    std::vector<int> temp(sumVertices, 0);                                                 // Инициализируем степень вхождения вершины
    degree = temp;
    for (int row = 0; row < adjList.size(); row++) {                                       // Задаём степень вхождения каждой вершины
        for (int col = 0; col < adjList[row].size(); col++) {                              // проходя по листу смежностей
            degree[adjList[row][col]]++;
        }
    }
    
    std::vector<int> F;                                                                    // Вектор конечного результата
    std::vector<int> Z;                                                                    // Набор всех узлов без входящих ребер (degree = 0)
    int n = sumVertices;                                                                   // Получаем общее количество вершин графа
    for (int i = 0; i < n; i++) {                                                          // Вершины без входящих рёбер добавляем в Z
        if (!degree[i]) {
            Z.push_back(i);

        }
    }
    while (!Z.empty()) {                                                                   // Пока перечень вершин без входящих рёбер не опустеет
        int n = Z.back();                                                                  // Удаляем узел `n` из `Z
        Z.pop_back();
        F.push_back(n);                                                                    // Добавляем `n` в конец `F`
        for (int m: adjList[n]){
            degree[m] -= 1;                                                                // Удаляем из графа ребро `n` до `m
            if (!degree[m]) {                                                              // Если `m` не имеет других входящих ребер, вставляем `m` в `Z
                Z.push_back(m);
            }
        }
    }
    for (int i = 0; i < n; i++) {                                                          // Если в графе остались ребра, то в графе есть хотя бы один цикл
        if (degree[i]) {
            return {};
        }
    }
    return F;
}

int Graph::get_SumVertices() {                                                             // Получение количества вершин графа
    return sumVertices;
}

int Graph::get_sumEdges() {                                                                // Получение количества рёбер графа
    return sumEdges;
}

int Graph::get_adjList(){                                                                  // Получение размера списка смежностей
    int size=0;
    for (int row = 0; row < adjList.size(); row++) {
        for (int col = 0; col < adjList[row].size(); col++) {
            size++;
        }
    }
    return size;
}

void Graph::print_adjList() {                                                              // Вывод списка смежностей на экран
    for (int row = 0; row < adjList.size(); row++) {
            std::cout << row << ": ";
            for (int col = 0; col < adjList[row].size(); col++) {
                std::cout << adjList[row][col] << " ";
            }
            std::cout << std::endl;
    }
}

void Graph::print_path(std::vector<int> path) {                                            // Вывод топологически отсортированного графа
    if (!path.empty()) {
        for (int i: path) {
            std::cout << i << " ";
        }
        std::cout << "" << std::endl;
    } else {
        std::cout << "Graph has at least one cycle. Topological sorting is not possible" << std::endl;
    }
}