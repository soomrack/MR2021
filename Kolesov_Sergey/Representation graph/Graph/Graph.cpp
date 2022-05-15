//
// Created by Master on 21.03.2022.
//

#include "Graph.h"
#include <iostream>

void Graph::free_memory(){
    graph.clear();
    buf.clear();
    num_nodes = 0;
    num_edges = 0;
    type = EDGESLIST;
    properties.weighted = false;
    properties.directed = false;
    properties.multiple = false;
}

Graph::Graph(Graph &clone){
    graph      = clone.graph;
    properties = clone.properties;
    num_edges  = clone.num_edges;
    num_nodes  = clone.num_nodes;
    type       = clone.type;

}

Graph::Graph(Graph &&clone) noexcept{
    graph      = clone.graph;
    properties = clone.properties;
    num_edges  = clone.num_edges;
    num_nodes  = clone.num_nodes;
    type       = clone.type;
    clone.free_memory();
}

Graph& Graph::operator= (const Graph& clone){
    if (this == &clone)
        return *this;

    free_memory();
    graph      = clone.graph;
    properties = clone.properties;
    num_edges  = clone.num_edges;
    num_nodes  = clone.num_nodes;
    type       = clone.type;
    return *this;
}

Graph& Graph::operator= (const Graph&& clone) noexcept{
    graph      = clone.graph;
    properties = clone.properties;
    num_edges  = clone.num_edges;
    num_nodes  = clone.num_nodes;
    type       = clone.type;
    return *this;
}

Graph::Graph(unsigned int num_nodes, bool weighted, bool directed, bool multiple)
{
    this->num_edges = 0;
    this->num_nodes = num_nodes;
    properties.weighted = weighted;
    properties.directed = directed;
    properties.multiple = multiple;
}

Graph::Graph(unsigned int num_nodes, unsigned int num_edges, bool weighted,
                                               bool directed, bool multiple)
{
    this->num_edges = num_edges;
    this->num_nodes = num_nodes;
    properties.weighted = weighted;
    properties.directed = directed;
    properties.multiple = multiple;

    unsigned int x;
    buf.resize(2);
    if (weighted){
        buf.resize(3);
    }

    std::cout<<"Input "<<num_edges<<" edges"<<std::endl;
    for (int i = 0; i < num_edges; i++)
    {
        if (weighted){
            std::cin>>buf[0]>>buf[1]>>buf[2];
        }
        else{
            std::cin>>buf[0]>>buf[1];
        }
        graph.push_back(buf);
        if (!(directed)){
            x = buf[0];
            buf[0] = buf[1];
            buf[1] = x;
            graph.push_back(buf);
        }
    }
}

Graph::~Graph(){
    this->free_memory();
}

void Graph::add_edge(unsigned int begin, unsigned int end, unsigned int weight, bool direct)
{
    num_edges++;

    switch (type) {
        case ADJACENCY:
            graph[begin][end] += weight;
            if (!(direct)){
                graph[end][begin] += weight;
            }
            break;

        case INCIDENCE:
            for (int i = 0; i < num_nodes; i++){
                graph[i].push_back(0);
            }
            graph[begin][num_edges-1] = weight;
            if (direct){
                graph[end][num_edges-1] = -weight;
            }
            else{
                graph[end][num_edges-1] = weight;
            }
            break;

        case ADJACLIST:
            if (properties.weighted){
                graph[begin].push_back(end);
                graph[begin].push_back(weight);
                if (!(direct)){
                    graph[end].push_back(begin);
                    graph[end].push_back(weight);
                }
            }
            else{
                graph[begin].push_back(end);
                if (!(direct)){
                    graph[end].push_back(begin);
                }
            }
            break;

        case EDGESLIST:
            buf.resize(2);
            buf[0] = begin;
            buf[1] = end;
            if (properties.weighted){
                buf.resize(3);
                buf[2] = weight;
            }
            graph.push_back(buf);
            if ((!(direct)&(properties.directed))){
                unsigned int x = buf[0];
                buf[0] = buf[1];
                buf[1] = x;
                graph.push_back(buf);
                num_edges++;
            }
            break;
    }
}

void Graph::add_node()
{
    num_nodes++;
    switch (type) {
        case ADJACENCY:
            buf.resize(num_nodes - 1);
            std::fill(buf.begin(), buf.end(), 0);
            graph.push_back(buf);
            for (int i = 0; i < num_nodes; i++) {
                graph[i].push_back(0);
            }
            break;

        case INCIDENCE:
            for (int i = 0; i < num_edges; i++) {
                graph[i].push_back(0);
            }
            break;

        case ADJACLIST:
            buf.clear();
            graph.push_back(buf);
            break;

        case EDGESLIST:

            break;
    }
}

