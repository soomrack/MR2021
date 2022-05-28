#include <iostream>
#include <string>
#include <time.h>
#include "rbtree.h"
using namespace std;

    void RedBlackTree::initializeNULLNode(NodePtr node, NodePtr parent) {
        node->data = 0;
        node->parent = parent;
        node->left = nullptr;
        node->right = nullptr;
        node->color = Black;
    }

    NodePtr RedBlackTree::searchTreeHelper(NodePtr node, int key) {
        if (node == TNULL || key == node->data) return node;

        if (key < node->data) return searchTreeHelper(node->left, key);

        return searchTreeHelper(node->right, key);
    }

    void RedBlackTree::deleteFix(NodePtr x) {
        NodePtr s;
        while (x != root && x->color == Black) {
            if (x == x->parent->left) {
                s = x->parent->right;
                if (s->color == Black) {
                    s->color = Black;
                    x->parent->color = Red;
                    leftRotate(x->parent);
                    s = x->parent->right;
                }

                if (s->left->color == Black && s->right->color == Black) {
                    s->color = Red;
                    x = x->parent;
                }
                else {  // случай 1
                    if (s->right->color == Black) {
                        s->left->color = Black;
                        s->color = Red;
                        rightRotate(s);
                        s = x->parent->right;
                    }

                    s->color = x->parent->color;
                    x->parent->color = Black;
                    s->right->color = Black;
                    leftRotate(x->parent);
                    x = root;
                }

            }
            else {
                s = x->parent->left;
                if (s->color == Red) {
                    s->color = Black;
                    x->parent->color = Red;
                    rightRotate(x->parent);
                    s = x->parent->left;
                }

                if (s->right->color == Black) {
                    s->color = Red;
                    x = x->parent;
                }
                else {
                    if (s->left->color == Black) {
                        s->right->color = Black;
                        s->color = Red;
                        leftRotate(s);
                        s = x->parent->left;
                    }

                    s->color = x->parent->color;
                    x->parent->color = Black;
                    s->left->color = Black;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = Black;
    }

    void RedBlackTree::rbTransplant(NodePtr u, NodePtr v) {
        if (u->parent == nullptr) {
            root = v;
        }
        else if (u == u->parent->left) {
            u->parent->left = v;
        }
        else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    void RedBlackTree::deleteNodeHelper(NodePtr node, int key) {
        NodePtr z = TNULL;
        NodePtr x, y;
        while (node != TNULL) { // поиск нужного узла
            if (node->data == key) {
                z = node;
            }

            if (node->data <= key) {
                node = node->right;
            }
            else {
                node = node->left;
            }
        }

        if (z == TNULL) { // не нашел нужный узел
            return;
        }

        y = z;
        int y_original_color = y->color;
        if (z->left == TNULL) {
            x = z->right;
            rbTransplant(z, z->right);
        }
        else if (z->right == TNULL) {
            x = z->left;
            rbTransplant(z, z->left);
        }
        else {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            }
            else {
                rbTransplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            rbTransplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;
        if (y_original_color == 0) {
            deleteFix(x);
        }
    }

    void RedBlackTree::insertFix(NodePtr k) {
        NodePtr u;
        while (k->parent->color == Red) {
            if (k->parent == k->parent->parent->right) {
                u = k->parent->parent->left;
                if (u->color == Red) { // case 1
                    u->color = Black;
                    k->parent->color = Black;
                    k->parent->parent->color = Red;
                    k = k->parent->parent;
                }
                else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = Black; // случай 2
                    k->parent->parent->color = Red;
                    leftRotate(k->parent->parent);
                }
            }
            else {
                u = k->parent->parent->right;

                if (u->color == Red) {
                    u->color = Black;
                    k->parent->color = Black;
                    k->parent->parent->color = Red;
                    k = k->parent->parent;
                }
                else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = Black;
                    k->parent->parent->color = Red;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root) {
                break;
            }
        }
        root->color = Black;
    }

    void RedBlackTree::printHelper(NodePtr root, string indent, bool last) {
        if (root != TNULL) {
            cout << indent;
            if (last) {
                cout << " R----";
                indent += "   ";
            }
            else {
                cout << " L----";
                indent += " |  ";
            }

            string sColor = root->color ? "R" : "B";
            cout << root->data << "(" << sColor << ")" << endl;
            printHelper(root->left, indent, false);
            printHelper(root->right, indent, true);
        }
    }

    RedBlackTree::RedBlackTree() {
        TNULL = new Node;
        TNULL->color = Black;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        root = TNULL;
    }

    void RedBlackTree::leftRotate(NodePtr x) {
        NodePtr y = x->right;
        x->right = y->left;
        if (y->left != TNULL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        }
        else if (x == x->parent->left) {
            x->parent->left = y;
        }
        else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void RedBlackTree::rightRotate(NodePtr x) {
        NodePtr y = x->left;
        x->left = y->right;
        if (y->right != TNULL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        }
        else if (x == x->parent->right) {
            x->parent->right = y;
        }
        else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    void RedBlackTree::insert(int key) {
        NodePtr node = new Node;
        node->parent = nullptr;
        node->data = key;
        node->left = TNULL;
        node->right = TNULL;
        node->color = Red;

        NodePtr y = nullptr;
        NodePtr x = this->root;

        while (x != TNULL) {
            y = x;
            if (node->data == x->data)
            {
                return;
            }
            else if (node->data < x->data) {
                x = x->left;
            }
            else {
                x = x->right;
            }
        }

        node->parent = y;

        if (y == nullptr) {
            root = node;
        }
        else if (node->data < y->data) {
            y->left = node;
        }
        else {
            y->right = node;
        }

        if (node->parent == nullptr) {
            node->color = Black;
            return;
        }

        if (node->parent->parent == nullptr) { return; }

        insertFix(node);
    }

    void RedBlackTree::printTree() {
        if (root) {
            printHelper(this->root, "", true);
        }
    }


    NodePtr RedBlackTree::minimum(NodePtr node) {
        while (node->left != TNULL) {
            node = node->left;
        }
        return node;
    }

int main() {
    uint64_t startTime, endTime;
    int degree = 2;
    //srand(time(NULL));
    int key;
    for(uint64_t j = 100; j <= 100000000; j*=10)
    {
        RedBlackTree tree;
        startTime = clock();
        for(int i = 0; i < 100000000; i++){
            key = rand();
            tree.insert(key);
        }

        endTime = clock();
        cout <<"10^"<< degree << ": "<< (double)(endTime - startTime)/CLK_TCK << "seconds.\n";
        degree ++;
        tree.deleteAll();
    }
    return 0;
}