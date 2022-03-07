#include <iostream>
#include "matrix.h"

int main() {
    Matrix A(2, 2);
    A.set_values(0,0,4);
    A.set_values(0,1,-4);
    A.set_values(1,0,5);
    A.set_values(1,1,-3);
    A.print();
    int trac = A.trace();
    std::cout << trac << std::endl;
    Matrix B(4, 4);
    B.set_unit();
    B.print();
    return 0;
}