void Graph::delete_edge(unsigned int begin, unsigned int end, unsigned int weight, bool direct){
    num_edges--;
    switch (type) {
        case ADJACENCY:
            if (graph[begin][end] != 0) {
                graph[begin][end] -= weight;
            }
            if (!(direct)){
                delete_edge(end, begin, weight, true);
            }
            break;

        case INCIDENCE:
            for (int i = 0; i < num_edges; i++) {
                if (graph[i][begin] == weight){
                    if ((direct)&(graph[i][end] == -weight)){
                        graph.erase(graph.begin() + i);
                        break;
                    }
                    if ((!(direct))&(graph[i][end] == weight)){
                        graph.erase(graph.begin() + i);
                        break;
                    }
                }
            }
            break;

        case ADJACLIST:
            if (properties.weighted){
                for (int i = 0; i < graph[begin].size(); i+=2){
                    if ((graph[begin][i] == end)&(graph[begin][i+1] == weight)){
                        graph.erase(graph.begin() + i, graph.begin() + i + 2);
                        break;
                    }
                }
            }
            else{
                for (int i = 0; i < graph[begin].size(); i++){
                    if (graph[begin][i] == end){
                        graph.erase(graph.begin() + i);
                        break;
                    }
                }
            }
            if (!(direct)){
                delete_edge(end, begin, weight, true);
            }
            break;

        case EDGESLIST:
            for (int i = 0; i < graph.size(); i++){
                if ((graph[i][0] == begin)&(graph[i][1] == end)){
                    if (properties.weighted){
                        if (graph[i][2] == weight){
                            graph.erase(graph.begin() + i);
                            break;
                        }
                    }
                    else{
                        graph.erase(graph.begin() + i);
                        break;
                    }
                }
            }
            if ((properties.directed)&((!direct))){
                delete_edge(end, begin, weight, true);
            }
            break;
    }
}

void Graph::delete_node(unsigned int n)
{
    num_nodes--;
    if (n > num_nodes){
        return;
    }
    switch (type) {
        case ADJACENCY:
            graph.erase(graph.begin() + n);
            for (int i = 0; i < num_nodes; i++) {
                graph[i].erase(graph[i].begin() + n);
            }
            break;

        case INCIDENCE:
            for (int i = 0; i < num_edges; i++) {
                if (graph[i][n] != 0){
                    graph.erase(graph.begin() + i);
                    num_edges--;
                    i--;
                }
                else{
                    graph[i].erase(graph[i].begin() + n);
                }
            }
            break;

        case ADJACLIST:
            graph.erase(graph.begin() + n);
            for (int i = 0; i < num_nodes; i++) {
                if (properties.weighted){
                    for (int j = 0; j < graph[i].size(); j+=2) {
                        if (graph[i][j] == n){
                            graph[i].erase(graph[i].begin() + j, graph[i].begin() + j + 2);
                            j-=2;
                        }
                        if (graph[i][j] > n){
                            graph[i][j]--;
                        }
                    }
                }
                else{
                    for (int j = 0; j < graph[i].size(); j++) {
                        if (graph[i][j] == n){
                            graph[i].erase(graph[i].begin() + j);
                            j--;
                        }
                        if (graph[i][j] > n){
                            graph[i][j]--;
                        }
                    }
                }
            }
            break;

        case EDGESLIST:
            for (int i = 0; i < graph.size(); i++){
                if ((graph[i][0] == n)|(graph[i][1] == n)){
                    graph.erase(graph.begin() + i);
                    i--;
                }
                if (graph[i][0] > n){
                    graph[i][0] -= 1;
                }
                if (graph[i][1] > n){
                    graph[i][1] -= 1;
                }
            }
            break;
    }
}

void Graph::present_from_EL(PresentType type) {
    unsigned n;
    this->type = type;
    switch (type)
    {
        case ADJACENCY:
            if (properties.weighted & properties.multiple){
                std::cout << "This type of graph can't be present like adjacency matrix";
                break;
            }
            n = graph.size();
            buf.resize(num_nodes);
            std::fill(buf.begin(), buf.end(), 0);
            graph.resize(n + num_nodes);
            std::fill(graph.begin() + n, graph.end(), buf);
            for (int i = 0; i < n; i++){
                if (properties.weighted){
                    graph[n + graph[i][0]][graph[i][1]] += graph[i][2];
                    if (!(properties.directed)){
                        graph[n + graph[i][1]][graph[i][0]] += graph[i][2];
                    }
                }
                else{
                    graph[n + graph[i][0]][graph[i][1]]++;
                    if (!(properties.directed)){
                        graph[n + graph[i][1]][graph[i][0]]++;
                    }
                }
            }
            graph.erase(graph.begin(), graph.begin() + n);
            break;

        case INCIDENCE:
            n = graph.size();
            buf.resize(num_nodes);
            std::fill(buf.begin(), buf.end(), 0);
            graph.resize(n + num_edges);
            std::fill(graph.begin() + n, graph.end(), buf);
            for (int i = 0; i < n; i++){
                if (properties.weighted) {
                    graph[n + i][graph[i][0]] += graph[i][2];
                    graph[n + i][graph[i][1]] += graph[i][2];
                }
                else {
                    graph[n + i][graph[i][0]]++;
                    graph[n + i][graph[i][1]]++;
                }
                if (properties.directed){
                    graph[n + i][graph[i][1]]*=-1;
                }
            }
            graph.erase(graph.begin(), graph.begin() + n);
            break;

        case ADJACLIST:
            n = graph.size();
            buf.clear();
            graph.resize(n + num_nodes);
            std::fill(graph.begin() + n, graph.end(), buf);
            for (int i = 0; i < n; i++) {
                graph[n + graph[i][0]].push_back(graph[i][1]);
                if (properties.weighted) {
                    graph[n + graph[i][0]].push_back(graph[i][2]);
                }
                if (!(properties.directed)){
                    graph[n + graph[i][1]].push_back(graph[i][0]);
                    if (properties.weighted) {
                        graph[n + graph[i][1]].push_back(graph[i][2]);
                    }
                }
            }
            graph.erase(graph.begin(), graph.begin() + n);
            break;
        case EDGESLIST:
            break;
    }
}

