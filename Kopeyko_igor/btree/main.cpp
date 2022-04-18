#include <iostream>
#include "b_tree.h"










int main() {
/*
    BTree Aboba;

    BTree::Node t1(4);
    BTree::Node t2(4);
    BTree::Node t3(4);
    BTree::Node t4(4);

    Aboba.root->pointers[0] = &t1;
    Aboba.root->pointers[1] = &t2;
    Aboba.root->pointers[2] = &t3;
    Aboba.root->pointers[3] = &t4;

    int t4_key[] = { 1,2,3};
    BTree::Node * t4_pointer[] = {nullptr, nullptr, nullptr, nullptr};
    t4.set(t4_key, t4_pointer);

    Aboba.print();

    */
    BTree Derevo;
    Derevo.add(2);
    Derevo.add(1);
    Derevo.add(3);
    Derevo.add(4);
    Derevo.add(5);
    Derevo.add(6);
    Derevo.add(7);
    Derevo.add(8);
    Derevo.add(9);
    Derevo.add(10);
    Derevo.add(11);
    Derevo.add(12);
    //Derevo.add(13);


    Derevo.print();

    return 0;
}

