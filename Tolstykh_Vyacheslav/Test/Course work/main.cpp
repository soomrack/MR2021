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
        void insert(int a) {
            if (a > data && right) right->insert(a);
            else if (a > data && !right) right = new Node(a);
            else if (a < data && left) left->insert(a);
            else left = new Node(a);
        }
        void print() {
            if (left) left->print();
            cout << data << endl;
            if (right) right->print();
        }
        int find(int data) {
            if (this->data == data) {
                return data;
            }
            else if (this->data > data) {
                this->left->find(data);
            }
            else {
                this->right->find(data);
            }
        }
        void remove(int data) {
            if (this->data == data) {
                if (left) {
                    left->remove(data);
                }
                if (right) {
                    right->remove(data);
                }
                delete[] this;
            }
            else if (this->data > data) {
                this->left->find(data);
            }
            else {
                this->right->find(data);
            }
        }
    };

class Tree {
private:
    Node* root;
public:
    Tree() :root(nullptr) {}
    void insert(int);
    void print();
    int find(int);
    void remove(int);
};

void Tree::insert(int data) {
    if (!root) root = new Node(data);
    else root->insert(data);
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