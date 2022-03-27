#include <iostream>
#include "graph.h"
#include <queue> // очередь
#include <stack> // стек

Graph::Graph() {
    numVertices = 0;
}

Graph::Graph(int64_t numVertices, std::vector<std::vector<int>>& other_matrix) { //матрица смежности создается на основе исходной матрицы
    this->numVertices = numVertices;
    adjMatrix = other_matrix;
}

Graph::Graph(int64_t numVertices, GraphType type) { //матрица смежности с разными данными
    this->numVertices = numVertices;
    switch (type)
    {
    case ZERO:
        for (int i = 0; i < numVertices; i++)
        {
            std::vector<int> row(numVertices);
            for (int j = 0; j < numVertices; j++)
            {
                row[j] = 0;
            }
            adjMatrix.push_back(row);
        }
        break;
    case RANDOM:
        srand(time(NULL));
        for (int i = 0; i < numVertices; i++)
        {
            std::vector<int> row(numVertices);
            for (int j = 0; j < numVertices; j++)
            {
                if (i == j) row[j] = 0;
                else row[j] = rand() % 2;
            }
            adjMatrix.push_back(row);
        }
        break;
    }
}

void Graph::addEdge(int64_t i, int64_t j) {
    adjMatrix[i][j] = 1;
    adjMatrix[j][i] = 1;
}

void Graph::removeEdge(int64_t i, int64_t j) {
    adjMatrix[i][j] = 0;
    adjMatrix[j][i] = 0;
}

bool Graph::isEdge(int64_t i, int64_t j) {
    return adjMatrix[i][j];
}

void Graph::toString() {
    for (int64_t i = 0; i < numVertices; i++) {
        for (int64_t j = 0; j < numVertices; j++)
            std::cout << adjMatrix[i][j] << " ";
        std::cout << "\n";
    }
}

void Graph::bfs_search() {
    std::cout << "\n";
    int64_t* nodes = new int64_t[numVertices]; // вершины графа (0 - все вершины не рассмотрены)
    for (int64_t i = 0; i < numVertices; i++) {
        nodes[i] = 0;
    }

    std::queue<int64_t> Queue;
    Queue.push(0); // помещаем в очередь первую вершину
    while (!Queue.empty()) // пока очередь не пуста
    {
        int64_t node = Queue.front(); // извлекаем вершину
        Queue.pop();
        nodes[node] = 2; // отмечаем ее как посещенную
        for (int64_t j = 0; j < numVertices; j++) { // проверяем для нее все смежные вершины
            if (adjMatrix[node][j] == 1 && nodes[j] == 0) { // если вершина смежная и не обнаружена
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
    std::cout << "\n";
    int64_t* nodes = new int64_t[numVertices]; // вершины графа (0 - все вершины не рассмотрены)
    for (int64_t i = 0; i < numVertices; i++) {
        nodes[i] = 0;
    }

    std::stack<int64_t> Stack;
    Stack.push(0); // помещаем в очередь первую вершину
    while (!Stack.empty()) {
        int64_t node = Stack.top(); // извлекаем вершину
        Stack.pop();
        nodes[node] = 2; // отмечаем ее как посещенную
        for (int64_t j = numVertices - 1; j >= 0; j--) { // проверяем для нее все смежные вершины
            if (adjMatrix[node][j] == 1 && nodes[j] == 0) { // если вершина смежная и не обнаружена
                Stack.push(j); // добавляем ее в cтек
                nodes[j] = 1; // отмечаем вершину как обнаруженную
            }
        }
        //std::cout << node << " "; // выводим номер вершины
    }
    delete[] nodes;
    nodes = nullptr;
}