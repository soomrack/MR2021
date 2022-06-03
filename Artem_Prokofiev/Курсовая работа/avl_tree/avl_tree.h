#include <iostream>
#ifndef AVL_TREE_H
#define AVL_TREE_H

struct node {             // struct for presentation node of the tree
    int key;              // current key
    unsigned short height;// height of subtree with root in current node
    node* left;           // pointer on left subtree
    node* right;          // pointer on right subtree
    node* info;           // pointer to include some information to node
};

class Tree {
public:
    node *root;
    node* insert(node* p, int k, node* info);    /* Insertion of key k in tree with root p and
                                                 re-balance of tree*/
    node* search(node* p, int k);                // Search of node with needed key
    node* remove(node* p, int k);                // Delete key k from tree p
    void pre_order(node *root);                  // Print preliminary traversal of the tree
    Tree();                                      // Start tree parameters
    void clear(node* current);
    ~Tree();

private:
    node* rotate_right(node* p);                 // Left rotate subtree rooted with p
    node* rotate_left(node* q);                  // Right rotate subtree rooted with q
    node* balance(node* p);                      // Balance tree in rules of AVL_Tree
    node* pre_insert(node* p, int k, node* info);// Preparation for insert function
    node* pre_search(node* p, int k);            // Preparation for search function
    node* find_min(node* p);                     // Search of node with min key from tree p
    node* remove_min(node* p);                   // Delete node with min key from tree p
    node* pre_remove(node* p, int k);            // Preparation for remove function
    unsigned short height(node* p);              // Helper functions
    int16_t balance_factor(node* p);
    void real_height(node* p);
};
#endif //AVL_TREE_H
