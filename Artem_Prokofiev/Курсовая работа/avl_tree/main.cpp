#include "avl_tree.h"
#include<bits/stdc++.h>

int main() {
    Node New_Node;
    Node *root = NULL;

    /* Building tree by adding values */

    root = New_Node.insert(root, 10);
    root = New_Node.insert(root, 20);
    root = New_Node.insert(root, 30);
    root = New_Node.insert(root, 40);
    root = New_Node.insert(root, 50);
    root = New_Node.insert(root, 25);
    root = New_Node.insert(root, 60);
    root = New_Node.insert(root, 70);
    root = New_Node.insert(root, 70);
    root = New_Node.insert(root, 45);
    root = New_Node.insert(root, 75);
    root = New_Node.insert(root, 55);
    root = New_Node.insert(root, 90);
    root = New_Node.insert(root, 15);
    root = New_Node.insert(root, 80);
    root = New_Node.insert(root, 5);
    root = New_Node.insert(root, 65);
    /* The AVL Tree structure will be look like:
              _____50_____
             /            \
            30            70
          /    \        /    \
         20     40     60     80
       /   \      \   /  \   /  \
      10  25     45  55  65 75  90
     /  \
    5   15
    */
    std::cout << "The preliminary traversal of the "
                 "constructed AVL tree looks like: \n";
    New_Node.preOrder(root);

    return 0;
}
 