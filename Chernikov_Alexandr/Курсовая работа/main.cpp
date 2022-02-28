#include<iostream>
#include <list>
#include <vector>
#include <ctime>
#include <algorithm>
#include <cmath>
#include "graph.h"

void tbfa_measure_time(int sum_of_edges_and_vertices){
    Graph g = create_random_graph(sum_of_edges_and_vertices);

    int start = clock();
    g.find_bridges();
    int end = clock();
    std::cout << "elements: " << g.get_number_of_vertices() + g.get_number_of_edges() << ", milliseconds: ";
    std::cout << (end - start) * 1000 / CLOCKS_PER_SEC << std::endl;
}

int main()
{
    srand(123456);

    tbfa_measure_time(100000);
    tbfa_measure_time(200000);
    tbfa_measure_time(300000);
    tbfa_measure_time(400000);
    tbfa_measure_time(500000);
    tbfa_measure_time(600000);
    tbfa_measure_time(700000);
    tbfa_measure_time(800000);
    tbfa_measure_time(900000);
    tbfa_measure_time(1000000);

    return 0;
}

