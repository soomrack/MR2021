#include <iostream>
#include <vector>
using namespace std;

struct Edge {                                       // Структура данных для хранения рёбер графа
    int src, dest;
};

class Graph {                                       // Класс объекта графа
public:
    vector<vector<int>> adjList;                    // Вектор векторов, представляющий список сопряжения узлов
    vector<int> degree;                             // Вектор, хранящий степень вершины (число входящих в неё рёбер)
    Graph(vector<Edge> const &edges, int n) {       // Конструктор графа
        adjList.resize(n);                          // Изменяем размер вектора, чтобы он содержал `n` элементов типа `vector<int>`
        vector<int> temp(n, 0);                     // Инициализируем степень вершины
        degree = temp;
        for (auto &edge: edges) {                   // Добавляем рёбра к ориентированному (отсортированному) графу
            adjList[edge.src].push_back(edge.dest); // Добавляем ребро от источника к месту назначения
            degree[edge.dest]++;                    // Увеличиваем степень целевой вершины на 1
        }
    }
};

vector<int> doTopologicalSort(Graph const &graph) { // Функция для выполнения топологической сортировки заданной DAG (направленный ациклический граф)
    vector<int> F;
    int n = graph.adjList.size();                   // Получаем общее количество вершин графа
    vector<int> degree = graph.degree;
    vector<int> Z;                                  // Набор всех узлов без входящих ребер (degree = 0)
    for (int i = 0; i < n; i++) {
        if (!degree[i]) {
            Z.push_back(i);
        }
    }
    while (!Z.empty()) {
        int n = Z.back();                           // Удаляем узел `n` из `Z`
        Z.pop_back();
        F.push_back(n);                             // Добавляем `n` в конец `F`
        for (int m: graph.adjList[n]){
            degree[m] -= 1;                         // Удаляем из графа рёбра от `n` до `m`
            if (!degree[m]) {                       // Если `m` не имеет других входящих ребер, вставляем `m` в `Z`
                Z.push_back(m);
            }
        }
    }
    for (int i = 0; i < n; i++) {                   // Если в графе остались ребра, то в графе есть хотя бы один цикл
        if (degree[i]) {
            return {};
        }
    }
    return F;
}

int main(){
    vector<Edge> edges =                            // Задаём вектор рёбер графа согласно примеру
            {
                    { 0, 6 }, { 1, 2 }, { 1, 4 }, { 1, 6 }, { 3, 0 }, { 3, 4 },
                    { 5, 1 }, { 7, 0 }, { 7, 1 }
            };
    int n = 8;                                      // Общее количество вершин в графе (0-7)
    Graph graph(edges, n);                          // Строим граф из заданных ребер
    vector<int> F = doTopologicalSort(graph);       // Выполняем топологическую сортировку
    if (F.size()) {                                 // Вывод топологического порядка
        for (int i: F) {
            cout << i << " ";
        }
    } else {
        cout << "Graph has at least one cycle. Topological sorting is not possible";
    }
    return 0;
}