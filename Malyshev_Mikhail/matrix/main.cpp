#include <iostream>
#include "matrix.h"

int main() {
    Matrix A(2, 2);
    A.set_values(1,1,4);
    A.set_values(1,2,-4);
    A.set_values(2,1,5);
    A.set_values(2,2,-3);
    A.print();
    int trac = A.trace();
    std::cout << trac << std::endl;
    Matrix B(4, 4);
    B.set_unit();
    B.print();
    return 0;
}
