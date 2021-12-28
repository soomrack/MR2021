#include "C_Matrix.h"
#include <iostream>
using namespace std;

void assign_V(int *A_Rows, int *A_Columns, int *B_Rows, int *B_Columns) {
    cout << "Enter the number of height of matrix A\n";
    cin >> *A_Rows;
    cout << "Enter the number of width of matrix A\n";
    cin >> *A_Columns;
    cout << "Enter the number of height of matrix B\n";
    cin >> *B_Rows;
    cout << "Enter the number of width of matrix B\n";
    cin >> *B_Columns;
}

int main() {
    int A_Rows, A_Columns, B_Rows, B_Columns;
    assign_V(&A_Rows, &A_Columns, &B_Rows, &B_Columns);
    Matrix A(A_Rows, A_Columns, RANDOM);
    Matrix B(B_Rows, B_Columns, RANDOM);
    cout << "\n Matrix A:\n";
    A.output();
    cout << "\n Matrix B:\n";
    B.output();

    cout << "\n Matrix C (A+B):\n";
    Matrix C = A + B;

    cout << "\n Matrix D (A-B):\n";
    Matrix D = A - B;

    cout << "\n Matrix E (A*B):\n";
    Matrix E = A * B;

    cout << "\n Matrix F=A :\n";
    Matrix F = A;
    F.output();

    cout<<"\n trace(A)="<< A.trace();
    cout << "\n trace(B)=" << B.trace() << "\n";

    cout<<"\n Det(A)="<< A.determinant();
    cout << "\n Det(B)=" << B.determinant() << "\n";
    return 0;
}