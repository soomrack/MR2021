#include <iostream>
#include "b_tree.h"



#define SIZE_ARRAY 1000
#define RAND_MAX 100000



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

    BTree Derevo; //создали дерево

    massiv_make(); //массив с рандомными значениями 

    for (int i = 0; i < SIZE_ARRAY; i++){
        std::cout << massiv[i] << " ";
    }

    std::cout << " ";


    std::cout << "Добавленные ключи" << std::endl;
    for (int i = 0; i < SIZE_ARRAY; i++){
        std::cout << "Добавляем++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ " << massiv[i] << std::endl;
        Derevo.add(massiv[i]);
        //std::cout << "Закончили++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ " << massiv[i] << std::endl;
        Derevo.print();

    }

    Derevo.print();

    for (int i = 0; i < SIZE_ARRAY; i++){
        std::cout << massiv[i] << " ";
    }

    for (int i = 0; i < SIZE_ARRAY; i++){
        std::cout <<"Удаляем:  "<< massiv[i] << " #############################################################################################################################################\n";
        Derevo.print();
        Derevo.print_keys_in_string();
        Derevo.delete_key(massiv[i]);
    }

    Derevo.count_tree();


    Derevo.print();



    return 0;
}

