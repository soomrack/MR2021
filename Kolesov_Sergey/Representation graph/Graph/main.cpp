#include <iostream>
#include "Graph.h"

int main ()
{
    Graph g1(6, true, true);
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
    g1.print();

    return 0;
}