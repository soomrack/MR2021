#include <iostream>
#ifndef AVL_TREE_H
#define AVL_TREE_H

struct node {             // struct for presentation node of the tree
    int key;              // current key
    unsigned short height;// height of subtree with root in current node
    node* left;           // pointer on left tree
    node* right;          // pointer on right tree
    node* info;           // pointer to include some information to node
};

class Tree {
public:
    node *root;
    node* remove(node* p, int k);            // Delete key k from tree p
    node* search(node* p, int k);            // Search of node with needed key
    node* insert(node* p, int k, node* info);// Insertion of key k in tree with root p and re-balance of tree
    void preOrder(node *root);               /* Print preliminary traversal of the tree.
                                             The function also prints height of every node.*/

    Tree() {                                 // Start tree parameters
        root = new node;
        root -> left = 0;
        root -> right = 0;
        root -> key = 0;
        root -> height = 1;
    };

private:
    node* balance(node* p);                  // Balance tree in rules of AVL_Tree
    node* rotate_right(node* p);             // Left rotate subtree rooted with p
    node* rotate_left(node* q);              // Right rotate subtree rooted with q
    node* find_min(node* p);                 // Search of node with min key from tree p
    node* remove_min(node* p);               // Delete node with min key from tree p
    unsigned short height(node* p);          // Helper functions
    int16_t balance_factor(node* p);
    void real_height(node* p);
};
#endif //AVL_TREE_H

