#include <iostream>
#include <vector>
using namespace std;

class prims
{
private://атрибуты аля переменные к объектам, цвет, колеса
    int no_of_edges, no_of_nodes;// кол-во узлов в графе
    vector <vector<long long int>> graph; // граф таблица смежности
    long long int INF; //бесконечность

public:// методы
 тип данных, т.к. функция ничего не возвращает
    void add_edge(int i, int j, int cost); //ехать , поворачивать  , добавить ребро
    void output();// вывод
    void spanningtree();//основной счет
    prims(int length, int nEdges, int nNodes)// функция конструктор , длина (размерность матрицы см-ти), кол-во ребер и узлов
    {
        this->no_of_edges =nEdges;//записываем кол-во ребер
        this->no_of_nodes = nNodes;//записываем кол-во узлов
        this->graph.resize(length);//выделение памяти под массив графа
        for (int i = 0; i < length; i++)// считаем длину
        {
            this->graph[i].resize(length); //выделение памяти под граф под матрицу
            for(int j = 0; j < length; j++)// забиваем нулями всю строчку по длине
            {
                this->graph[i].push_back(0);
            }
        }
    }

};

void prims::add_edge(int i, int j, int cost)//метод добавления ребра
{
    this->graph[i][j]=this->graph[j][i]=cost;
}

void prims::output() //вывод графа на экран
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

void prims::spanningtree() //сама функция
{
    this->INF = 9999999999;
    int n = this->no_of_nodes;
    for(int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            if (this->graph[i][j]==0){
                graph[i][j]= INF; //все элементы графа бесконечности
            }
        }
    }
    vector<bool> used (n); //массив с лог переменными НУЖЕН VERY проверка смотрели мы на этот узел или нет , visited
    vector<int> min_e (n, INF), sel_e (n, -1); // храним веса и узлы
    min_e[0] = 0; //первый вес = 0

    for (int i=0; i<n; ++i) { //цикл с перебором и нахождением мин пути
        int v = -1;
        for (int j=0; j<n; ++j)
            if (!used[j] && (v == -1 || min_e[j] < min_e[v]))
                v = j; //тут самый мин элемент
        if (min_e[v] == INF) {
            cout << "No MST!";
            exit(0);
        }

        used[v] = true;
        if (sel_e[v] != -1)
            cout << v << " " << sel_e[v] << endl; //вывод в консоль

        for (int to=0; to<n; to++) //запись мин остовного дерева и нужных узлов
            if (this->graph[v][to] < min_e[to]) {
                min_e[to] = graph[v][to];
                sel_e[to] = v;
            }
    }


    long long int total = 0; // вся длина пути
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
    prims obj {200, 20, 20}; // создание матрицы 200х200, 20 узлов, 20 ребер
    for (int i = 0; i<20; i++){
        int j=0;
        int k=0;
        while(j==k){
            j = rand() % 20;
            k = rand() % 20;
        }
        obj.add_edge(j, k, rand()); //закидываем в узел с рандомным весом
    }
    obj.spanningtree();
    obj.output(); // вывод


    return 0;
}



