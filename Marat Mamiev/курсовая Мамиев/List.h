#ifndef LIST
#define LIST
template <typename T>
class List {
public:
	List();
	~List();
	List(const List& other_list);
	List(List&& other_list);
public:
	bool empty() const;
	void clear();
	void print();
	void pop_front();
	void pop_back();
	void removeAt(const int index);
	void push_front(const T& data);
	void push_back(const T& data);
	void insert(const T& data, int index);
	int size() { return list_size; }
	T& operator [](const int index);
private:
	class Node {
	public:
		T data;
		Node* next;
		Node(T data, Node* next) {
			this->data = data;
			this->next = next;
		}
	};
	Node* head;
	int list_size;
}; 
#endif
