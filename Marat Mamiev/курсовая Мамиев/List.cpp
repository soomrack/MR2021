#include <iostream>
#include "List.h"

#define EXPLICIT_INSTANTIATION(CLASSNAME)   \
    template class CLASSNAME<int8_t>;       \
    template class CLASSNAME<int16_t>;      \
    template class CLASSNAME<int32_t>;      \
    template class CLASSNAME<int64_t>;      \
                                            \
    template class CLASSNAME<float>;        \
    template class CLASSNAME<double>;       \

EXPLICIT_INSTANTIATION(List);

template <typename T>
List<T>::List()
{
	list_size = 0;
	head = nullptr;
}

template <typename T>
List<T>::List(const List& other_list) { //конструктор копирования
	list_size = other_matrix.list_size;
	for (int i = 0; i < list_size - 1; ++i) {
		Node* next = other_list[i];
	}
}

template <typename T>
List<T>::List(List&& other_list) { //конструктор перемещения
	list_size = other_matrix.list_size;
	other_matrix.list_size = 0;
	for (int i = 0; i < list_size - 1; ++i) {
		Node* next = other_list[i];
		other_list[i] = nullptr;
	}
}

template <typename T>
bool List<T>::empty() const {
	return head == nullptr;
}

template <typename T>
void List<T>::clear() {
	while (size()) {
		pop_front();
	}
}

template <typename T>
void List<T>::print() {
	Node* temp_head = head;
	while (temp_head != nullptr) {
		std::cout << temp_head->data << " ";
		temp_head = temp_head->next;
	}
}

template <typename T>
void List<T>::removeAt(const int index) {
	if (index >= size()) {
		std::cout << "going overboard the list";
	}
	if (index == 0) {
		pop_front();
	}
	else {
		Node* previous = head;
		for (int i = 0; i < index - 1; ++i) {
			previous = previous->next;
		}
		Node* del_node = previous->next;
		previous->next = del_node->next;
		delete del_node;
		list_size--;
	}
}

template <typename T>
void List<T>::insert(const T& data, int index) {
	if (index >= size()) {
		std::cout << "going overboard the list";
	}
	if (index == 0) {
		push_front(data);
	}
	else {
		Node* previous = head;
		for (int i = 0; i < index - 1; ++i) {
			previous = previous->next;
		}
		previous->next = new Node(data, previous->next);
		list_size++;
	}
}

template <typename T>
void List<T>::push_front(const T& data) {
	Node* new_head = new Node(data, head);
	head = new_head;
	list_size++;
}

template <typename T>
void List<T>::push_back(const T& data) {
	if (empty()) {
		head = new Node(data, nullptr);
		list_size++;
	}
	else {
		Node* temp_head = head;
		while (temp_head->next != nullptr) {
			temp_head = temp_head->next;
		}
		temp_head->next = new Node(data, nullptr);
		list_size++;
	}
}

template <typename T>
void List<T>::pop_back() {
	removeAt(size() - 1);
}

template <typename T>
void List<T>::pop_front() {
	Node* del_node = head;
	head = head->next;
	delete del_node;
	list_size--;
}

template<typename T>
T& List<T>::operator[](const int index) {
	if (index >= size()) {
		std::cout << "going overboard the list";
	}
	int count = 0;
	Node* temp_head = head;
	while (temp_head != nullptr) {
		if (count == index) {
			return temp_head->data;
		}
		count++;
		temp_head = temp_head->next;
	}
}

template <typename T>
List<T>::~List() {
	clear();
}