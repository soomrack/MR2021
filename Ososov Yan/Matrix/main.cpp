#include <iostream>
#include "library.h"

int main() {
    srand(time(NULL));
    std::cout << "Hello, World!" << std::endl;
    int arr[9] = {1,2,3,4,5,6,7,8,111};
    Matrix A(3,3,arr, (unsigned int)9);
    A.print();
    Matrix B(3,3,arr, (unsigned int)9);
    B.print();
    Matrix C(B+A);
    C.print();
    Matrix D(3,3, ZEROS,3);
    D.print();
    Matrix E(D);
    E.print();
    printf("%d", A.det());
    //std::cout << A.det() << std::endl;

    return 0;
}
