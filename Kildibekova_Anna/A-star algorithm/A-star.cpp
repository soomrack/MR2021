#include "A-star.h"

// TODO: массив from[size] с адресом предыдущего узла (возможно)

Graph::Graph(uint size, type_of_graph type, uint max_weigh) {
    this->size = size;
    this->max_weight = max_weigh;
    memory_allocation();
    switch(type) {
        case NETWORK: network_graph();
            break;
        case BAD_CASE: bad_case_graph();
            break;
        default:
            std::cout<<"Некорректный тип графа"<<std::endl;
            free_memory();
            return;
    }
    get_heuristic_table();
}

Graph::~Graph() {
    free_memory();
    free_heuristic_mem();
}

void Graph::memory_allocation() {
    adjacency_table = new uint* [size];
    for (uint col = 0; col < size; col++) {
        adjacency_table[col] = new uint[size];
    }
}

void Graph::free_memory() {
    for (uint col = 0; col < size; col++) {
        free(adjacency_table[col]);
    }
    free(adjacency_table);
    size = 0;
    max_weight = 0;
}

void Graph::network_graph() {
    for (uint row = 0; row < size; row++) {
        for (uint col = 0; col < size; col++) {
            adjacency_table[row][col] = random_weight();
        }
    }
    for (uint node = 0; node < size; node++) {
        adjacency_table[node][node] = 0;
    }
}

void Graph::bad_case_graph() {
    network_graph();
    for (uint row = 0; row < size; row++) {
        for (uint col = 0; col < size; col++) {
            adjacency_table[row][col] *= rand() % (1 + 1);;
        }
    }
    for (uint node = 0; node < size; node++) {
        adjacency_table[node][node] = 0;
    }
}

void Graph::get_heuristic_table() {
    heuristic_mem_alloc();
    create_heuristic_table();
//    std::cout<<"Graph::get_heuristic_table passed"<<std::endl;  //todo
}

void Graph::heuristic_mem_alloc() {
    heuristic_table = new uint* [size];
    for (uint col = 0; col < size; col++) {
        heuristic_table[col] = new uint[size];
    }
}

void Graph::free_heuristic_mem() {
    for (uint col = 0; col < size; col++) {
        free(heuristic_table[col]);
    }
    free(heuristic_table);
}

void Graph::create_heuristic_table() {
    for (uint row = 0; row < size; row++) {
        for (uint col = 0; col < size; col++) {
            heuristic_table[row][col] = 0;
        }
    }


    for (uint node = 0; node < size; node++) {
        start = node;
        uint curr_node = node;
        uint next_node = node;

        Front hFront (this);
        hFront.init_front();

        while (hFront.front_pointer > 0) {
            hFront.change_front(curr_node);
            hFront.get_front(curr_node);
            next_node = hFront.front[0];
            for (uint i = 0; i < hFront.front_pointer; i++) {
                if (adjacency_table[curr_node][hFront.front[i]]) {
                    uint temp_length = heuristic_table[node][curr_node] + 1;
                    if (!heuristic_table[node][hFront.front[i]] ||
                        temp_length < heuristic_table[node][hFront.front[i]]) {
                        heuristic_table[node][hFront.front[i]] = temp_length;
                    }
                }
            }
            curr_node = next_node;
        }
    }
    start = 0;

    //TODO убрать
//    std::cout<<"heuristic_table:"<<"\n";
//    for (uint row = 0; row < size; row++) {
//        for (uint col = 0; col < size; col++) {
//            std::cout<<heuristic_table[row][col]<<"\t";
//        }
//        std::cout<<std::endl;
//    }
}

uint Graph::random_weight() {
    uint weight = rand() % (max_weight + 1);
    return weight;
}

void Graph::print_graph() {
    for (uint row = 0; row < size; row++) {
        for (uint col = 0; col < size; col++) {
            std::cout<<adjacency_table[row][col]<<"\t";
        }
        std::cout<<std::endl;
    }
}


