#include "../graph.h"
#include <iostream>


# define CHECK_EQUAL(expected, got, test_name) {                    \
    if ((got) == (expected)) {                                      \
        std::cout << test_name << ":\tpass" << std::endl;           \
    } else {                                                        \
        std::cout << test_name << ":\tfailed" << std::endl;         \
        std::cout << "Expected: " << expected << std::endl;         \
        std::cout << "Got: " << got << std::endl;                   \
        exit(1);                                                    \
    }                                                               \
}                                                                   \


# define CHECK_NOT_EQUAL(expected, got, test_name) {                \
    if ((got) != (expected)) {                                      \
        std::cout << test_name << ":\tpass" << std::endl;           \
    } else {                                                        \
        std::cout << test_name << ":\tfailed" << std::endl;         \
        std::cout << "Expected: " << expected << std::endl;         \
        std::cout << "Got: " << got << std::endl;                   \
        exit(1);                                                    \
    }                                                               \
}                                                                   \


void vertex_add_edge_test();
void vertex_remove_edge_test();
void find_vertex_test();
void add_edge_test();
void remove_edge_test();
void add_vertex_test();
void remove_vertex_test();
void actualize_adjacency_list_test();
void actualize_adjacency_matrix();


int main() {

    vertex_add_edge_test();
    vertex_remove_edge_test();

    find_vertex_test();
    add_edge_test();
    remove_edge_test();
    add_vertex_test();
    add_vertex_test();

    return 0;
}


void vertex_add_edge_test() {

    std::cout << std::endl << "====== Vertex add edge test ======" << std::endl;

    Vertex<int> vtx;
    size_t num_of_neighbors = 0;

    num_of_neighbors = vtx.get_edges().size();
    CHECK_EQUAL(0, num_of_neighbors, "Vertex has 0 edges");

    Vertex<int> neighbor_1;
    vtx.add_edge(&neighbor_1, 0);
    num_of_neighbors = vtx.get_edges().size();
    CHECK_EQUAL(1, num_of_neighbors, "Vertex has 1 edges after adding");

    Vertex<int> neighbor_2;
    vtx.add_edge(&neighbor_2, 0);
    num_of_neighbors = vtx.get_edges().size();
    CHECK_EQUAL(2, num_of_neighbors, "Vertex has 2 edges after adding");
}



void vertex_remove_edge_test() {

    std::cout << std::endl << "====== Vertex remove edge test ======" << std::endl;

    Vertex<int> vtx;
    size_t num_of_neighbors = 0;

    Vertex<int> neighbor_1;
    Vertex<int> neighbor_2;
    vtx.add_edge(&neighbor_1, 0);
    vtx.add_edge(&neighbor_2, 0);
    std::cout << vtx.get_edges().size() << std::endl;

    vtx.remove_edge(&neighbor_2);
    num_of_neighbors = vtx.get_edges().size();
    CHECK_EQUAL(1, num_of_neighbors, "Neighbor_2 removed");

    Vertex<int> neighbor_3;
    vtx.remove_edge(&neighbor_3);
    num_of_neighbors = vtx.get_edges().size();
    CHECK_EQUAL(1, num_of_neighbors, "Neighbor_3 did not remove");

    vtx.remove_edge(&neighbor_1);
    num_of_neighbors = vtx.get_edges().size();
    CHECK_EQUAL(0, num_of_neighbors, "Neighbor_2 removed");
}


void find_vertex_test() {

    std::cout << std::endl << "====== Find vertex test ======" << std::endl;

    Graph<int> graph(2);
    std::list<Vertex<int>*> vertices = graph.get_vertices();

    auto it = vertices.begin();
    Vertex<int>* vtx = graph.find_vertex(0);
    CHECK_EQUAL(*it, vtx, "Find vertex 0");

    it++;
    vtx = graph.find_vertex(1);
    CHECK_EQUAL(*it, vtx, "Find vertex 1");

    vtx = graph.find_vertex(2);
    CHECK_EQUAL(0, vtx, "Correctly find unknown vertex 2");
}


