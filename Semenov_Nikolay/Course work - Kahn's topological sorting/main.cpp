using namespace std;
#include <iostream>
#include <vector>
#include <ctime>
#include "Graph.h"

void doTopologicalSort_Measurement(int sumVE) {                            // Процедура проверки времени выполнения топологической сортировки
    Graph g(sumVE, RANDOM_DAG);
    //g.print_adjList();
    int start = clock();
    g.print_path(g.doTopologicalSort());
    int end = clock();
    int time = (end - start) * 1000 / CLOCKS_PER_SEC;
    std::cout << "Summary of edges and vertices: " << g.get_SumVertices() + g.get_sumEdges() << ", milliseconds: ";
    std::cout << time << std::endl;
    std::cout << "Size of adjacency list: " << g.get_adjList() << std::endl;
}

int main(){
    //std::vector<std::vector<int>> adjList_1 =                             // Задаём вектор рёбер графа согласно примеру
    //        {
    //                {6}, {2,4,6}, {}, {0,4}, {}, {1}, {}, {0, 1}
    //        };
    //int n = 8;                                                            // Общее количество вершин в графе (0-7)
    //Graph graph(adjList_1);                                               // Строим граф из заданных ребер
    //graph.print_adjList();
    //graph.print_path(graph.doTopologicalSort());                          // Выполняем топологическую сортировку
    doTopologicalSort_Measurement(1000000000);
    return 0;
}