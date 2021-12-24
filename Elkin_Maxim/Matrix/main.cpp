#include <iostream>
#include "matrix_lib.h"
#include "matrix_lib.cpp"
using namespace std;

//example of using matrix library
int main() {
    Matrix A(3,2);
    A.print_matrix();

    double arrayA[4][3] = {{1,2,5},
                          {8,3,7},
                          {6,9,2},
                          {4,13,88}};
    A.set_matrix_from_2d(arrayA);
    cout << "New A ";
    A.print_matrix();

    Matrix B(A);
    B.print_matrix();
    double arrayB[4][3] = {{8.8,4,6},
                           {13,5,9},
                           {13,37,41},
                           {5.5,16,3}};
    B.set_matrix_from_2d(arrayB);
    cout << "New B ";
    B.print_matrix();
    cout << "determinant of B: " << B.get_det() << endl;

    Matrix C = A + B;
    cout << "result of A sum B" << endl;
    C.print_matrix();

    Matrix D;
    D = A - B;
    cout << "result of A sub B" << endl;
    D.print_matrix();

    double mult1[3][2] = {{1,2},
                          {6,4},
                          {12,7}};

    double mult2[2][3] = {{9,5,6},
                          {4,3,1}};

    A.set_matrix_from_2d(mult1);
    cout << "New A ";
    A.print_matrix();

    B.set_matrix_from_2d(mult2);
    cout <<"New B ";
    B.print_matrix();

    Matrix E = A * B;
    cout << "multiplication of A and B" << endl;
    E.print_matrix();

    Matrix F = B;
    cout << "matrix F is the same as B" << endl;
    F.print_matrix();

    double det [4][4] = {{3,4,6,8},
                         {7,8.7,2.2,4},
                         {1,8,3,4},
                         {13,3,5,7}};

    F.set_matrix_from_2d(det);
    cout <<"New F ";
    F.print_matrix();
    cout << "determinant of F: " << F.get_det() << endl;

    double m[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    F.set_matrix_from_1d(m);
    F.print_matrix();

    return 0;
}
