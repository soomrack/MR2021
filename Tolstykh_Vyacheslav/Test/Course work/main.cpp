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
   if (this->left) 
            this->left->destroy();
    if (this->right) 
            this->right->destroy();
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

int main() {

    return 0;
}