void add_edge_test() {

    std::cout << std::endl << "====== Add edge test ======" << std::endl;

    /* DIRECTED EDGE */

    Graph<int> graph1(2);
    std::list<Vertex<int>*> vertices = graph1.get_vertices();
    Vertex<int>* v0 = graph1.find_vertex(0);
    Vertex<int>* v1 = graph1.find_vertex(1);

    CHECK_EQUAL(0, v0->get_edges().size(), "Vertex 0 has no edges in initial graph");
    CHECK_EQUAL(0, v1->get_edges().size(), "Vertex 1 has no edges in initial graph");

    int ret = graph1.add_edge(0, 1, 0, DIRECTED);
    CHECK_EQUAL(0, ret, "Success return is 0");
    CHECK_EQUAL(1, v0->get_edges().size(), "Vertex 0 has neighbor");
    CHECK_EQUAL(v1, v0->get_edges().begin()->get_neighbor(), "Neighbor of vertex 0 is vertex 1");
    CHECK_EQUAL(0, v1->get_edges().size(), "Vertex 1 hasn't neighbor");

    ret = graph1.add_edge(0, 0, 0, DIRECTED);
    CHECK_EQUAL(1, ret, "Fail return is 1");
    CHECK_EQUAL(1, v0->get_edges().size(), "Vertex 0 has neighbor");
    CHECK_EQUAL(v1, v0->get_edges().begin()->get_neighbor(), "Neighbor of vertex 0 is vertex 1");
    CHECK_EQUAL(0, v0->get_edges().begin()->get_distance(), "Distance between vertex 0 and vertex 1 is zero");

    CHECK_EQUAL(0, v1->get_edges().size(), "Vertex 1 hasn't neighbor");

    ret = graph1.add_edge(1, 0, 0, DIRECTED);
    CHECK_EQUAL(0, ret, "Success return is 0");
    CHECK_EQUAL(1, v0->get_edges().size(), "Vertex 0 has neighbor");
    CHECK_EQUAL(v1, v0->get_edges().begin()->get_neighbor(), "Neighbor of vertex 0 is vertex 1");
    CHECK_EQUAL(0, v0->get_edges().begin()->get_distance(), "Distance between vertex 0 and vertex 1 is zero");

    CHECK_EQUAL(1, v1->get_edges().size(), "Vertex 1 has neighbor");
    CHECK_EQUAL(v0, v1->get_edges().begin()->get_neighbor(), "Neighbor of vertex 1 is vertex 0");
    CHECK_EQUAL(0, v1->get_edges().begin()->get_distance(), "Distance between vertex 1 and vertex 0 is zero");

    ret = graph1.add_edge(0, 1, 1, DIRECTED);
    CHECK_EQUAL(0, ret, "Success return is 0");
    CHECK_EQUAL(1, v0->get_edges().size(), "Vertex 0 has neighbor");
    CHECK_EQUAL(v1, v0->get_edges().begin()->get_neighbor(), "Neighbor of vertex 0 is vertex 1");
    CHECK_EQUAL(1, v0->get_edges().begin()->get_distance(), "Distance between vertex 0 and vertex 1 is one");

    CHECK_EQUAL(1, v1->get_edges().size(), "Vertex 1 has neighbor");
    CHECK_EQUAL(v0, v1->get_edges().begin()->get_neighbor(), "Neighbor of vertex 1 is vertex 0");
    CHECK_EQUAL(0, v1->get_edges().begin()->get_distance(), "Distance between vertex 1 and vertex 0 is zero");


    /* UNDIRECTED EDGE */

    Graph<int> graph2(2);
    vertices = graph1.get_vertices();
    v0 = graph1.find_vertex(0);
    v1 = graph1.find_vertex(1);

    graph1.add_edge(1, 0, 0, UNDIRECTED);

    CHECK_EQUAL(1, v0->get_edges().size(), "Vertex 0 has neighbor");
    CHECK_EQUAL(v1, v0->get_edges().begin()->get_neighbor(), "Neighbor of vertex 0 is vertex 1");
    CHECK_EQUAL(0, v0->get_edges().begin()->get_distance(), "Distance between vertex 0 and vertex 1 is zero");

    CHECK_EQUAL(1, v1->get_edges().size(), "Vertex 1 has neighbor");
    CHECK_EQUAL(v0, v1->get_edges().begin()->get_neighbor(), "Neighbor of vertex 1 is vertex 0");
    CHECK_EQUAL(0, v1->get_edges().begin()->get_distance(), "Distance between vertex 1 and vertex 0 is zero");
}


