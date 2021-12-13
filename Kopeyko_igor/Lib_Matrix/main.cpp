#include <iostream>
#include "matrixlib.h"


int main() {
    Matrix T4(4,4);
    T4.set(0,0,23);
    T4.set(0,1,49);
    T4.set(0,2,21);
    T4.set(0,3,75);

    T4.set(1,0,0);
    T4.set(1,1,99);
    T4.set(1,2,9);
    T4.set(1,3,63);

    T4.set(2,0,0);
    T4.set(2,1,0);
    T4.set(2,2,8);
    T4.set(2,3,63);

    T4.set(3,0,0);
    T4.set(3,1,0);
    T4.set(3,2,0);
    T4.set(3,3,8);

    T4.print();
    double g = T4.det();
    std::cout << g << std::endl;
    return 0;
}
