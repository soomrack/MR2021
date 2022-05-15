//
// Created by Master on 21.03.2022.
//
#include <iostream>
#include <vector>

#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H

typedef enum{
    ADJACENCY,
    INCIDENCE,
    ADJACLIST,
    EDGESLIST
} PresentType;


class Graph {
private:
    struct edge{
        unsigned int begin;
        unsigned int end;
        double weigth;
    };

    struct property{
        bool directed = false;
        bool weighted = false;
        bool multiple = false;
  };

    struct property properties;
    PresentType type = EDGESLIST;
    std::vector< std::vector< int > > graph;
    std::vector<int> buf;
    unsigned int num_edges = 0;
    unsigned int num_nodes = 0;

public:
    Graph(Graph& clone);
    Graph(Graph&& clone) noexcept;
    Graph(unsigned int num_nodes, bool weighted = false,
          bool directed = false, bool multiple = false); // Only num_nodes Nodes without edges
    Graph(unsigned int num_nodes, unsigned int num_edges, bool weighted = false,
          bool directed = false, bool multiple = false); // num_nodes nodes and read num_edges edges
    Graph& operator= (const Graph&  clone);
    Graph& operator= (const Graph&& clone) noexcept;
    ~Graph();

public:
    void add_edge(unsigned int begin, unsigned int end, unsigned int weight = 1, bool direct = false);
    void add_node();
    void delete_node(unsigned int n);
    void delete_edge(unsigned int begin, unsigned int end, unsigned int weight = 1, bool direct = false);
    void represent(PresentType type);
    void present_like_EL();
    void present_from_EL(PresentType type);
    void print();
    void free_memory();

};

#endif //GRAPH_GRAPH_H
