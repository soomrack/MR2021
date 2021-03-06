#include <iostream>
#include <vector>
using namespace std;

class Node {
    private:
        int data;
        Node* left;
        Node* right;
    public:
        Node(int data) :data(data), left(nullptr), right(nullptr) {}
        void insert(int);
        void print();
        int find(int);
        void remove(int);
        void destroy();
    };

void Node::insert(int a) {
    if (a > data && right) 
        right->insert(a);

    else if (a > data && !right) 
        right = new Node(a);

    else if (a < data && left) 
        left->insert(a);

    else 
        left = new Node(a);
}

Tree::Tree(const Tree& other_tree) { //конструктор копирования
    tree_size = other_tree.tree_size;
    for (int i = 0; i < tree_size - 1; ++i) {
        Tree* next = other_tree[i];
    }
}

Tree::Tree(Tree&& other_tree) { //конструктор перемещения
    tree_size = other_tree.tree_size;
    other_tree.other_tree = 0;
    for (int i = 0; i < other_tree - 1; ++i) {
        Node* root = other_tree[i];
        other_tree[i] = nullptr;
    }
}

void Node::print() {
    if (left) 
        left->print();

    cout << data << endl;

    if (right) 
        right->print();
}

int Node::find(int data) {
    if (this->data == data) 
        return data;

    else if (this->data > data) 
        this->left->find(data);

    else 
        this->right->find(data);
}
void Node::destroy(){
   if (left) 
        left->destroy();
    if (right) 
        right->destroy();
    delete[] this;
    
}
void Node::remove(int data) {
    if (this->data == data) {
        if (this->left) 
            this->left->destroy();
        if (this->right) 
            this->right->destroy();
        
        delete[] this;
    }
    else if (this->data > data) {
        this->left->remove(data);
    }
    else 
        this->right->remove(data);
}

class Tree {
private:
    Node* root;
public:
    Tree() :root(nullptr) {}
    void insert(int);
    void print();
    int find(int);
    void remove(int);
    Tree(const Tree& other_tree);
    Tree::Tree(Tree&& other_tree);
};

void Tree::insert(int data) {
    if (!root) 
        root = new Node(data);
    else 
        root->insert(data);
}

void Tree::print() {
    root->print();
}

int Tree::find(int data) {
    return root->find(data);
}

void Tree::remove(int data) {
    root->remove(data);
}

void test_insert_time(int nodes_count) {

    vector<int> values(nodes_count);
    for (int i = 0; i < values.size(); ++i) {
        values[i] = rand() % nodes_count;
    }

    Tree* tree = new Tree();
    int start = clock();

    for (int i = 0; i < values.size(); i++) {
        tree->insert(values[i]);
    }

    int end = clock();
    cout << "nodes_count: " << nodes_count << ", milliseconds: ";
    cout << (end - start) * 1000 / CLOCKS_PER_SEC << endl;
}

int main() {

    //тест insert
    cout << "Inserts tests...\n";
    test_insert_time(1000000);
    test_insert_time(2000000);
    test_insert_time(3000000);
    test_insert_time(4000000);
    test_insert_time(5000000);
    test_insert_time(6000000);
    test_insert_time(7000000);
    test_insert_time(8000000);

    return 0;
}