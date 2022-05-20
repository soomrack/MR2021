//
// Created by Аня on 19.03.2022.
//
#ifndef A_STAR_ALGORITHM_A_STAR_H
#define A_STAR_ALGORITHM_A_STAR_H
#include <iostream>
#include <string.h>

class Graph;
class Front;

enum type_of_graph {NETWORK, BAD_CASE};
enum type_of_search {AStar, Dijkstra};

class Graph {
public:
    Graph(uint size, type_of_graph, uint max_weight = 1);
    virtual ~Graph();
private:
    uint size;
    uint **adjacency_table;
    uint max_weight;
private:
    void memory_allocation();
    void free_memory();
    void network_graph();
    void bad_case_graph();
private:
    uint random_weight();
private:
    void get_heuristic_table();
    void heuristic_mem_alloc();
    void free_heuristic_mem();
    void create_heuristic_table();
public:
    void AStarSearch(uint start_node = 0, uint goal_node = 0);
    void DijkstraSearch(uint start_node = 0, uint goal_node = 0);
private:
    uint start = 0;              // Номер 1-го узла - 0
    uint goal = 0;
    uint **heuristic_table;
    uint* dist_from_start_to;
    uint* dist_estimate;
    uint* path;
    uint path_cost;
    uint path_length;
private:
    void find_AStar_path();
    uint dist_to_goal_from(uint node);
    void AStar_mem_alloc();
    void free_AStar_mem();
    void find_Dijkstra_path();
    void Dijkstra_mem_alloc();
    void free_Dijkstra_mem();
    void print_path_search_res(type_of_search algorithm);
    void get_path(const Front* currFront);
public:
    void print_graph();
public:
    friend class Front;
};

class Front {
private:
    explicit Front(const Graph * graph);
    virtual ~Front();
private:
    const Graph * graph;
    uint* front;
    uint front_pointer;       // Указатель на верх границы
    bool* visited;
private:
    void init_front();
    void get_front(uint current_node);
    void change_front(uint current_node);
    void clean_front();
    void memory_allocation();
    void free_memory();
public:
    friend class Graph;
};
#endif //A_STAR_ALGORITHM_A_STAR_H

