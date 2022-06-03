#include <iostream>
#include <vector>
#include <limits>
using namespace std;

class Ford{
private:
    int noOfNodes;                  //Ко-во узлов
    int length;                     //Размерность матрицы смежности
    vector<vector<int>> graph;      //Матрица смежности
    vector<vector<int>> database;   //2 x length - вес пути до вершины
public:
    void addEdge(int i, int j, int cost);       //Добавление в таблицу смежности
    void calculate(int startNode);
    bool find(vector<int> nodes, int number);   //Наличие элемента в массиве. Защита от повторного заполнения

    Ford(int length, int n){
        this->noOfNodes = n;
        this->length = length;
        this->graph.resize(length);
        this->database.resize(length);
        for (int i=0; i < length; i++){
            this->database[i].resize(2);
            for(int j = 0; j < 2; j++){
                this->database[i][j]=0;
            }
            this->graph[i].resize(length);
            for(int j=0; j < length; j++){
                this->graph[i].push_back(0);
            }
        }
    }
};

bool Ford::find(vector<int> nodes, int number){
    for(int i=0; i<nodes.size(); i++){
        if (nodes[i] == number){
            return false;
        }
    }
    return true;
}


void Ford::addEdge(int i, int j, int cost){
    this->graph[i][j] = cost;
}


void Ford::calculate(int startNode){
    int infinity = numeric_limits<int>::max();
    vector<int> nodes;                                  //Хранение номеров узлов
    for(int i=0; i<this->length; i++){
        for (int j = 0; j<this->length; j++){
            if (this->graph[i][j] != 0){
                if(this->find(nodes, i)){
                    if(i == startNode) {                //Стартовый узел
                        this->database[i][0] = 0;
                        this->database[i][1] = 0;
                    }else{                              //Остальные узлы
                        this->database[i][0] = infinity;
                        this->database[i][1] = 0;

                    }
                    nodes.push_back(i);
                }
                if (this->find(nodes, j)){
                    if(j == startNode) {
                        this->database[j][0] = 0;
                        this->database[j][1] = 0;
                    }else{
                        this->database[j][0] = infinity;
                        this->database[j][1] = 0;
                    }
                    nodes.push_back(j);
                }
            }
        }
    }


    for (int k=0; k<this->noOfNodes-1; k++){
        for (int i = 0; i < nodes.size(); i++) {
            int prev = this->database[nodes[i]][0];         //Вес в текущем узле
            for (int j = 0; j < this->length; j++) {
                if (this->graph[nodes[i]][j] != 0) {
                    if (prev < infinity) {                  //Проверка родительского нода
                        int cost = prev + this->graph[nodes[i]][j];
                        if (cost < database[j][0]) {
                            database[j][0] = cost;
                            database[j][1] = i;
                        }
                    }
                }
            }
        }
    }

    for(int node : nodes){
        cout << "Minimal distance to "<<node<<" node is:"<<this->database[node][0]<<'\n';
    }


}
int main()
{
    Ford ford = Ford(4,4);
    ford.addEdge(0,1,4);
    ford.addEdge(0,2,4);
    ford.addEdge(0,3,7);
    ford.addEdge(2,1,-1);
    ford.addEdge(1,3,3);
    ford.addEdge(2,3,6);

    ford.calculate(0);
    return 0;
}