#include <iostream>
#include "b_tree.h"
int massiv[35];


void massiv_make(){
    //int * copy = mass;
    for (int i = 0; i <30; i++){
        massiv[i] = 0;
    }

    int a = 0;
    int fatal = 0;
    for (int i = 0; i < 30; i++) {
        fatal = 0;
        a = rand() % 100;
        for (int k = 0; k < 30; k++) {
            if (massiv[k] == a){
                fatal++;
            }
        }
        if (fatal == 0){
            massiv[i] = a;
        } else {
            massiv[i] = rand() % 100;
        }
    }

}









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
    /*
    BTree Derevo;

    for (int i = 100; i >= 79; i = i -1){
        std::cout << "Начали добавлять  " << i << std::endl;
        Derevo.add(i);
        std::cout << "Добавили  " << i << std::endl;
        Derevo.print();
    }
    */

/*
    Derevo.add(2);
    Derevo.add(1);

    Derevo.print();
    Derevo.add(3);

    Derevo.print();
    Derevo.add(4);

    Derevo.print();
    Derevo.add(5);

    Derevo.print();
    Derevo.add(6);

    Derevo.print();
    Derevo.add(7);

    Derevo.print();
    Derevo.add(8);
    Derevo.print();

    //std::cout << "Начали 9! ===================================" << std::endl;
    Derevo.add(9);
    Derevo.add(10);
    Derevo.add(11);
    Derevo.add(12);
    Derevo.print();
    std::cout << "Начали 13! ===================================" << std::endl;
    Derevo.add(13);

    std::cout << "Закончили 13   =====================================" << std::endl;
    Derevo.add(14);
    Derevo.add(15);
    Derevo.add(16);
    Derevo.add(17);
    Derevo.add(18);
    Derevo.add(19);
    Derevo.add(20);
    Derevo.print();
    std::cout << "Начали 21! ===================================))))))))))))))))))))" << std::endl;
    Derevo.add(21);
    std::cout << "Закончили 21   =====================================)))))))))))))))))))" << std::endl;
    Derevo.add(22);
    Derevo.add(23);
    Derevo.add(24);
    Derevo.print();
    std::cout << "Начали 25! ===================================))))))))))))))))))))" << std::endl;
    Derevo.add(25);
    Derevo.add(26);
    Derevo.add(27);
    Derevo.add(28);
    Derevo.add(29);
    Derevo.add(30);
    Derevo.add(31);
    Derevo.add(32);
    */
    BTree Derevo;
    //int a = 0;
    //int massiv[35];
    for (int i = 0; i < 30; i++) {
        massiv[i] = 0;
    }

/*
    for (int i = 0; i < 30; i++) {
        a = rand()%100;
        massiv[i] = a;
        Derevo.add(a);
        std::cout << "Добавили  "<< a << std::endl;
    }
    */






    massiv_make();


    std::cout << "Добавленные ключи" << std::endl;
    for (int i = 0; i < 30; i++){
        std::cout << "Добавляем++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ " << massiv[i] << std::endl;
        Derevo.add(massiv[i]);
        std::cout << "Закончили++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ " << massiv[i] << std::endl;
        Derevo.print();

    }
    Derevo.print();



    for (int i = 0; i < 30; i++){
        std::cout << massiv[i] << " ";
    }

    std::cout << "Закончили++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ ";
int kaka = Derevo.search(72);

    std::cout <<  "\n Уровень  " << kaka << " ";
    //Derevo.search(44);


    return 0;
}

