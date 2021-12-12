#include <iostream>
#include "Matrix_lib.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    Matrix A(3,3,4);
    Matrix B(3,3,0);
    Matrix C(A+B);
    std::cout << "Matrix A " << std::endl;
    A.print();
    std::cout << "Matrix B" << std::endl;
    B.print();
    std::cout << "Matrix C" << std::endl;
    C.print();

    std::cout << C.det() << std::endl;

    return 0;
}
