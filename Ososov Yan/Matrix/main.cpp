#include <iostream>
#include "library.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    Matrix A(3,3,5);
    A.print();
    Matrix B( 3, 3, 1);
    B.print();
    Matrix C(B+A);
    C.print();


    //std::cout << A.det() << std::endl;

    return 0;
}