void remove_edge_test() {
    std::cout << std::endl << "====== Remove edge test ======" << std::endl;

    Graph<int> graph1(2);
    std::list<Vertex<int>*> vertices = graph1.get_vertices();
    Vertex<int>* v0 = graph1.find_vertex(0);
    Vertex<int>* v1 = graph1.find_vertex(1);

    graph1.add_edge(0, 1, 0, UNDIRECTED);
    int ret = graph1.remove_edge(0, 1, DIRECTED);
    CHECK_EQUAL(0, ret, "Success return is 0");
    CHECK_EQUAL(0, v0->get_edges().size(), "Vertex 0 has no neighbors");
    CHECK_EQUAL(1, v1->get_edges().size(), "Vertex 1 has neighbor");
    CHECK_EQUAL(v0, v1->get_edges().begin()->get_neighbor(), "Neighbor of vertex 1 is vertex 0");
    CHECK_EQUAL(0, v1->get_edges().begin()->get_distance(), "Distance between vertex 1 and vertex 0 is zero");

    ret = graph1.remove_edge(0, 0, DIRECTED);
    CHECK_EQUAL(1, ret, "Fail return is 1");
    CHECK_EQUAL(0, v0->get_edges().size(), "Vertex 0 has no neighbors");
    CHECK_EQUAL(1, v1->get_edges().size(), "Vertex 1 has neighbor");
    CHECK_EQUAL(v0, v1->get_edges().begin()->get_neighbor(), "Neighbor of vertex 1 is vertex 0");
    CHECK_EQUAL(0, v1->get_edges().begin()->get_distance(), "Distance between vertex 1 and vertex 0 is zero");

    ret = graph1.remove_edge(1, 0, DIRECTED);
    CHECK_EQUAL(0, v0->get_edges().size(), "Vertex 0 has no neighbors");
    CHECK_EQUAL(0, v1->get_edges().size(), "Vertex 1 has no neighbors");

    ret = graph1.remove_edge(2, 3, DIRECTED);
    CHECK_EQUAL(0, v0->get_edges().size(), "Vertex 0 has no neighbors");
    CHECK_EQUAL(0, v1->get_edges().size(), "Vertex 1 has no neighbors");

}


void add_vertex_test() {

    std::cout << std::endl << "====== Add vertex test ======" << std::endl;

    Graph<int> graph(0);
    CHECK_EQUAL(0, graph.find_vertex(0), "Graph(0) has no vertex with id=0");

    graph.add_vertex();
    CHECK_NOT_EQUAL(0, graph.find_vertex(0), "After adding vertex graph has vertex with id=0");
    CHECK_EQUAL(0, graph.find_vertex(1), "But doesnt have vertex with id=1");

    graph.add_vertex();
    CHECK_NOT_EQUAL(0, graph.find_vertex(0), "After one more adding vertex graph has vertex with id=0");
    CHECK_NOT_EQUAL(0, graph.find_vertex(1), "After one more adding vertex graph has vertex with id=1");
    CHECK_EQUAL(0, graph.find_vertex(2), "But doesnt have vertex with id=2");
}






