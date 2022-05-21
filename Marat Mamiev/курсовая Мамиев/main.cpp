#include <iostream>
#include "List.h"
#include <vector>
#include <ctime>

//义耱 push_front
void test_push_front(int nodes_count) {
	List<int> my_list;
	for (int i = 0; i < nodes_count; i++) {
		my_list.push_front(rand() % nodes_count);
	}
	int start = clock();
	my_list.push_front(1);
	int end = clock();
	std::cout << "nodes_count: " << nodes_count << ", milliseconds: ";
	std::cout << (end - start) * 1000 / CLOCKS_PER_SEC << std::endl;
}

//义耱 push_back
void test_push_back(int nodes_count) {
	List<int> my_list;
	for (int i = 0; i < nodes_count; i++) {
		my_list.push_front(rand() % nodes_count);
	}
	int start = clock();
	my_list.push_back(1);
	int end = clock();
	std::cout << "nodes_count: " << nodes_count << ", milliseconds: ";
	std::cout << (end - start) * 1000 / CLOCKS_PER_SEC << std::endl;
}

//义耱 pop_front
void test_pop_front(int nodes_count) {
	List<int> my_list;
	for (int i = 0; i < nodes_count; i++) {
		my_list.push_front(rand() % nodes_count);
	}
	int start = clock();
	my_list.pop_front();
	int end = clock();
	std::cout << "nodes_count: " << nodes_count << ", milliseconds: ";
	std::cout << (end - start) * 1000 / CLOCKS_PER_SEC << std::endl;
}

//义耱 pop_back
void test_pop_back(int nodes_count) {
	List<int> my_list;
	for (int i = 0; i < nodes_count; i++) {
		my_list.push_front(rand() % nodes_count);
	}
	int start = clock();
	my_list.pop_back();
	int end = clock();
	std::cout << "nodes_count: " << nodes_count << ", milliseconds: ";
	std::cout << (end - start) * 1000 / CLOCKS_PER_SEC << std::endl;
}

int main() {

	//义耱 push_front
	std::cout << "Test push_front:" << std::endl;
	test_push_front(1000000);
	test_push_front(2000000);
	test_push_front(3000000);
	test_push_front(4000000);
	test_push_front(5000000);
	test_push_front(6000000);
	test_push_front(7000000);
	test_push_front(8000000);
	test_push_front(9000000);
	test_push_front(10000000);

	//义耱 push_back
	std::cout << "Test push_back:" << std::endl;
	test_push_back(1000000);
	test_push_back(2000000);
	test_push_back(3000000);
	test_push_back(4000000);
	test_push_back(5000000);
	test_push_back(6000000);
	test_push_back(7000000);
	test_push_back(8000000);
	test_push_back(9000000);
	test_push_back(10000000);

	//义耱 pop_front
	std::cout << "Test pop_front:" << std::endl;
	test_pop_front(1000000);
	test_pop_front(2000000);
	test_pop_front(3000000);
	test_pop_front(4000000);
	test_pop_front(5000000);
	test_pop_front(6000000);
	test_pop_front(7000000);
	test_pop_front(8000000);
	test_pop_front(9000000);
	test_pop_front(10000000);

	//义耱 pop_back
	std::cout << "Test pop_back:" << std::endl;
	test_pop_back(1000000);
	test_pop_back(2000000);
	test_pop_back(3000000);
	test_pop_back(4000000);
	test_pop_back(5000000);
	test_pop_back(6000000);
	test_pop_back(7000000);
	test_pop_back(8000000);
	test_pop_back(9000000);
	test_pop_back(10000000);

	return 0;
}