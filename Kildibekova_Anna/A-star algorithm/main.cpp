#include <iostream>
#include "A-star.h"
#include <chrono>

int main() {
    uint max_weight = 25;
    std::cout<<"____________________________________"<<std::endl;
    for (uint i = 2; i <= 32; i += 10) {
        std::cout << "for size = " << i << "\t and max_weight = " << max_weight << std::endl;
        Graph First(i, BAD_CASE, max_weight);
        //First.print_graph();

        std::chrono::high_resolution_clock::time_point Dijkstra_start_time = std::chrono::high_resolution_clock::now();
        First.DijkstraSearch(0, 1);
        std::chrono::high_resolution_clock::time_point Dijkstra_end_time = std::chrono::high_resolution_clock::now();

        std::chrono::high_resolution_clock::time_point AStar_start_time = std::chrono::high_resolution_clock::now();
        First.AStarSearch(0, 1);
        std::chrono::high_resolution_clock::time_point AStar_end_time = std::chrono::high_resolution_clock::now();

        auto Dijkstra_runtime = std::chrono::duration_cast<std::chrono::microseconds>(
                Dijkstra_end_time - Dijkstra_start_time).count();
        auto AStar_runtime = std::chrono::duration_cast<std::chrono::microseconds>(
                AStar_end_time - AStar_start_time).count();

        std::cout << "### Dijkstra runtime: " << Dijkstra_runtime << " us." << std::endl;
        std::cout << "### AStar runtime: " << AStar_runtime << " us." << std::endl;
        std::cout << std::endl << std::endl;
    }
    return 0;
}
