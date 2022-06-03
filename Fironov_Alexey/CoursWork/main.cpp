#include <iostream>
#include <vector>
#include <limits>
using namespace std;

class Ford{
private:
    int noOfNodes;
    int length;
    vector<vector<int>> graph;
    vector<vector<int>> database;
public:
    void addEdge(const int i, const int j, const int cost);
    void calculate( const int startNode);
    bool find(vector<int> nodes, int number);
    Ford(const int length, const int n);
    Ford(const Ford &other);
    Ford(Ford&& other) noexcept;
};

bool Ford::find(vector<int> nodes, int number){
    for(int i=0; i<nodes.size(); i++){
        if (nodes[i] == number){
            return false;
        }
    }
    return true;
}
Ford::Ford(Ford&& other) noexcept{
    length = other.length;
    noOfNodes = other.noOfNodes;
    graph = other.graph;
    database = other.graph;
    other.length = 0;
    other.noOfNodes = 0;
}

Ford::Ford(const Ford &other){
    length = other.length;
    noOfNodes = other.noOfNodes;
    graph = other.graph;
    database = other.database;
}
Ford::Ford(const int length, const int n){
    noOfNodes = n;
    this->length = length;
    graph.resize(length);
    database.resize(length);
    for(int i=0; i<length; i++){
        database[i].resize(2);
        for(int j = 0; j<2; j++){
            database[i][j]=0;
        }
        graph[i].resize(length);
        for(int j=0; j<length; j++){
            graph[i].push_back(0);
        }
    }
}

void Ford::addEdge(const int i, const int j, const int cost){
    graph[i][j] = cost;
}


void Ford::calculate(const int startNode){
    const int infinity = numeric_limits<int>::max();
    vector<int> nodes;
    for(int i=0; i<length; i++){
        for (int j = 0; j<length; j++){
            if (graph[i][j] != 0){
                if(find(nodes, i)){
                    if(i == startNode) {
                        database[i][0] = 0;
                        database[i][1] = 0;
                    }else{
                        database[i][0] = infinity;
                        database[i][1] = 0;

                    }
                    nodes.push_back(i);
                }
                if (find(nodes, j)){
                    if(j == startNode) {
                        database[j][0] = 0;
                        database[j][1] = 0;
                    }else{
                        database[j][0] = infinity;
                        database[j][1] = 0;
                    }
                    nodes.push_back(j);
                }
            }
        }
    }


    for (int k=0; k<noOfNodes-1; k++){
        for (int i = 0; i < nodes.size(); i++) {
            const int prev = database[nodes[i]][0];
            for (int j = 0; j < length; j++) {
                if (graph[nodes[i]][j] != 0) {
                    if (prev < infinity) {
                        const int cost = prev + graph[nodes[i]][j];
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
        cout << "Minimal distance to "<<node<<" node is:"<<database[node][0]<<'\n';
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