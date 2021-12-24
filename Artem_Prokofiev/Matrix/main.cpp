#include <iostream>
#include "Matrix.h"
#include <iostream>



int main() {
    Matrix Exm (4,4);
    Exm.assigning(0,0,4);
    Exm.assigning(0,1,83);
    Exm.assigning(0,2,14);
    Exm.assigning(0,3,71);

    Exm.assigning(1,0,32);
    Exm.assigning(1,1,7);
    Exm.assigning(1,2,0);
    Exm.assigning(1,3,45);

    Exm.assigning(2,0,341);
    Exm.assigning(2,1,0);
    Exm.assigning(2,2,89);
    Exm.assigning(2,3,76);

    Exm.assigning(3,0,3);
    Exm.assigning(3,1,1);
    Exm.assigning(3,2,0);
    Exm.assigning(3,3,9);

    Exm.assigning(4,0,1);
    Exm.assigning(4,1,2);
    Exm.assigning(4,2,8);
    Exm.assigning(4,3,55);

    Exm.print();
    double g = Exm.determinant(Exm);
    std::cout << g << std::endl;
    return 0;
}