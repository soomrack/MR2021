#include <iostream>
#include <vector>
using namespace std;

class prims
{
private:
    int no_of_edges, no_of_nodes;
    vector <vector<long long int>> graph;
    vector<int> visited;
    long long int INF;
public:

    void add_edge(int i, int j, int cost);
    void output();
    void spanningtree();
    prims(int length, int nEdges, int nNodes)
    {
        this->no_of_edges =nEdges;
        this->no_of_nodes = nNodes;
        this->graph.resize(length);
        for (int i = 0; i < length; i++)
        {
            this->visited.push_back(0);
            this->graph[i].resize(length);
            for(int j = 0; j < length; j++)
            {
                this->graph[i].push_back(0);
            }
        }
    }

};

void prims::add_edge(int i, int j, int cost)
{
    this->graph[i][j]=this->graph[j][i]=cost;
}

void prims::output()
{
    for (int i = 0; i < this->no_of_nodes; i++)
    {
        cout << endl;
        for (int j = 0; j < this->no_of_nodes; j++)
        { if (this->graph[i][j]!= INF){
                cout.width(4);
                cout << this->graph[i][j];
            }else{
                cout.width(4);
                cout << 0;
            }
        }
    }
}

void prims::spanningtree()
{
    this->INF = 9999999999;
    int n = this->no_of_nodes;
    for(int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            if (this->graph[i][j]==0){
                graph[i][j]= INF;
            }
        }
    }
    vector<bool> used (n);
    vector<int> min_e (n, INF), sel_e (n, -1);
    min_e[0] = 0;

    for (int i=0; i<n; ++i) {
        int v = -1;
        for (int j=0; j<n; ++j)
            if (!used[j] && (v == -1 || min_e[j] < min_e[v]))
                v = j;
        if (min_e[v] == INF) {
            cout << "No MST!";
            exit(0);
        }

        used[v] = true;
        if (sel_e[v] != -1)
            cout << v << " " << sel_e[v] << endl;

        for (int to=0; to<n; ++to)
            if (this->graph[v][to] < min_e[to]) {
                min_e[to] = graph[v][to];
                sel_e[to] = v;
            }
    }


    long long int total = 0;
    cout<<endl;
    cout<<"Minimum distance peth is ";
    for (int i = 0; i < n - 1; i++)
    {
        cout << min_e[i] << " ";
        total = total + min_e[i];

    }
    cout << endl << "Total path cost is " << total;

}

int main()
{
    prims obj {200, 20, 20};
    for (int i = 0; i<20; i++){
        int j=0;
        int k=0;
        while(j==k){
            j = rand() % 20;
            k = rand() % 20;
        }
        obj.add_edge(j, k, rand()%100);
    }

    prims a {200, 20, 20};
    a=obj;
    cout<<'\n'<<'\n';
    a.add_edge(2,3,100);
    obj.output();
    cout<<'\n'<<'\n';
    a.output();

    return 0;
}




