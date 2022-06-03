#pragma once

using namespace std;

enum Color{
    Black,
    Red
};

struct Node {
    int data;
    Node* parent;
    Node* left;
    Node* right;
    Color color;
};

typedef Node* NodePtr;

class RedBlackTree {
private:
    NodePtr root;
    NodePtr TNULL;

    void initializeNULLNode(NodePtr node, NodePtr parent);

    NodePtr searchTreeHelper(NodePtr node, int key);

    void deleteFix(NodePtr x);

    void rbTransplant(NodePtr u, NodePtr v);

    void deleteNodeHelper(NodePtr node, int key);

    void insertFix(NodePtr k);

    void printHelper(NodePtr root, string indent, bool last) ;

    void leftRotate(NodePtr x);

    void rightRotate(NodePtr x);

    void deleteAllNodeHelper(NodePtr current);

public:
    RedBlackTree();

    NodePtr getTNULL() { return TNULL; }

    NodePtr minimum(NodePtr node);

    void deleteAll(){
        deleteAllNodeHelper(root);
        //root = TNULL;
    };

    NodePtr searchTree(int k) { return searchTreeHelper(this->root, k); }

    void insert(int key);

    NodePtr getRoot() { return this->root; }

    void deleteNode(int data) { deleteNodeHelper(this->root, data); }

    void printTree();
};