void Graph::print_path_search_res(type_of_search algorithm) {
    std::string alg_name;
    switch (algorithm) {
        case AStar:alg_name = "A-star";
            break;
        case Dijkstra:alg_name = "Dijkstra";
            break;
        default:alg_name = "Unknown algorithm";
    }

    if (!path_length) {
        std::cout<<alg_name<<" path no found"<<std::endl;
        return;
    }
    std::cout<<alg_name<<" cost: "<<path_cost<<std::endl;
    std::cout<<alg_name<<" length: "<<path_length<<std::endl;
    std::cout<<alg_name<<" path: \t";
    for (uint node = 0; node < path_length - 1; node++) {
        std::cout<<path[node]<<" -> ";
    }
    std::cout<<path[path_length - 1]<<std::endl<<std::endl;
}


void Graph::AStarSearch(uint start_node, uint goal_node) {
    if (start_node > size - 1) {return;}
    if (goal_node > size - 1) {return;}
    this->start = start_node;
    this->goal = goal_node;
    AStar_mem_alloc();
    find_AStar_path();
//    std::cout<<"Graph::find_AStar_path passed"<<std::endl;  //todo
    print_path_search_res(AStar);
    free_AStar_mem();
}

void Graph::find_AStar_path() {     // TODO: Упростить читаемость
    if (start == goal) {return;}

    path_cost = 0;
    path_length = 0;
    //memset(dist_from_start_to, 0, size);     TODO ???
    //memset(dist_estimate, 0, size);
    for (uint node = 0; node < size; node++) {
        dist_from_start_to[node] = 0;
        dist_estimate[node] = 0;
    }

    uint min_dist = max_weight + size;
    uint current_node = start;
    uint node_to_visit = start;

    Front currFront (this);
    currFront.init_front();
    dist_estimate[start] = dist_from_start_to[start] + dist_to_goal_from(start);

    while (currFront.front_pointer > 0) {
        currFront.change_front(current_node);
        currFront.get_front(current_node);
        node_to_visit = currFront.front[0];
        for (uint i = 0; i < currFront.front_pointer; i++) {                            // Для первого узла
            // foo
            if (adjacency_table[current_node][currFront.front[i]]) {
                uint temp_dist_from_start = dist_from_start_to[current_node]
                                            + adjacency_table[current_node][currFront.front[i]];
                if (!dist_from_start_to[currFront.front[i]] ||
                    dist_from_start_to[currFront.front[i]] > temp_dist_from_start) {
                    dist_from_start_to[currFront.front[i]] = temp_dist_from_start;           // Если к узлу подошли с нескольких сторон
                    dist_estimate[currFront.front[i]] = dist_from_start_to[currFront.front[i]]
                                                        + dist_to_goal_from(currFront.front[i]);
                }
            }
            // foo
            if (min_dist > dist_estimate[currFront.front[i]]) {
                min_dist = dist_estimate[currFront.front[i]];
                node_to_visit = currFront.front[i];
            }
        }
        // take_next_node
        current_node = node_to_visit;
        if (current_node == goal) {
            currFront.clean_front();
            path_cost = dist_from_start_to[current_node];
            path = new uint [size];
            for (uint node = 0; node < size; node++) {
                path[node] = 0;
            }
            //memset(path, 0, size);              TODO
            get_path(&currFront);
            return;}
        min_dist += max_weight + size;
    }
}

uint Graph::dist_to_goal_from(uint node) {
    return (uint)((float)heuristic_table[node][goal] * (1.0 + (float)max_weight * 0.005f));
}

void Graph::AStar_mem_alloc() {
    dist_from_start_to = new uint [size];
    dist_estimate = new uint [size];
//    std::cout<<"Graph::AStar_mem_alloc passed"<<std::endl;  //todo
}

void Graph::free_AStar_mem() {
    start = 0;
    goal = 0;
    free(path);
    free(dist_from_start_to);
    free(dist_estimate);
    path_cost = 0;
    path_length = 0;
//    std::cout<<"Graph::free_AStar_mem passed"<<std::endl;  //todo
}

