#include "avl_tree.h"
#include<bits/stdc++.h>

int Node:: get_height(Node *N) {
    if (N == NULL) {
        return 0;
    }
    return N->height;
}

int Node::max(int a, int b) {
    return (a > b)? a : b;
}

Node* Node::newNode(int key) {
    Node* node = new Node();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // The new node is initially added at the end (at leaf)
    return(node);
}

Node *Node::rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    // Rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(get_height(y->left),
                    get_height(y->right)) + 1;
    x->height = max(get_height(x->left),
                    get_height(x->right)) + 1;

    // Return new root
    return x;
}

Node *Node::leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    // Rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(get_height(x->left),
                    get_height(x->right)) + 1;
    y->height = max(get_height(y->left),
                    get_height(y->right)) + 1;

    // Return new root
    return y;
}

int Node::getBalance(Node *N) {
    if (N == NULL)
        return 0;
    return get_height(N->left) - get_height(N->right);
}

Node* Node::insert(Node* node, int key) {
    /* 1. Insertion */
    if (node == NULL) {
        return (newNode(key));
    }
    if (key < node->key) {
        node->left = insert(node->left, key);
    } else if (key > node->key) {
        node->right = insert(node->right, key);
    } else {    // Equal keys are not allowed in binary search trees
        return node;
    }
    /* 2. Update height of this previous node */
    node->height = 1 + max(get_height(node->left),
                           get_height(node->right));

    /* 3. Get the balance factor of this previous
        node to check whether this node became unbalanced */
    int balance = getBalance(node);

    /* If this node becomes unbalanced, then there are 4 cases:
       1. Left Left Case*/
    if (balance > 1 && key < node->left->key) {
        return rightRotate(node);
    }
    // 2. Right Right Case
    if (balance < -1 && key > node->right->key) {
        return leftRotate(node);
    }
    // 3. Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    // 4. Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* If node is balanced return the (unchanged) node pointer */
    return node;
}

void Node::preOrder(Node *root) {
    if(root != NULL) {
        std::cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}