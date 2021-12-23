#include <iostream>
#include "matrixlib.h"


int main() {
    /*
    Matrix RR(4,4,1);
    Matrix T4(4,4);
    T4.set(0,0,1);
    T4.set(0,1,49);
    T4.set(0,2,21);
    T4.set(0,3,75);

    T4.set(1,0,1);
    T4.set(1,1,9);
    T4.set(1,2,2);
    T4.set(1,3,2);

    T4.set(2,0,76);
    T4.set(2,1,23);
    T4.set(2,2,12);
    T4.set(2,3,4);

    T4.set(3,0,0);
    T4.set(3,1,0);
    T4.set(3,2,0);
    T4.set(3,3,1);

    T4.print();

    Matrix Als (2,2);
    Als.set(0,0,1);
    Als.set(0,1,3);
    Als.set(1,0,7);
    Als.set(1,1,9);
    Als.print();
*/
    Matrix T4 (5,5);
    T4.set(0,0,0);
    T4.set(0,1,233);
    T4.set(0,2,3);
    T4.set(0,3,4);
    T4.set(0,4,5);

    T4.set(1,0,6);
    T4.set(1,1,0);
    T4.set(1,2,8);
    T4.set(1,3,9);
    T4.set(1,4,10);

    T4.set(2,0,11);
    T4.set(2,1,12);
    T4.set(2,2,0);
    T4.set(2,3,14);
    T4.set(2,4,15);

    T4.set(3,0,123);
    T4.set(3,1,17);
    T4.set(3,2,18);
    T4.set(3,3,0);
    T4.set(3,4,20);

    T4.set(4,0,21);
    T4.set(4,1,22);
    T4.set(4,2,23);
    T4.set(4,3,224);
    T4.set(4,4,0);
    T4.print();
    double g = T4.det();
    std::cout << g << std::endl;
    return 0;
}
