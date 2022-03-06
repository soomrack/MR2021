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

//    tbfa_measure_time(10000);
//    tbfa_measure_time(20000);
//    tbfa_measure_time(30000);
//    tbfa_measure_time(40000);
//    tbfa_measure_time(50000);
//    tbfa_measure_time(60000);
//    tbfa_measure_time(70000);
//    tbfa_measure_time(80000);
//    tbfa_measure_time(90000);
//    tbfa_measure_time(100000);
//    tbfa_measure_time(200000);
//    tbfa_measure_time(300000);
//    tbfa_measure_time(400000);
//    tbfa_measure_time(500000);
//    tbfa_measure_time(600000);
//    tbfa_measure_time(700000);
//    tbfa_measure_time(800000);
    tbfa_measure_time(900000);
    tbfa_measure_time(1000000);

    return 0;
}


//    Graph graph1 = create_random_graph(10);
//    std::cout << graph1.get_number_of_edges() + graph1.get_number_of_vertices() << '\n';
//
//
//    // Create graphs given in above diagrams
//    std::cout << "\nBridges in first graph \n";
//    Graph g1(5);
//    g1.add_edge(1, 0);
//    g1.add_edge(0, 2);
//    g1.add_edge(2, 1);
//    g1.add_edge(0, 3);
//    g1.add_edge(3, 4);
//    g1.find_bridges();
//
//    std::cout << "\nBridges in second graph \n";
//    Graph g2(4);
//    g2.add_edge(0, 1);
//    g2.add_edge(1, 2);
//    g2.add_edge(2, 3);
//    g2.find_bridges();
//
//    std::cout << "\nBridges in third graph \n";
//    Graph g3(7);
//    g3.add_edge(0, 1);
//    g3.add_edge(1, 2);
//    g3.add_edge(2, 0);
//    g3.add_edge(1, 3);
//    g3.add_edge(1, 4);
//    g3.add_edge(1, 6);
//    g3.add_edge(3, 5);
//    g3.add_edge(4, 5);
//    g3.find_bridges();