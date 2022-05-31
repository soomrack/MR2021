#include <iostream>
#include "Graph.h"
#include "iostream"
#include "time.h"

int main ()
{
    unsigned int n1;
    unsigned int n2;
    Graph g1(1000,false,true,true);
    clock_t t = clock();
    for (int i = 0; i < 102400000; i++)
    {
        n1 = rand() % 1000;
        n2 = rand() % 1000;
        g1.add_edge(n1, n2, false, true);
    }
    t = clock() - t;
    t = (float)(t);// (CLOCKS_PER_SEC))*1000;
    std::cout << t << " microsec"<<"\n";

    g1.represent(ADJACLIST);
    t = clock();
    for (int i = 0; i < 10; i++)
    {
        g1.delete_edge(rand() % 1000, rand() % 1000);
    }
    t = clock() - t;
    t = (float)(t); // (CLOCKS_PER_SEC))*1000;
    std::cout << t << " microsec";



/*    Graph g1(6, true, true);
    g1.add_edge(0,1, 1, true);
    g1.add_edge(0,4, 2, true);
    g1.add_edge(1,2, 3, true);
    g1.add_edge(2,3, 4, true);
    g1.add_edge(3,4, 5, true);
    g1.add_edge(1,4, 6, true);
    g1.add_edge(3,5, 7);

    g1.print();
    g1.represent(ADJACENCY);
    g1.print();
    g1.represent(INCIDENCE);
    g1.print();
    g1.represent(ADJACLIST);
    g1.print();
    g1.represent(EDGESLIST);
    g1.print(); */

    return 0;
}