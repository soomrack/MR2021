#include <iostream>
#include "b_tree.h"



#define SIZE_ARRAY 85
#define RAND_MAX 100



int massiv[SIZE_ARRAY];


void massiv_make(){
    //int * copy = mass;
    for (int i = 0; i <SIZE_ARRAY; i++){
        massiv[i] = 0;
    }

    int a = 0;
    int fatal = -1;
    for (int i = 0; i < SIZE_ARRAY; i++) {
        fatal = -1;
        while( fatal != 0 ) {
            start:
            fatal = 0;
            a = rand() % RAND_MAX;

            for (int k = 0; k < i; k++) {
                if (massiv[k] == a) {
                    fatal++;
                }
                if (massiv[k] == 0) {
                    fatal++;
                }
            }
            if (fatal == 0) {
                massiv[i] = a;
            }
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


/*
    for (int i = 0; i < 30; i++) {
        a = rand()%100;
        massiv[i] = a;
        Derevo.add(a);
        std::cout << "Добавили  "<< a << std::endl;
    }
    */






    massiv_make();
    for (int i = 0; i < SIZE_ARRAY; i++){
        std::cout << massiv[i] << " ";
    }
    std::cout << " ";


    std::cout << "Добавленные ключи" << std::endl;
    for (int i = 0; i < SIZE_ARRAY; i++){
        std::cout << "Добавляем++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ " << massiv[i] << std::endl;
        Derevo.add(massiv[i]);
        std::cout << "Закончили++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ " << massiv[i] << std::endl;
        Derevo.print();

    }
    //Derevo.add(88);
    Derevo.print();



    for (int i = 0; i < SIZE_ARRAY; i++){
        std::cout << massiv[i] << " ";
    }

    std::cout << "Закончили++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ ";

    for (int i = 0; i < SIZE_ARRAY; i++){
        std::cout <<"Удаляем:  "<< massiv[i] << " #############################################################################################################################################\n";
        Derevo.print();
        Derevo.print_keys_in_string();
        Derevo.delete_key(massiv[i]);
    }

    Derevo.count_tree();


    Derevo.print();



 /*
    BTree Kakashka;

    Kakashka.add(1);
    Kakashka.add(2);
    Kakashka.add(3);
    Kakashka.add(4);
    Kakashka.add(5);
    Kakashka.add(6);
    Kakashka.add(7);
    Kakashka.add(8);
    Kakashka.add(9);
    Kakashka.add(10);
    Kakashka.add(11);
    Kakashka.add(12);
    Kakashka.add(13);
    Kakashka.add(14);
    Kakashka.add(15);
    Kakashka.add(16);
    Kakashka.add(17);
    Kakashka.add(18);
    Kakashka.add(19);
    Kakashka.add(20);
    Kakashka.add(21);
    Kakashka.add(22);
    Kakashka.add(23);
    Kakashka.add(24);
    Kakashka.add(25);
    Kakashka.add(26);
    Kakashka.add(27);

    Kakashka.delete_key(15);
    Kakashka.delete_key(14);
    Kakashka.delete_key(9);
    Kakashka.delete_key(13);
    Kakashka.delete_key(12);
    Kakashka.delete_key(19);
    Kakashka.delete_key(18);
    Kakashka.delete_key(17);
    Kakashka.delete_key(16);
    Kakashka.delete_key(21);
    Kakashka.delete_key(20);
    Kakashka.delete_key(23);
    Kakashka.delete_key(3);
    Kakashka.delete_key(7);
    Kakashka.delete_key(6);
    Kakashka.delete_key(22);
    Kakashka.delete_key(5);
    Kakashka.delete_key(24);
    Kakashka.delete_key(11);
    Kakashka.delete_key(2);
    Kakashka.delete_key(27);
    Kakashka.delete_key(1);
    Kakashka.delete_key(8);
    Kakashka.delete_key(26);
    Kakashka.delete_key(25);
    Kakashka.delete_key(4);
    Kakashka.delete_key(10);
    Kakashka.delete_key(0);

    Kakashka.print();




    //Kakashka.delete_key(15);
    //Kakashka.delete_key(16);
    //Kakashka.delete_key(14);
    //Kakashka.delete_key(13);
    //Kakashka.delete_key(1);

    Kakashka.print();

*/



    return 0;
}

