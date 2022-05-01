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
    //выведем массив
    for (int i = 0; i < SIZE_ARRAY; i++){
        std::cout << massiv[i] << " ";
    }

    for (int i = 0; i < SIZE_ARRAY; i++){
        Derevo.add(massiv[i]);
    }

    Derevo.print();

    for (int i = 0; i < SIZE_ARRAY; i++){
        std::cout << massiv[i] << " ";
    }

    for (int i = 0; i < SIZE_ARRAY; i++){
        //Derevo.print();
        //Derevo.print_keys_in_string();
        Derevo.delete_key(massiv[i]);
    }

    Derevo.count_tree(); //подсчет числа ключей в дереве
    Derevo.print();
    return 0;
}

