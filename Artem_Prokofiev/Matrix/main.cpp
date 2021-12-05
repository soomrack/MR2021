#include <iostream>
#include <cstdlib>
#include "Matrix.h"

enum comparisons {
    N = 3,
    Q = 4,
};

int main ()
{
    double M1[N][N] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    double M2[N][N] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    double M3[Q][Q] = {{1, 2, 3, 4}, {5, 6 , 7 ,8}, {9, 10, 11, 12}, {13, 14, 15, 16}};

    Matrix A = {3, 3, *M1};
    Matrix B = {3, 3, *M2};
    Matrix C = {4, 4, *M3};

    double trace, det;

    std::cout << "A = \n";
    A.print(A);
    std::cout << "\nB = \n";
    B.print(B);

    trace = A.trace(A);
    std::cout << "\n trace A = " << trace << "\n";

    Matrix Sum;
    std::cout << "\n A + B = \n";
    Sum = A.sum(A, B);
    Sum.print(Sum);

    Matrix Mult;
    std::cout << "\n A * B = \n";
    Mult = B.mult(A, B);
    Mult.print(Mult);

    Matrix MultConst;
    std::cout << "\n A * 5 = \n";
    MultConst = A.mult_scalar(5, A);
    MultConst.print(MultConst);

    Matrix Transp;
    std::cout << "\n A(transp) \n";
    Transp = A.transposition(A);
    Transp.print(Transp);


    Matrix Minor;
    std::cout << "\n minor B \n";
    Minor = B.Minor(1, 1, B);
    Minor.print(Minor);

    Matrix Dop;
    std::cout << "\n dop B \n";
    Dop = B.add(B);
    Dop.print(Dop);

    det = B.det(C);
    std::cout << "\n det C = " << det << "\n";

    Matrix One;
    std::cout << "\n one \n";
    One = One.single(4);
    One.print(One);

    Matrix power;
    std::cout << "\n B^2 \n";
    power = B.power(B, 2);
    power.print(power);

    return 0;
}