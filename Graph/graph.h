#ifndef TARJAN_S_BRIDGE_FINDING_ALGORITHM_GRAPH_H
#define TARJAN_S_BRIDGE_FINDING_ALGORITHM_GRAPH_H

#include <vector>
#include <list>

typedef enum{
    UNDIRECTED,
    DIRECTED,
} EdgeType;

typedef enum{
    ADJACENCY_MATRIX,
    ADJACENCY_LIST,
} DataType;

template<typename T>
T get_inf();            // Получить "бесконечность" для типа T
// (целочисленный тип - максимальное значение, с плавающей запятой - inf)

template <typename T>
T INF = get_inf<T>();   // переменная, содержащая "бесконечность", т.е. такой вес ребра,
// который эквивалентен отсутствию этого ребра


// Класс графа с базовой функциональностью
template <typename T>
class BaseGraph{
protected:
    std::vector<std::vector<T>> adjacency_matrix;   // Матрица смежности
    std::vector<std::list<T>> adjacency_list;       // Список смежности
public:
    explicit BaseGraph(int num_of_vertices = 0);
    explicit BaseGraph(std::vector<std::vector<T>> &adjacency_matrix);
    explicit BaseGraph(std::vector<std::list<T>> &adjacency_list);
    BaseGraph(const BaseGraph &other);
    BaseGraph(BaseGraph &&other) noexcept;
    virtual ~BaseGraph() = default;

// Методы для взаимодействия с графом (т.е. геттеры, сеттеры и т.д.)
public:
    void add_edge(int v, int w, int weight = 0, EdgeType edge_type = UNDIRECTED);
    void synchronize_data(/*DataType source_data, DataType target_data*/);  // Ранняя версия метода (будет еще дорабатываться)
};



// Далее идут классы, в которых реализуются алгоритмы
// Все эти классы наследуются от базового графа как virtual public

template<typename T>
class GraphTarjansBridges: virtual public BaseGraph<T> {
protected:
    int tarjan_s_time = 0;
public:
    explicit GraphTarjansBridges(int num_of_vertices = 0) : BaseGraph<T>(num_of_vertices) {};
    explicit GraphTarjansBridges(std::vector<std::vector<T>> &adjacency_matrix) : BaseGraph<T>(adjacency_matrix) {};
    explicit GraphTarjansBridges(std::vector<std::list<T>> &adjacency_list) : BaseGraph<T>(adjacency_list) {};
    GraphTarjansBridges(const GraphTarjansBridges &other) : BaseGraph<T>(other) {};
    GraphTarjansBridges(GraphTarjansBridges &&other) noexcept : BaseGraph<T>(other) {};
    virtual ~GraphTarjansBridges() = default;
public:
    std::vector<std::pair<int, int>> tarjans_find_bridges();
private:
    void tarjan_s_bridge_finding_dfs(int u,
                                     std::vector<bool> &visited,
                                     std::vector<int> &disc,
                                     std::vector<int> &low,
                                     std::vector<int> &parent,
                                     std::vector<std::pair<int, int>> &bridges);
};


template<typename T>
class GraphFloydWarshall: virtual public BaseGraph<T> {
private:
    std::vector<std::vector<int>> restore_matrix;   // Матрица для восстановления кратчайшего пути
    std::vector<int> restored_path;                 // Вектор, в котором хранится путь восстановленный методом restore_path
public:
    std::vector<std::vector<T>> floyd_warshall();   // Базовая реализация алгоритма
public:
    // Дополнительный функционал на основе алгоритма
    std::tuple<std::vector<std::vector<T>>, std::vector<std::vector<int>>> floyd_warshall_ways(); // Дополнительно возвращает
                                                                                                  // матрицу для восстановления
                                                                                                  // пути между узлами
    std::vector<int> restore_path(int from, int to); // Восстанавливает путь между указанными узлами
private:
    T min(int, int, int);
};


template<typename T>
class GraphDijkstra: virtual public BaseGraph<T>{
public:
    std::vector<std::vector<T>> dijkstra();
private:
    std::vector<T> dijkstra_from_one_vertex(int origin);
};


template<typename T>
class GraphTraversal: virtual public BaseGraph<T> {
private:
    std::vector<T> restored_path;                   // Вектор для хранения пути между двумя вершинами
    std::vector<T> topological_sorted_graph;        // Топологически отсортированный граф
public:
    void print_vector(std::vector<T> vector_to_print);
    void bfs_search();
    void dfs_search();
    std::vector<T> find_path(T from, T to);
    std::vector<T> topological_sort();
};


// Итоговый класс графа, наследующийся как virtual public от всех классов, реализующих алгоритмы,
// т.е. создающийся с помощью ромбовидного наследования

template<typename T>
class Graph:
        virtual public GraphFloydWarshall<T>,
        virtual public GraphTarjansBridges<T>,
        virtual public GraphDijkstra<T>,
        virtual public GraphTraversal<T> {
public:
    explicit Graph(int num_of_vertices = 0) : BaseGraph<T>(num_of_vertices) {};
    explicit Graph(std::vector<std::vector<T>> &adjacency_matrix) : BaseGraph<T>(adjacency_matrix) {};
    explicit Graph(std::vector<std::list<T>> &adjacency_list) : BaseGraph<T>(adjacency_list) {};
    Graph(const Graph &other) : BaseGraph<T>(other) {};
    Graph(Graph &&other) noexcept : BaseGraph<T>(other) {};
    virtual ~Graph() = default;
};

#endif
