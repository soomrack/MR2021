#include "avl_tree.h"
#include <iostream>

Tree::Tree() {
    root = new node;
    root -> left = 0;
    root -> right = 0;
    root -> key = 0;
    root -> height = 1;
};

unsigned short Tree::height(node* p) {
    return p?p -> height:0;
}

int16_t Tree::balance_factor(node* p) {
    return (int8_t)(height(p -> right) - height(p -> left));
}

void Tree::real_height(node* p) {
    unsigned short h_left = height(p->left);
    unsigned short h_right = height(p->right);
    p->height = (h_left > h_right?h_left:h_right) + 1;
}

node* Tree::rotate_right(node* p) {
    node* q = p -> left;
    p -> left = q -> right;
    q -> right = p;
    real_height(p);
    real_height(q);
    return q;
}

node* Tree::rotate_left(node* q) {
    node* p = q -> right;
    q -> right = p -> left;
    p -> left = q;
    real_height(q);
    real_height(p);
    return p;
}

node* Tree::balance(node* p) {
    real_height(p);
    if(balance_factor(p) == 2) {
        if(balance_factor(p -> right) < 0)
            p -> right = rotate_right(p -> right);
        return rotate_left(p);
    }
    if(balance_factor(p) == -2) {
        if(balance_factor(p -> left) > 0)
            p -> left = rotate_left(p -> left);
        return rotate_right(p);
    }
    return p; // do not need balance
}

node* Tree::pre_insert(node* p, int k, node* information) {
    if(!p) {
        node* A = new node;
        A -> height = 1;
        A -> key = k;
        A -> left = 0;
        A -> right = 0;
        A -> info = 0;
        return A;
    }

    if(k < p -> key) {
        p -> left = pre_insert(p -> left, k, information);
    } else if (k > p -> key) {
        p -> right = pre_insert(p -> right, k, information);
    } else {    // Equal keys are not allowed in binary search trees
        return p;
    }
    return balance(p); // balance after insertion
}

node* Tree::insert(node *p, int k, node *info) {
    return pre_insert(p, k, info);
}

node* Tree::pre_search(node* p, int k) {
    while(1) {
        if (k < p -> key) {
            p = p -> left;
        }
        if (k > p -> key) {
            p = p -> right;
        }
        if (k == p -> key) {
            std::cout << k <<std::endl;
            return p;
        }
        if ((p -> left == 0) && (p -> right == 0)) {
            std::cout << "can't find the key\n"<<"return zero pointer"<<std::endl;
            return p;
        }
    }
}

node* Tree::search(node *p, int k) {
    return pre_search(p, k);
}

node* Tree::find_min(node* p) {
    return p -> left?find_min(p -> left):p;
}

node* Tree::remove_min(node* p) {
    if(p -> left == 0) {
        return p->right;
    }
    p -> left = remove_min(p -> left);
    return balance(p);
}

node* Tree::pre_remove(node* p, int k) {
    if(!p) {
        return 0;
    }
    if( k < p->key ) {
        p->left = pre_remove(p->left, k);
    } else if( k > p->key ) {
        p->right = pre_remove(p->right, k);
    } else {  // k == p -> key
        node* q = p->left;
        node* r = p->right;
        delete p;
        if( !r ) {
            return q;
        }
        node* min = find_min(r);
        min->right = remove_min(r);
        min->left = q;
        return balance(min);
    }
    return balance(p); // balance after delete node
}

node* Tree::remove(node *p, int k) {
    return pre_remove(p, k);
}

void Tree::pre_order(node *root) {
    if(root != NULL) {
        std::cout << root->key << " ";
        pre_order(root->left);
        pre_order(root->right);
    }
}
