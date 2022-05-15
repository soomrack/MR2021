#include "../graph.h"
#include <iostream>


void empty_graph_test();
void graph_without_edges_test(int num_of_vertices);
void chain_graph_test(int num_of_vertices);
void dense_graph_test(int num_of_vertices);


int main() {

    std::cout << "====== Empty graph test ======" << std::endl;
    empty_graph_test();


    std::cout << "====== Graph without edges test ======" << std::endl;
    graph_without_edges_test(1);
    graph_without_edges_test(2);
    graph_without_edges_test(3);
    graph_without_edges_test(4);


    std::cout << "====== Chain graph test ======" << std::endl;
    chain_graph_test(3);
    chain_graph_test(5);
    chain_graph_test(10);


    std::cout << "====== Dense graph test ======" << std::endl;
    dense_graph_test(3);
    dense_graph_test(10);
    dense_graph_test(20);

    return 0;
}


void empty_graph_test() {
    Graph<int> graph;
    auto bridges = graph.tarjans_find_bridges();

    if (!bridges.empty()) {
        std::cout << "Error with empty graph" << std::endl;
        exit(1);
    }
    std::cout << "Empty graph correctly has zero bridges" << std::endl;
}


void graph_without_edges_test(int num_of_vertices) {
    Graph<int> graph(num_of_vertices);
    auto bridges = graph.tarjans_find_bridges();

    graph.actualize_adjacency_matrix(); // change

    if (!bridges.empty()) {
        std::cout << "Graph with " << num_of_vertices << "vertices ";
        std::cout << "and without edges incorrectly has non-zero bridges" << std::endl;
        exit(1);
    }

    std::cout << "Graph correctly has " << num_of_vertices - 1 << " bridges" << std::endl;
}


void chain_graph_test(int num_of_vertices) {
    Graph<int> graph(num_of_vertices);
    for (int i = 0; i < num_of_vertices - 1; i++) {
        graph.add_edge(i, i + 1);
    }
    graph.actualize_adjacency_matrix(); // change
    auto bridges = graph.tarjans_find_bridges();

    if (bridges.size() == num_of_vertices - 1) {
        std::cout << "Graph correctly has " << num_of_vertices - 1 << " bridges" << std::endl;
        return;
    }

    std::cout << "Error with chain graph with " << num_of_vertices << "vertices" << std::endl;
    exit(1);
}


void dense_graph_test(int num_of_vertices) {
    Graph<int> graph(num_of_vertices);
    for (int i = 0; i < num_of_vertices; i++) {
        for (int j = i + 1; j < num_of_vertices; j++) {
            graph.add_edge(i, j);
        }
    }
    graph.actualize_adjacency_matrix(); // change
    auto bridges = graph.tarjans_find_bridges();

    int correct_num_of_bridges = 0;
    if (bridges.size() == correct_num_of_bridges) {
        std::cout << "Graph correctly has " << correct_num_of_bridges << " bridges" << std::endl;
        return;
    }

    std::cout << "Error with dense graph with " << num_of_vertices << " vertices" << std::endl;
    std::cout << "Correct: " << correct_num_of_bridges << std::endl;
    std::cout << "Got: " << bridges.size() << std::endl;
    exit(1);
}
