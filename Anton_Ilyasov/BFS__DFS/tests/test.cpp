#include "pch.h"
#include "graph.h"

TEST(test_create_random_graph) { //тесты создания случайного графа
	//отрицательная сумма вершин и ребер
	Graph a0(-1000, RANDOM);
	ASSERT_EQ(a0.get_number_of_edges(), 0);
	ASSERT_EQ(a0.get_number_of_vertices(), 0);
	//нулевая сумма вершин и ребер
	Graph a1(0, RANDOM);
	ASSERT_EQ(a1.get_number_of_edges(), 0);
	ASSERT_EQ(a1.get_number_of_vertices(), 0);
	//положительная сумма вершин и ребер
	Graph a2(1, RANDOM);	//sum = 1
	ASSERT_EQ(a2.get_number_of_edges(), 0);
	ASSERT_EQ(a2.get_number_of_vertices(), 1);
	
	Graph a3(2, RANDOM);	//sum = 2
	ASSERT_EQ(a3.get_number_of_edges(), 0);
	ASSERT_EQ(a3.get_number_of_vertices(), 2);
}

TEST(test_create_graph_from_other_graph) {	//тесты создания графа на основе списка смежности
	//test 1
	std::vector<std::vector<int>> a_list_1 = { {1,2},
											   {0,3},
											   {0,1},
											   {2} };
	Graph a0(a_list_1);
	ASSERT_EQ(a0.get_adjacency_list(), a_list_1);
	ASSERT_EQ(a0.get_number_of_vertices(), 4);
	//test 2
	std::vector<std::vector<int>> a_list_2;
	Graph a1(a_list_2);
	ASSERT_EQ(a1.get_adjacency_list(), a_list_2);
}

TEST(test_constructor_copy) {	//тесты конструктора копирования
	//test 1
	Graph a0(1000, RANDOM);
	Graph a1(a0);
	ASSERT_EQ(a1.get_adjacency_list(), a0.get_adjacency_list());
	//test 2
	Graph a2 = a1;
	ASSERT_EQ(a2.get_adjacency_list(), a0.get_adjacency_list());
}

TEST(test_overload_operation_equal) {	//тесты оператора присваивания
	//test 1
	Graph a0(100, RANDOM);
	Graph a1(5, RANDOM);
	a1 = a0;
	ASSERT_EQ(a1.get_adjacency_list(), a0.get_adjacency_list());
	//test 2
	std::vector<std::vector<int>> a_list_1 = { {1,2},
										   {0,3},
										   {0,1},
										   {2} };
	Graph a2(a_list_1);
	Graph a3 = a2;
	a0 = a2;
	a3 = a0;
	ASSERT_EQ(a3.get_adjacency_list(), a2.get_adjacency_list());
}

TEST(test_get_adjacency_matrix) {	//тесты получения матрицы смежности
	//test 1
	std::vector<std::vector<int>> a_list_1 = { {1,2},
											   {0,3},
											   {0,1},
											   {2} };
	Graph a0(a_list_1);
	std::vector<std::vector<int>> a_list_1_adj_matrix = { {0,1,1,0},
														  {1,0,0,1},
														  {1,1,0,0},
														  {0,0,1,0} };
	ASSERT_EQ(a0.get_adjacency_matrix(), a_list_1_adj_matrix);
	//test 2
	Graph a1(1000, RANDOM);
	Graph a2(a1.get_adjacency_list());
	ASSERT_EQ(a1.get_adjacency_matrix(), a2.get_adjacency_matrix());
	ASSERT_EQ(a1.get_adjacency_list(), a2.get_adjacency_list());
}

