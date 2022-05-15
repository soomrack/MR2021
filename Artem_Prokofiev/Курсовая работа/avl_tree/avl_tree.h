#ifndef AVL_TREE_H
#define AVL_TREE_H

// An AVL tree node
class Node {
public:
    int key;
    int height;
    Node * left;
    Node * right;

public:
    int get_height(Node *N);           // Get the height of the tree
    int max(int a, int b);             // Get maximum of two numbers
    int getBalance(Node *N);           // Get balance factor of node N
    void preOrder(Node *root);         /* Print preliminary traversal of the tree.
                                       The function also prints height of every node.*/
    Node* newNode(int key);            /* Allocates a new node with the given
                                       key and NULL left and right pointers.*/
    Node *rightRotate(Node *y);        // Right rotate subtree rooted with y.
    Node *leftRotate(Node *x);         // A utility function to left rotate subtree rooted with x.
    Node* insert(Node* node, int key); /* Recursive function to insert a key in the subtree rooted
                                       with node and returns the new root of the subtree.*/
};

#endif //AVL_TREE_H

