#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>

#include <ctime>

using namespace std;

const int inf = numeric_limits<int>::max(); // Принимаем за "бесконечность" наибольшее число int


struct edge {
    int a, b, cost; //a - номер предыдущей вершины, b - номер новой вершины, cost - вес ребра
};


void solve(const vector<edge> &e, int n, int start_value)
{
    vector<int> d(n, inf);
    d[start_value] = 0; // вес ребра для нулевой вершины - 0

    for(;;)
    {
        bool any = false;
        for (int k = 0; k < e.size(); ++k)
            if (d[e[k].a] < inf)    //Проверка для рёбер отрицательного веса
                if (d[e[k].b] > d[e[k].a] + e[k].cost)
                {
                    d[e[k].b] = d[e[k].a] + e[k].cost;
                    any = true;
//====================БЛОК ВЫВОДА=========================
                    for (int i = 1; i < n; ++i)
                    {
                        if (d[i] != inf) cout << i << ": " << d[i] << endl;
                        else cout << i << ": NO" << endl;
                    }
                    cout << endl << endl;
//========================================================
                }
        if (!any) break;
    }
}

int main()
{
    unsigned int start_time =  clock(); // начальное врем

    edge temp;
    vector<edge> e;
    int n = 0, w = 0, i = 0, j = 0;

    cout<<"Количество вершин > "; cin>>n;

    for (i = 0; i < n; i++)
        for (j = 1; j<n; j++)
        {
            if (i < j) {
                cout << "Вес " << i << " -> " << j << " > ";
                cin >> w;
                if (w != 0) {   // нулевой вес = отсутствие связи
                    temp.a = i;
                    temp.b = j;
                    temp.cost = w;
                }
            }
        e.push_back(temp);
    }

    solve(e, n, 0);

    unsigned int end_time = clock(); // конечное время
    unsigned int search_time = end_time - start_time; // искомое время
    cout << search_time << ": " << search_time << endl;


    system("pause");
}