#include <iostream>
#include "graph.h"
using namespace std;
#include <queue> // очередь
#include <stack> // стек

Graph::Graph(int numVertices) {
    this->numVertices = numVertices;
    adjMatrix = new bool* [numVertices];
    for (int i = 0; i < numVertices; i++) {
        adjMatrix[i] = new bool[numVertices];
        for (int j = 0; j < numVertices; j++)
            adjMatrix[i][j] = false;
    }
}

Graph::Graph(int numVertices, string type) {
    //srand(time(NULL));
    this->numVertices = numVertices;
    adjMatrix = new bool* [numVertices];
    for (int i = 0; i < numVertices; i++) {
        adjMatrix[i] = new bool[numVertices];
        for (int j = 0; j < numVertices; j++) {
            adjMatrix[i][j] = rand() % 2;
        }
    }
}

void Graph::addEdge(int i, int j) {
    adjMatrix[i][j] = true;
    adjMatrix[j][i] = true;
}

void Graph::removeEdge(int i, int j) {
    adjMatrix[i][j] = false;
    adjMatrix[j][i] = false;
}

bool Graph::isEdge(int i, int j) {
    return adjMatrix[i][j];
}

void Graph::toString() {
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++)
            cout << adjMatrix[i][j] << " ";
        cout << "\n";
    }
}

void Graph::bfs_search() {
    cout << endl;
    int* nodes = new int[numVertices]; // вершины графа (0 - все вершины не рассмотрены)
    for (int i = 0; i < numVertices; i++) {
        nodes[i] = 0;
    }

    queue<int> Queue;
    Queue.push(0); // помещаем в очередь первую вершину
    while (!Queue.empty()) // пока очередь не пуста
    {
        int node = Queue.front(); // извлекаем вершину
        Queue.pop();
        nodes[node] = 2; // отмечаем ее как посещенную
        for (int j = 0; j < numVertices; j++) { // проверяем для нее все смежные вершины
            if (adjMatrix[node][j] == true && nodes[j] == 0) { // если вершина смежная и не обнаружена
                Queue.push(j); // добавляем ее в очередь
                nodes[j] = 1; // отмечаем вершину как обнаруженную
            }
        }
        //cout << node << " "; // выводим номер вершины
    }
    delete[] nodes;
    nodes = nullptr;
}

void Graph::dfs_search() {
    cout << endl;
    int* nodes = new int[numVertices]; // вершины графа (0 - все вершины не рассмотрены)
    for (int i = 0; i < numVertices; i++) {
        nodes[i] = 0;
    }

    stack<int> Stack;
    Stack.push(0); // помещаем в очередь первую вершину
    while (!Stack.empty()) {
        int node = Stack.top(); // извлекаем вершину
        Stack.pop();
        if (nodes[node] == 2) continue;
        nodes[node] = 2; // отмечаем ее как посещенную
        for (int j = numVertices - 1; j >= 0; j--) { // проверяем для нее все смежные вершины
            if (adjMatrix[node][j] == true && nodes[j] != 2) { // если вершина смежная и не обнаружена
                Stack.push(j); // добавляем ее в cтек
                nodes[j] = 1; // отмечаем вершину как обнаруженную
            }
        }
        //cout << node << " "; // выводим номер вершины
    }
    delete[] nodes;
    nodes = nullptr;
}

Graph::~Graph() {
    for (int i = 0; i < numVertices; i++)
        delete[] adjMatrix[i];
    delete[] adjMatrix;
    adjMatrix = nullptr;
}