#include "C_Matrix.h"
#include <iostream>
using namespace std;

void assign_V(int *A_Rows, int *A_Columns, int *B_Rows, int *B_Columns) {
    cout << "Enter the number of rows of matrix A\n";
    cin >> *A_Rows;
    cout << "Enter the number of columns of matrix A\n";
    cin >> *A_Columns;
    cout << "Enter the number of rows of matrix B\n";
    cin >> *B_Rows;
    cout << "Enter the number of columns of matrix B\n";
    cin >> *B_Columns;
}

int main() {
    int A_Rows, A_Columns, B_Rows, B_Columns;
    assign_V(&A_Rows, &A_Columns, &B_Rows, &B_Columns);
    Matrix A(A_Rows, A_Columns);
    Matrix B(B_Rows, B_Columns);
    A.Rand(A_Rows, A_Columns);
    B.Rand(B_Rows, B_Columns);
    cout << "\n Matrix A:\n";
    A.Output();
    cout << "\n Matrix B:\n";
    B.Output();

    cout << "\n Matrix C (A+B):\n";
    Matrix C = A + B;

    cout << "\n Matrix D (A-B):\n";
    Matrix D = A - B;

    cout << "\n Matrix E (A*B):\n";
    Matrix E = A * B;

    cout << "\n Matrix F=A :\n";
    Matrix F = A;
    F.Output();

    cout<<"\n Trace(A)="<<A.Trace();
    cout<<"\n Trace(B)="<<B.Trace()<<"\n";

    cout<<"\n Det(A)="<<A.Determinant();
    cout<<"\n Det(B)="<<B.Determinant()<<"\n";
    return 0;
}