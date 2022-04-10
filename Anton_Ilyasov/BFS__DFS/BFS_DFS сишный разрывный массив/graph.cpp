#include <iostream>
#include "graph.h"
#include <queue> // очередь
#include <stack> // стек

Graph::Graph() {
    numVertices = 0;
    adjMatrix = nullptr;
}

Graph::Graph(int numVertices, const int other_matrix[][6]) { //матрица смежности создается на основе исходной матрицы
    this->numVertices = numVertices;
    adjMatrix = new int* [numVertices];
    for (int i = 0; i < numVertices; i++)
    {
        adjMatrix[i] = new int [numVertices];
    }

    for (int i = 0; i < numVertices; i++)
    {
        for (int j = 0; j < numVertices; j++)
        {
            adjMatrix[i][j] = other_matrix[i][j];
        }
    }
}

Graph::Graph(int numVertices, GraphType type) { //матрица смежности с разными данными
    this->numVertices = numVertices;
    adjMatrix = new int* [numVertices];
    for (int i = 0; i < numVertices; i++)
    {
        adjMatrix[i] = new int[numVertices];
    }
    switch (type)
    {
    case ZERO:
        for (int i = 0; i < numVertices * numVertices; i++)
        {
            for (int j = 0; j < numVertices; j++)
            {
                adjMatrix[i][j] = 0;
            }
        }
        break;
    case RANDOM:
        //srand(time(NULL));
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices ; j++) {
                adjMatrix[i][j] = rand() % 2;
                if (i == j) adjMatrix[i][i] = 0;
            }
        }
        break;
    }
}

Graph::Graph(const Graph& other_matrix) //конструктор копирования
{
    numVertices = other_matrix.numVertices;
    adjMatrix = new int* [numVertices];
    for (int i = 0; i < numVertices; i++)
    {
        adjMatrix[i] = new int[numVertices];
    }

    for (int i = 0; i < numVertices; i++)
    {
        for (int j = 0; j < numVertices; j++)
        {
            adjMatrix[i][j] = other_matrix.adjMatrix[i][j];
        }
    }
}

Graph::Graph(Graph&& other_matrix) //Конструктор перемещения
{
    numVertices = other_matrix.numVertices;
    adjMatrix = other_matrix.adjMatrix;
    other_matrix.numVertices = 0;
    other_matrix.adjMatrix = nullptr;
}

void Graph::addEdge(int i, int j) {
    adjMatrix[i][j] = 1;
    adjMatrix[j][i] = 1;
}

void Graph::removeEdge(int i, int j) {
    adjMatrix[i][j] = 0;
    adjMatrix[j][i] = 0;
}

bool Graph::isEdge(int i, int j) {
    return adjMatrix[i][j];
}

void Graph::toString() {
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++)
            std::cout << adjMatrix[i][j] << " ";
        std::cout << "\n";
    }
}

void Graph::bfs_search() {
    std::cout << "\n";
    int* nodes = new int[numVertices]; // вершины графа (0 - все вершины не рассмотрены)
    for (int i = 0; i < numVertices; i++) {
        nodes[i] = 0;
    }

    std::queue<int> Queue;
    Queue.push(0); // помещаем в очередь первую вершину
    while (!Queue.empty()) // пока очередь не пуста
    {
        int node = Queue.front(); // извлекаем вершину
        Queue.pop();
        nodes[node] = 2; // отмечаем ее как посещенную
        for (int j = 0; j < numVertices; j++) { // проверяем для нее все смежные вершины
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
    int* nodes = new int[numVertices]; // вершины графа (0 - все вершины не рассмотрены)
    for (int i = 0; i < numVertices; i++) {
        nodes[i] = 0;
    }

    std::stack<int> Stack;
    Stack.push(0); // помещаем в очередь первую вершину
    while (!Stack.empty()) {
        int node = Stack.top(); // извлекаем вершину
        Stack.pop();
        nodes[node] = 2; // отмечаем ее как посещенную
        for (int j = numVertices - 1; j >= 0; j--) { // проверяем для нее все смежные вершины
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

Graph::~Graph() {
    for (int i = 0; i < numVertices; i++)
    {
        delete[] adjMatrix[i];
    }
    delete[] adjMatrix;
    adjMatrix = nullptr;
}