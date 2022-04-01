#pragma once

template <typename T>
class List
{
public:
	List();
	~List();
public:
	void clear();
	void print();
	void pop_front();
	void pop_back();
	void removeAt(int index);
	void push_front(T data);
	void push_back(T data);
	void insert(T data, int index);
	int size() { return Size; }
	T& operator[](const int index);
private:
	template <typename T>
	class Node
	{
	public:
		Node* pNext;
		T data;
		Node(T data = T(), Node* pNext = nullptr)
		{
			this->data = data;
			this->pNext = pNext;
		}
	};

	int Size;
	Node<T>* head;
};
