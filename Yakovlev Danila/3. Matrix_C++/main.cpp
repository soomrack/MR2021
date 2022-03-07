#include "library.h"

int main() {
    Matrix A(4,4);
    A.create(0, 0, 11);
    A.create(0, 1, 12);
    A.create(0, 2, 13);
    A.create(0, 3, 14);

    A.create(1, 0, 21);
    A.create(1, 1, 22);
    A.create(1, 2, 23);
    A.create(1, 3, 24);

    A.create(2, 0, 31);
    A.create(2, 1, 32);
    A.create(2, 2, 33);
    A.create(2, 3, 34);

    A.create(3, 0, 41);
    A.create(3, 1, 42);
    A.create(3, 2, 43);
    A.create(3, 3, 44);
    Matrix C(4,4);
    Matrix D(4,4);

    D.unit_matrix();
    C = A * D;
    printf("\n C=A*D\n");

    A.print();
    D.print();
    C.print();

    return 0;
}