void Graph::DijkstraSearch(uint start_node, uint goal_node) {
    if (start_node > size - 1) {return;}
    if (goal_node > size - 1) {return;}
    this->start = start_node;
    this->goal = goal_node;
    Dijkstra_mem_alloc();
    find_Dijkstra_path();
    print_path_search_res(Dijkstra);
    free_Dijkstra_mem();
}
// ^   ^    ____________
// ='t'=  < MEOW~ ~ ~ ~ |
// u   u S  ------------
void Graph::find_Dijkstra_path() {     // TODO: Упростить читаемость
    if (start == goal) {return;}

    path_cost = 0;
    path_length = 0;
    for (uint node = 0; node < size; node++) {
        dist_from_start_to[node] = 0;
    }
    //memset(dist_from_start_to, 0, size);    TODO

    uint min_dist = max_weight;
    uint current_node = start;
    uint node_to_visit = start;

    Front currFront (this);
    currFront.init_front();

    while (currFront.front_pointer > 0) {
        currFront.change_front(current_node);
        currFront.get_front(current_node);
        node_to_visit = currFront.front[0];
        for (uint i = 0; i < currFront.front_pointer; i++) {
            if (adjacency_table[current_node][currFront.front[i]]) {
                uint temp_dist = dist_from_start_to[current_node]
                                 + adjacency_table[current_node][currFront.front[i]];
                if (!dist_from_start_to[currFront.front[i]] ||
                    dist_from_start_to[currFront.front[i]] > temp_dist) {
                    dist_from_start_to[currFront.front[i]] = temp_dist;           // Если к узлу подошли с нескольких сторон
                }
            }
            if (min_dist > dist_from_start_to[currFront.front[i]]) {
                min_dist = dist_from_start_to[currFront.front[i]];
                node_to_visit = currFront.front[i];
            }
        }
        // take_next_node
        current_node = node_to_visit;
        if (current_node == goal) {
            currFront.clean_front();
            path_cost = dist_from_start_to[current_node];
            path = new uint [size];
            for (uint node = 0; node < size; node++) {
                path[node] = 0;
            }
            //memset(path, 0, size);                      TODO
            get_path(&currFront);
            return;}
        min_dist += max_weight;
    }
}

void Graph::get_path(const Front* currFront) {
uint current_node = goal;
    path [0] = goal;
    uint i = 0;
    while (current_node != start) {
        for (uint prev_node = 0; prev_node < size; prev_node++) {
            if (currFront->visited[prev_node] && adjacency_table[prev_node][current_node]
                && (dist_from_start_to[prev_node] + adjacency_table[prev_node][current_node]
                    == dist_from_start_to[current_node])) {
                i++;
                path[i] = prev_node;
                current_node = prev_node;
                prev_node = size - 1;
            }
        }
    }
    //reflect path      // TODO foo
    path_length = i;
    for (; i > path_length/2; i --) {
        uint temp = path[path_length - i];
        path[path_length - i] = path[i];
        path[i] = temp;
    }
    path_length ++;
}

void Graph::Dijkstra_mem_alloc() {
    dist_from_start_to = new uint [size];
}

void Graph::free_Dijkstra_mem() {
    start = 0;
    goal = 0;
    free(path);
    free(dist_from_start_to);
    path_cost = 0;
    path_length = 0;
}

//TODO: rename to Queue ?
/// class Front ///

Front::Front(const Graph * graph) {
    this->graph = graph;
    memory_allocation();
}

Front::~Front() {
    free_memory();
}

void Front::memory_allocation() {
    front = new uint [graph->size];
    visited = new bool [graph->size];
    front_pointer = 0;
}

void Front::free_memory() {
    free(front);
    free(visited);
    front_pointer = 0;
}

void Front::init_front() {
    for (uint node = 0; node < graph->size; node++) {
        visited[node] = false;
        front[node] = 0;
    }
    front[0] = graph->start;
    front_pointer = 1;
    visited[graph->start] = true;
//    dist_from_start_to[graph->start] = 0;                        // ???
}

void Front::get_front(uint current_node) {
    for (uint node = 0; node < graph->size; node++) {
        if (!visited[node] && graph->adjacency_table[current_node][node]) {
            visited[node] = true;
            front[front_pointer] = node;
            front_pointer++;
        }
    }
}

void Front::change_front(uint current_node) {
    for (uint i = 0; i < front_pointer; i++) {
        if (front[i] == current_node) {
            front[i] = front[front_pointer - 1];
            front[front_pointer - 1] = 0;
            front_pointer--;
            return;
        }
    }
}

void Front::clean_front() {
    while (front_pointer > 0) {
        front_pointer--;
        visited[front[front_pointer]] = false;
        front[front_pointer] = 0;
    }
}