#include "avl_tree.h"

int main() {
    Tree New_Tree;
    New_Tree.root = New_Tree.remove(New_Tree.root,0);
    node *info = 0;
    ///* Building tree by adding values *///
    New_Tree.root = New_Tree.insert(New_Tree.root, 10, info);
    New_Tree.root = New_Tree.insert(New_Tree.root, 20, info);
    New_Tree.root = New_Tree.insert(New_Tree.root, 30, info);
    New_Tree.root = New_Tree.insert(New_Tree.root, 40, info);
    New_Tree.root = New_Tree.insert(New_Tree.root, 50, info);
    New_Tree.root = New_Tree.insert(New_Tree.root, 25, info);
    New_Tree.root = New_Tree.insert(New_Tree.root, 60, info);
    New_Tree.root = New_Tree.insert(New_Tree.root, 70, info);
    New_Tree.root = New_Tree.insert(New_Tree.root, 45, info);
    New_Tree.root = New_Tree.insert(New_Tree.root, 75, info);
    New_Tree.root = New_Tree.insert(New_Tree.root, 55, info);
    New_Tree.root = New_Tree.insert(New_Tree.root, 90, info);
    New_Tree.root = New_Tree.insert(New_Tree.root, 15, info);
    New_Tree.root = New_Tree.insert(New_Tree.root, 80, info);
    New_Tree.root = New_Tree.insert(New_Tree.root, 5, info);
    New_Tree.root = New_Tree.insert(New_Tree.root, 65, info);
    New_Tree.root = New_Tree.insert(New_Tree.root, 56, info);

    New_Tree.root = New_Tree.insert(New_Tree.root, 54, info);
    New_Tree.root = New_Tree.remove(New_Tree.root,54);
    /* The AVL Tree structure will be look like:
                 _____55_____
                /            \
               40            70
             /    \        /    \
            20     50     60     80
          /    \   /     /  \     \
         10    30 45   56   65     90
        /  \   /              \
       5   15 25              75
       */
    std::cout << "The preliminary traversal of the "
                 "constructed AVL tree looks like: \n";
    New_Tree.pre_order(New_Tree.root);
    return 0;
}