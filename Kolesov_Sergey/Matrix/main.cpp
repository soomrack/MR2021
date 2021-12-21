#include <iostream>
#include "Matrix.h"


int main ()
{
    double A[3][3] = {1, 2, 3,
                      4, 5, 6,
                      7, 8, 9};
    double B[3][3] ={{1, 2, 3},
                     {4, 0, 6},
                     {7, 8, 9}};

    Matrix M1(3, 3, *A);
    Matrix M2(3, 3, *A);

    M1.print();
    M2.print();
    M1.swap_cols(1, 3);
    M1.swap_rows(1, 3);
    M1.print();
    Matrix M3;
    M3 = M1 + M2;
    M3.print();
    M3.normalization();
    M3.print();
    std::cout << M3(2,2) << "\n";
    std::cout << M2.det()   << "\n"
              << M2.trace() << "\n"
              << M2.minorij(2,2) << "\n"
              << M2.complement(2,2) << "\n";
    Matrix M4(3,3,*B);
    M3 = M4;
    M4.print();
    M4.reverse();
    M4.print();
    M3 = M3 * M4;
    M3.print();

    return 0;
}