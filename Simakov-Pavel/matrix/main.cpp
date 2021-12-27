#include <iostream>
#include "library.h"

int main() {
    Matrix A(3,3);
    A.user_input();
    A.print();
    std::cout << A.det() << std::endl;
    return 0;
}
