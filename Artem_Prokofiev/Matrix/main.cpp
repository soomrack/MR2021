#include <iostream>
#include "Matrix.h"


int main() {
    Matrix Exm (4,4);
    Exm.value(0,0,4);
    Exm.value(0,1,83);
    Exm.value(0,2,14);
    Exm.value(0,3,71);

    Exm.value(1,0,32);
    Exm.value(1,1,7);
    Exm.value(1,2,0);
    Exm.value(1,3,45);

    Exm.value(2,0,341);
    Exm.value(2,1,0);
    Exm.value(2,2,89);
    Exm.value(2,3,76);

    Exm.value(3,0,3);
    Exm.value(3,1,1);
    Exm.value(3,2,0);
    Exm.value(3,3,9);

    Exm.value(4,0,1);
    Exm.value(4,1,2);
    Exm.value(4,2,8);
    Exm.value(4,3,55);

    Exm.print();
    double g = Exm.determinant(Exm);
    std::cout << g << std::endl;
    return 0;
}