TEST(test_bfs_search) {	//тесты поиска в ширину
	//test 1
	Graph a0(100, RANDOM);
	std::vector<int> expected_bfs_search = { 0, 1, 2, 3, 6, 7, 12, 13, 4, 9, 11, 5, 10, 8 };
	ASSERT_EQ(a0.bfs_search(), expected_bfs_search);
	//test 2
	Graph a1(500, RANDOM);
	std::vector<int> expected_bfs_search_1 = { 0, 1, 3, 5, 7, 8, 10, 11, 13, 19, 22, 23, 25, 26, 27,
										   28, 29, 2, 6, 9, 12, 15, 16, 24, 30, 4, 14, 18, 20, 21, 17 };
	ASSERT_EQ(a1.bfs_search(), expected_bfs_search_1);
	//test 3
	Graph a2(1000, RANDOM);
	std::vector<int> expected_bfs_search_2 = { 0, 3, 5, 6, 7, 10, 12, 16, 17, 18, 19, 21, 24, 28, 29, 30, 31, 34, 35, 38, 40, 41,
										   42, 1, 2, 9, 13, 20, 22, 25, 26, 27, 37, 39, 4, 8, 11, 32, 36, 43, 15, 14, 23, 33 };
	ASSERT_EQ(a2.bfs_search(), expected_bfs_search_2);
}	

TEST(test_dfs_search) {	//тесты поиска в глубину
	//test 1
	Graph a0(100, RANDOM);
	std::vector<int> expected_dfs_search = { 0, 1, 2, 4, 3, 5, 6, 9, 11, 7, 10, 8, 12, 13 };
	ASSERT_EQ(a0.dfs_search(), expected_dfs_search);
	//test 2
	Graph a1(500, RANDOM);
	std::vector<int> expected_dfs_search_1 = { 0, 1, 2, 3, 4, 5, 8, 6, 7, 11, 9, 12, 13, 10, 16, 14, 17,
										   18, 15, 20, 19, 21, 22, 23, 25, 24, 26, 27, 28, 29, 30 };
	ASSERT_EQ(a1.dfs_search(), expected_dfs_search_1);
	//test 3
	Graph a2(1000, RANDOM);
	std::vector<int> expected_dfs_search_2 = { 0, 3, 1, 4, 6, 5, 2, 7, 8, 10, 13, 11, 12, 15, 9, 17, 20, 16, 14, 19, 22, 23, 18, 25,
										   21, 24, 28, 29, 26, 27, 31, 32, 34, 30, 36, 33, 38, 42, 37, 39, 40, 35, 41, 43 };
	ASSERT_EQ(a2.dfs_search(), expected_dfs_search_2);
}

TEST(test_find_path) {	//тесты поиска кратчайшего пути
	//test 1
	std::vector<std::vector<int>> a_list_0 = { {2},
											   {0,4,6},
											   {5,7},
											   {1,6},
											   {2},
											   {},
											   {4,8},
											   {5},
											   {4,7} };
	Graph a0(a_list_0);
	std::vector<int> expected_path = { 3, 1, 0, 2, 5 };
	ASSERT_EQ(a0.find_path(3,5), expected_path);
	//test 2
	Graph a1(100, RANDOM);
	std::vector<int> expected_path_1 = { 12, 7, 0, 13 };
	ASSERT_EQ(a1.find_path(12,13), expected_path_1);
	//test 3
	Graph a2(500, RANDOM);
	std::vector<int> expected_path_2 = { 29, 7, 30 };
	ASSERT_EQ(a2.find_path(29, 30), expected_path_2);
}

TEST(test_topological_sort) {	//тесты топологической сортировки графа
	//test 1
	std::vector<std::vector<int>> a_list_0 = { {2},
											   {0,4,6},
											   {5,7},
											   {1,6},
											   {2},
											   {},
											   {4,8},
											   {5},
											   {4,7} };
	Graph a0(a_list_0);
	std::vector<int> expected_topological_sort_0 = { 3, 1, 6, 8, 4, 0, 2, 7, 5 };
	ASSERT_EQ(a0.topological_sort(), expected_topological_sort_0);
	//test 2
	std::vector<std::vector<int>> a_list_1 = { {1,2,3},
											   {6},
											   {9,14},
											   {14,17},
											   {11,16,19},
											   {0,3},
											   {14},
											   {2,8},
											   {},
											   {},
											   {7},
											   {12,16,19},
											   {9},
											   {2,11},
											   {4},
											   {19},
											   {},
											   {18},
											   {4,14,15},
											   {12} };
	Graph a1(a_list_1);
	std::vector<int> expected_topological_sort_1 = { 13, 10, 7, 8, 5, 0, 3, 17, 18, 15, 2, 1, 6, 14, 4, 11, 19, 16, 12, 9 };
	ASSERT_EQ(a1.topological_sort(), expected_topological_sort_1);
}