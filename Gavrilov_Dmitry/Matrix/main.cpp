#include <iostream>
#include "Matrix_lib.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    srand(time(NULL));

    Matrix A(3,3);
    Matrix B(3,3,3);
    Matrix C(A+B);
    std::cout << "Matrix A " << std::endl;
    A.print();
    std::cout << "Matrix B" << std::endl;
    B.print();
    std::cout << "Matrix C" << std::endl;
    C.print();

    std::cout << C.determinate() << std::endl;

    return 0;
}
