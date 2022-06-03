#include <iostream>
#include <vector>
#include <stack>
#include <chrono>
using namespace std;

class Graph {
private:
    int vertices;
    vector<vector<int>> adj_matrix ;
public:
    Graph(int v, vector<vector<int>> &adj_matrix);
    void Tarjan_algorithm();
    void Tarjan_DFS( int current_node, vector<int>& queue_num, vector<int>& low_link, vector<bool>& presents_in_stack,
                stack<int>& stack_of_relatives);
    void Print_SCC(int head_of_SCC, stack<int>& stack_of_relatives, vector<bool>& presents_in_stack);
};

Graph::Graph(int v, vector<vector<int>> &adj_matrix){
    this->adj_matrix = adj_matrix;
    this->vertices = v;
}

void Graph::Print_SCC(int head_of_SCC, stack<int>& stack_of_relatives, vector<bool>& presents_in_stack) {
    cout << "SCC: ";
    while (stack_of_relatives.top() != head_of_SCC ) {
        cout << stack_of_relatives.top() << ", ";
        presents_in_stack[stack_of_relatives.top()] = false;
        stack_of_relatives.pop();
    }
    cout << stack_of_relatives.top() << "\n";
    presents_in_stack[stack_of_relatives.top()] = false;
    stack_of_relatives.pop();
}

void Graph::Tarjan_DFS(int current_node, vector<int> &queue_num, vector<int> &low_link, vector<bool> &presents_in_stack,
                       stack<int>& stack_of_relatives) {
    static int time = 0;
    queue_num[current_node] = time;
    low_link[current_node] = time;
    time++;
    stack_of_relatives.push(current_node);
    presents_in_stack[current_node] = true;
    for (int descendant = 0; descendant <= vertices; descendant++){
        if ( adj_matrix[current_node][descendant] == 0){
        }
        else if (queue_num[descendant] == -1) {
            Tarjan_DFS(descendant, queue_num, low_link, presents_in_stack, stack_of_relatives );
            low_link[current_node] = min(low_link[current_node],low_link[descendant]);
        }
        else if (presents_in_stack[descendant]) {
            low_link[current_node] = min(low_link[current_node],queue_num[descendant]);
        }
    }
    if ( low_link[current_node] == queue_num[current_node]){
        Print_SCC(current_node, stack_of_relatives, presents_in_stack);
    }

}

void Graph::Tarjan_algorithm(){
    vector<bool> presents_in_stack(vertices, false);
    stack<int> stack_of_relatives;
    vector<int> queue_num(vertices, -1);
    vector<int> low_link(vertices, -1);
    for (int i = 0; i < vertices; i++){
        if (queue_num[i] == -1){
            Tarjan_DFS(i, queue_num, low_link, presents_in_stack, stack_of_relatives );
        }
    }
}


int main() {
    int v = 7;
    vector<vector<int>> grid = {{0,1,0,0,0,0,0},
                                {0,0,1,0,0,0,0},
                                {0,0,0,1,0,1,0},
                                {0,0,0,0,1,0,0},
                                {0,0,0,0,0,0,1},
                                {1,0,0,0,0,0,0},
                                {0,0,1,0,0,0,0}};
    //vector<vector<int>> grid(v, vector<int>(v,1));
    int a = v + v * v;
    cout << "V+E=" << a << endl;
    Graph A(v,grid);
    auto start=chrono::high_resolution_clock::now();
    A.Tarjan_algorithm();
    auto end=chrono::high_resolution_clock::now();
    chrono::duration<float> duration = end - start;
    cout << "Duration " << duration.count() << endl;
    //Проверка
    vector<vector<int>> grid_1;
    grid_1 = grid;
    grid = {{1,1,0,0,0,0,0},
            {0,0,1,0,0,0,0},
            {0,0,0,1,0,1,0},
            {0,0,0,0,1,0,0},
            {0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0},
            {0,0,1,0,0,0,0}};
    cout << grid[0][0] << endl;
    cout << grid_1[0][0]  << endl;

}