void Graph::present_like_EL() {
    buf.resize(2);
    if (properties.weighted){
        buf.resize(3);
    }
    switch (this->type)
    {
        case ADJACENCY:
            for (int i = 0; i < num_nodes; i++) {
                for (int j = 0; j < num_nodes; j++) {
                    if (graph[i][j] != 0){
                        buf[0] = i;
                        buf[1] = j;
                        if (properties.weighted){
                            buf[2] = graph[i][j];
                        }
                        if (properties.multiple){
                            for (int k = 0; k < graph[i][j]; k++){
                                 graph.push_back(buf);
                            }
                        }
                        else{
                            graph.push_back(buf);
                        }
                        if (!(properties.directed)){
                            graph[j][i] = 0;
                        }
                    }
                }
            }
            graph.erase(graph.begin(), graph.begin() + num_nodes);
            num_edges = graph.size();
            break;

        case INCIDENCE:
            for (int i = 0; i < num_edges; i++) {
                buf[0] = -1;
                buf[1] = -1;
                for (int j = 0; j < num_nodes; j++) {
                    if (graph[i][j] > 0){
                        if (buf[0] >= 0){
                            buf[1] = j;
                            if (properties.directed){
                                graph.push_back(buf);
                                buf[1] = buf[0];
                                buf[0] = j;
                                graph.push_back(buf);
                                break;
                            }
                        }
                        else{
                            buf[0] = j;
                        }
                        if (properties.weighted){
                            buf[2] = graph[i][j];
                        }
                    }
                    if (graph[i][j] < 0){
                        buf[1] = j;
                    }
                    if ((buf[0]>=0)&(buf[1]>=0)){
                        graph.push_back(buf);
                        break;
                    }
                }
            }
            graph.erase(graph.begin(), graph.begin() + num_edges);
            num_edges = graph.size();
            break;

        case ADJACLIST:
            for (int i = 0; i < num_nodes; i++) {
                buf[0] = i;
                if (properties.weighted){
                    for (int j = 0; j < graph[i].size(); j+=2) {
                        buf[1] = graph[i][j];
                        buf[2] = graph[i][j+1];
                        graph.push_back(buf);
                        if (!(properties.directed)){
                            for (int k = 0; k < graph[buf[1]].size(); k+=2){
                                if ((graph[buf[1]][k] == i)&(graph[buf[1]][k+1] == buf[2])){
                                    graph[buf[1]].erase(graph[buf[1]].begin() + k, graph[buf[1]].begin() + k + 2);
                                }
                            }
                        }

                    }
                }
                else{
                    for (int j = 0; j < graph[i].size(); j++) {
                        buf[1] = graph[i][j];
                        graph.push_back(buf);
                        if (!(properties.directed)){
                            for (int k = 0; k < graph[buf[1]].size(); k++){
                                if (graph[buf[1]][k] == i){
                                    graph[buf[1]].erase(graph[buf[1]].begin() + k);
                                }
                            }
                        }
                    }
                }

            }
            graph.erase(graph.begin(), graph.begin() + num_nodes);
            num_edges = graph.size();
            break;

        case EDGESLIST:
            break;
    }
    this->type = EDGESLIST;
}

void Graph::represent(PresentType type) {
    this->present_like_EL();
    this->present_from_EL(type);
}

void Graph::print(){
    std::cout << num_nodes << "  " << num_edges << "\n";
    switch (type)
    {
        case ADJACENCY:
            for (int i = 0; i < num_nodes; i++){
                for (int j = 0; j < num_nodes; j++){
                    std::cout << graph[i][j] << "  ";
                }
                std::cout << '\n';
            }
            std::cout << '\n';
            break;
        case INCIDENCE:
            for (int i = 0; i < num_nodes; i++){
                for (int j = 0; j < num_edges; j++){
                    std::cout << graph[j][i] << "  ";
                }
                std::cout << '\n';
            }
            std::cout << '\n';
            break;
        case ADJACLIST:
            for (int i = 0; i < num_nodes; i++){
                for (int j = 0; j < graph[i].size(); j++){
                    std::cout << graph[i][j] << "  ";
                }
                std::cout << '\n';
            }
            std::cout << '\n';
            break;
        case EDGESLIST:
            for (int i = 0; i < graph.size(); i++){
                for (int j = 0; j < graph[i].size(); j++){
                    std::cout << graph[i][j] << "  ";
                }
                std::cout << '\n';
            }
            std::cout << '\n';
            break;
    }
}

