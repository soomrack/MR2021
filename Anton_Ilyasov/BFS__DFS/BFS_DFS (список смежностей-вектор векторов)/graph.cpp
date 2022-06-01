#include "pch.h"
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

Graph::Graph(int num_of_vertices) { //������ ���� ����������
    this->num_of_vertices = num_of_vertices;
    adjacency_list = std::vector<std::vector<int>>(num_of_vertices);
}

Graph::Graph(const std::vector<std::vector<int>>& other_list) { //������ ��������� �� ������ ��������� ����� ���������
    num_of_vertices = other_list.size();
    adjacency_list = other_list;
}

Graph::Graph(int sum_of_edges_and_vertices, GraphType type) { //������ ��������� � ������� �������
    if (sum_of_edges_and_vertices <= 0) {
        num_of_edges = 0;
        num_of_vertices = 0;
        adjacency_list = std::vector<std::vector<int>>(0);
    }
    else if (sum_of_edges_and_vertices == 1) {
        num_of_edges = 0;
        num_of_vertices = 1;
        adjacency_list = std::vector<std::vector<int>>(1);
    }
    else if (sum_of_edges_and_vertices == 2) {
        num_of_edges = 0;
        num_of_vertices = 2;
        adjacency_list = std::vector<std::vector<int>>(2);
    }
    else {
        switch (type) {
        case RANDOM: //��������� ������ ����������
            //srand(time(NULL));
            srand(1);
            //����� ������������� ������� ����
            num_of_vertices = (-1 + (int)ceil(sqrt(1 + 8.0 * sum_of_edges_and_vertices))) / 2;
            num_of_edges = sum_of_edges_and_vertices - num_of_vertices;

            int add_edge = 0; //����� ����� ��������� 

            adjacency_list = std::vector<std::vector<int>>(num_of_vertices);

            //����������� ���������� ������ ����������
            int vertice_edge = num_of_edges / num_of_vertices + 1;
            bool add_edge_less_num_edge = true;

            for (int v = 0; v < num_of_vertices && add_edge_less_num_edge; v++) {
                int add_vertice_edge = 0; //��������� ����� ��� �������
                bool add_vertice_edge_less_vertice_edge = true;
                for (int w = (rand() % num_of_vertices); add_vertice_edge_less_vertice_edge && add_edge_less_num_edge;) {
                    if (v != w && !(std::find(adjacency_list[v].begin(), adjacency_list[v].end(), w) != adjacency_list[v].end())) {
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

Graph::Graph(const Graph& other_list) { //����������� �����������
    num_of_vertices = other_list.num_of_vertices;
    num_of_edges = other_list.num_of_edges;
    adjacency_list = other_list.adjacency_list;
    adjacency_matrix = other_list.adjacency_matrix;
}

Graph::Graph(Graph&& other_list) { //����������� �����������
    num_of_vertices = other_list.num_of_vertices;
    num_of_edges = other_list.num_of_edges;
    adjacency_list = other_list.adjacency_list;
    adjacency_matrix = other_list.adjacency_matrix;
}

Graph& Graph::operator =(const Graph& other_list) { //���������� ��������� ������������ 
    if (&other_list == this) {
        return *this;
    }
    num_of_vertices = other_list.num_of_vertices;
    num_of_edges = other_list.num_of_edges;
    adjacency_list = other_list.adjacency_list;
    adjacency_matrix = other_list.adjacency_matrix;
    return *this;
}

void Graph::add_edge(int from, int to) { //���������� ����������������� �����
    adjacency_list[from].push_back(to);
    sort(adjacency_list[from].begin(), adjacency_list[from].end());
    num_of_edges++;
}

void Graph::remove_edge(int from, int to) { //�������� ����������������� �����
    for (auto it = adjacency_list[from].begin(); it != adjacency_list[from].end(); )
    {
        if (*it == to)
        {
            it = adjacency_list[from].erase(it);
            break;
        }
        else
            ++it;
    }
    num_of_edges--;
}

bool Graph::is_edge(int from, int to) { //���� �� ����� ����� ��������� from � to
    for (int i = 0; i < adjacency_list[from].size(); ++i) {
        if (adjacency_list[from][i] == to) return true;
    }
    return false;
}

int Graph::get_number_of_vertices() { //���������� ������
    return num_of_vertices;
}

int Graph::get_number_of_edges() { //���������� �����
    num_of_edges = 0;
    for (int row_count = 0; row_count < adjacency_list.size(); row_count++) {
        for (int i = 0; i < adjacency_list[row_count].size(); ++i) {
            num_of_edges++;
        }
    }
    return num_of_edges;
}

std::vector<std::vector<int>> Graph::get_adjacency_matrix() { //�������� ������� ���������� �� ������ ���������
    for (int v = 0; v < num_of_vertices; v++) {
        std::vector<int> row(num_of_vertices, 0);
        adjacency_matrix.push_back(row);
        for (int i = 0; i < adjacency_list[v].size(); ++i) {
            adjacency_matrix[v][adjacency_list[v][i]] = 1;
        }
    }
    return adjacency_matrix;
}

std::vector<std::vector<int>> Graph::get_adjacency_list() { //�������� ������ ����������
    return adjacency_list;
}

void Graph::print_adjacency_list() { //����� ������ ��������� �� �����
    for (int row_count = 0; row_count < adjacency_list.size(); row_count++) {
        std::cout << row_count << ": ";
        for (int i = 0; i < adjacency_list[row_count].size(); ++i) {
            std::cout << adjacency_list[row_count][i] << " ";
        }
        std::cout << std::endl;
    }
}

void Graph::print_adjacency_matrix() { //����� ������� ��������� �� �����
    if (adjacency_matrix.size() == 0) {
        std::cout << "Print adjacency matrix error. Adjacency matrix size must be more zero"
            "To fix this mistake input x.get_adjacency_matrix()";
        return;
    }
    for (int i = 0; i < num_of_vertices; i++) {
        for (int j = 0; j < num_of_vertices; j++)
            std::cout << adjacency_matrix[i][j] << " ";
        std::cout << "\n";
    }
}

void Graph::print_vector(std::vector<int> vector_to_print) { //����� �������
    for (int i = 0; i < vector_to_print.size(); i++) {
        std::cout << vector_to_print[i] << " ";
    }
}

std::vector<int> Graph::bfs_search() {
    std::vector<int> bfs_search;
    std::vector<int> nodes(num_of_vertices, 0); // ������� ����� (0 - ��� ������� �� �����������)
    std::queue<int> Queue; // ������� ��� �������� ������� ������
    Queue.push(0); // �������� � ������� ������ �������
    while (!Queue.empty()) { // ���� ������� �� �����
        int node = Queue.front(); // ��������� �������
        Queue.pop(); // ������� �������
        nodes[node] = 2; // �������� �� ��� ����������
        for (int i = 0; i < adjacency_list[node].size(); ++i) { // ������� ��� ������� �������
            if (nodes[adjacency_list[node][i]] == 0) { // ���� ������� ������� � �� ����������
                Queue.push(adjacency_list[node][i]); // ��������� �� � �������
                nodes[adjacency_list[node][i]] = 1; // �������� �� ��� ������������
            }
        }
        bfs_search.push_back(node);
    }
    return bfs_search;
}

std::vector<int> Graph::dfs_search() {
    std::vector<int> dfs_search;
    std::vector<int> nodes(num_of_vertices, 0); // ������� ����� (0 - ��� ������� �� �����������)
    std::stack<int> Stack; //���� ��� �������� ������� ������
    Stack.push(0); // �������� � ���� ������ �������
    while (!Stack.empty()) { //���� ���� �� ����
        int node = Stack.top(); // ��������� �������
        Stack.pop(); // ������� �������
        if (nodes[node] == 2) continue; // ���� ������� ���� ��������, ��������� � ���������
        nodes[node] = 2; // �������� �� ��� ����������
        for (int i = adjacency_list[node].size() - 1; i >= 0; --i) { // ��������� ��� ��� ��� ������� �������
            if (nodes[adjacency_list[node][i]] != 2) { // ���� ������� ������� � �� ��������
                Stack.push(adjacency_list[node][i]); // ��������� �� � c���
                nodes[adjacency_list[node][i]] = 1; // �������� ������� ��� ������������
            }
        }
        dfs_search.push_back(node);
    }
    return dfs_search;
}

std::vector<int> Graph::find_path(const int from, const int to) {
    if (from >= num_of_vertices || to >= num_of_vertices) { //������, ���� ����� ������� ���
        std::cout << "Find min path error. Index exceeds the number of vertices. Index must be not more " << num_of_vertices - 1 << "\n";
        return restored_path;
    }
    if (from == to) { //������, ���� ���� = �����
        std::cout << "Find min path error. Check entrance and exit.";
        return restored_path;
    }
    std::vector<int> nodes(num_of_vertices, 0); // ������� ����� (0 - ��� ������� �� �����������)
    std::queue<int> Queue; //����� �������� ��� ������� �������
    struct Edge { //��������� ��� �����
        int begin;
        int end;
    };
    Edge Edge_beetween_two_vertices; //����� � ����� �����������
    std::stack<Edge> Edges; //������ �����
    Queue.push(from); //������� �������� �������
    bool find = false; //���������� ���� �� ������
    while (!Queue.empty() && !find) { //���� ���� ������� ������� � ���� �� ������
        int node = Queue.front();
        Queue.pop();
        nodes[node] = 2; //�������� ������� ��� ����������
        for (int i = 0; i < adjacency_list[node].size(); ++i) { //���������� ������� ������� ��� �������
            if (nodes[adjacency_list[node][i]] == 0) { //���� ������� �� ���� ��������
                nodes[adjacency_list[node][i]] = 1; // �������� ������� ��� ������������
                Queue.push(adjacency_list[node][i]); //������� ������� � �������
                Edge_beetween_two_vertices.begin = node; //������� ������ �����
                Edge_beetween_two_vertices.end = adjacency_list[node][i]; //������� ����� �����
                Edges.push(Edge_beetween_two_vertices); //������� ����� � ���� �����
                if (adjacency_list[node][i] == to) { //���� ��������� �� ������ �������, ������������� ������� ������
                    find = true; //����� ��������� �������
                    break; //������� �� �����
                }
            }
        }
    }
    //����� ���� ����������
    if (find) {
        int update_to = to;
        while (update_to != from && !Edges.empty()) { //���������� ��� ��������� �����
            Edge_beetween_two_vertices = Edges.top(); //��������� ������� �����
            Edges.pop(); //������� ������� �����
            if (Edge_beetween_two_vertices.end == update_to) { //���� ����� ����� ����� � ������� �������
                update_to = Edge_beetween_two_vertices.begin; //������ ������� ������� - ������ ����� �����
                restored_path.push_back(Edge_beetween_two_vertices.end); //������� ����� ����� � ������ ������
            }
        }
        restored_path.push_back(from); //������� ������ ���� � ������ �����
        std::reverse(restored_path.begin(), restored_path.end()); //������, ����� ���� ��� �� from � to
    }
    //����� ���������, ���� ���� ���
    else {
        std::cout << "No path from " << from << " to " << to << ".";
    }
    return restored_path;
}

std::vector<int> Graph::topological_sort() {
    //!!!����� ��������� �������� �� ������������ �����!!!

    std::vector<int> nodes(num_of_vertices, 0); // ������� ����� (0 - ��� ������� �� �����������)
    std::stack<int> Stack; // ���� ��� �������� ������� ������
    for (int i = 0; i < num_of_vertices; ++i) { // ���������� ��� ������� �����
        Stack.push(i); // �������� � ���� �������
        while (!Stack.empty()) { //���� ���� �� ����
            int node = Stack.top(); // ��������� �������
            if (nodes[node] == 2) { //���� ������� ��������
                Stack.pop(); // ������� �������,
                continue; // ��������� � ���������;
            }
            if (nodes[node] == 1) { // ���� ������� ���� ����������
                topological_sorted_graph.push_back(node);
                Stack.pop(); // ������� �������,
                nodes[node] = 2; //�������� ��� ����������
                continue; // ��������� � ���������;
            }
            nodes[node] = 1; // �������� �� ��� ������������
            bool has_edge = false; // ���������� �� ������� ������� ��� �����
            for (int i = adjacency_list[node].size() - 1; i >= 0; --i) { // ��������� ��� ��� ��� ������� �������
                if (nodes[adjacency_list[node][i]] != 2) { // ���� ������� ������� � �� ��������
                    Stack.push(adjacency_list[node][i]); // ��������� �� � c���
                    has_edge = true; // ���� �����
                }
            }
            if (!has_edge) { // ���� �� ������� ������� ��� �����
                topological_sorted_graph.push_back(node);
                Stack.pop(); // ������� �������
                nodes[node] = 2; //�������� ��� ����������
            }
        }
    }
    std::reverse(topological_sorted_graph.begin(), topological_sorted_graph.end());
    return topological_sorted_graph;
}
