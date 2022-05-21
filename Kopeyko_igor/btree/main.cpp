#include <iostream>
#include "b_tree.h"

#include <ctime>

unsigned int start_time = 0; // начальное время
unsigned int end_time = 0; // конечное время
unsigned int search_time = 0;



#define SIZE_ARRAY 10000
#define RAND_MAX 100000



int massiv[SIZE_ARRAY];


void massiv_make(){
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
        //std::cout << massiv[i] << " ";
    }




    for (int i = 0; i < SIZE_ARRAY; i++){
        Derevo.add(massiv[i]);
    }
    Derevo.count_tree();

    start_time = clock();

    for (int i = 0; i < SIZE_ARRAY; i++){
        Derevo.search(massiv[i]);
    }
    end_time = clock();


    Derevo.print();

    for (int i = 0; i < SIZE_ARRAY; i++){
        std::cout << massiv[i] << " ";
    }



    for (int i = 0; i < SIZE_ARRAY; i++){
        Derevo.delete_key(massiv[i]);
    }



    Derevo.count_tree(); //подсчет числа ключей в дереве
    Derevo.print();


    //подсет времени
    search_time = (end_time - start_time)/CLK_TCK;
    unsigned int search_time_orig = (end_time - start_time);
    std::cout << "Время выполенения программы (в милисекундах) = " << search_time <<std::endl;
    std::cout << "Время выполенения программы (в единицах) = " << search_time_orig <<std::endl;

    return 0;
}

