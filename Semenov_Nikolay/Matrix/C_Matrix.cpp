#include "C_Matrix.h"
#include <iostream>
using namespace std;

void M_Sum(Matrix A, Matrix B) {
    if ((A.M_Size_H() == B.M_Size_H()) && (A.M_Size_W() == B.M_Size_W())) {
        cout << "\nResult matrix:\n";
        for (int i = 0; i < A.M_Size_H() * A.M_Size_W(); i++)
            A.data[i] = A.data[i] + B.data[i];
        A.M_Out(A.M_Size_W(), A.M_Size_H());
    } else {
        cout << "\n\nERROR\n\nMatrix A and B must be the same size//";
        exit(0);
    }
}

void M_Sub(Matrix A, Matrix B) {
    if ((A.M_Size_H() == B.M_Size_H()) && (A.M_Size_W() == B.M_Size_W())) {
        cout << "\nFinal matrix:\n";
        for (int i = 0; i < A.M_Size_W() * A.M_Size_H(); i++)
            A.data[i] = A.data[i] - B.data[i];
        A.M_Out(A.M_Size_W(), A.M_Size_H());
    } else {
        cout << "\n\nERROR\n\nMatrix A and B must be the same size//";
        exit(0);
    }
}

void M_Mul(Matrix A, Matrix B) {
    int sum = 0;
    if (A.M_Size_W() == B.M_Size_H()) {
        cout << "\nFinal matrix:\n";
        Matrix C(A.M_Size_H(), B.M_Size_W());
        for (int i = 0, j = 0; i < A.M_Size_H() * B.M_Size_W(); i++) {
            for (int k = 0; k < A.M_Size_W(); k++)
                sum += A.data[k+j* A.M_Size_W()] * B.data[i - j * B.M_Size_W() + k * B.M_Size_W()];
            C.data[i] = sum;
            sum = 0;
            if ((i+1) % (A.M_Size_W() + 1) == 0) j++;
        }
        C.M_Out(C.M_Size_W(), C.M_Size_H());
    } else {
        cout << "\n\nERROR\n\nMatrix A and B must be commutative (columns A = rows B)//";
        exit(0);
    }
}

void assign_V(int *a_rows, int *a_columns, int *b_rows, int *b_columns) {
    cout << "Enter the number of rows of matrix A\n";
    cin >> *a_rows;
    cout << "Enter the number of columns of matrix A\n";
    cin >> *a_columns;
    cout << "Enter the number of rows of matrix B\n";
    cin >> *b_rows;
    cout << "Enter the number of columns of matrix B\n";
    cin >> *b_columns;
}

void op_Switch(const Matrix A, const Matrix B) {
    char operation;
    cout << "Choose a matrix operation:\n"
            "\"+\" - addition (A+B)\n"
            "\"-\" - subtraction (A-B)\n"
            "\"*\" - multiplication (AxB)\n"
            "\"c\" - copying\n";
    cin >> operation;
    switch (operation) {
        case '+':
            M_Sum(A, B);
            break;
        case '-':
            M_Sub(A, B);
            break;
        case '*':
            M_Mul(A, B);
            break;
        case 'c':
            break;
        default:
            cout << "You make some mistake(s)//";
            break;
    }
}

int main() {
    int a_rows, a_columns, b_rows, b_columns;
    assign_V(&a_rows, &a_columns, &b_rows, &b_columns);
    Matrix A(a_rows, a_columns);
    Matrix B(b_rows, b_columns);
    A.M_Rand(a_rows, a_columns);
    B.M_Rand(b_rows, b_columns);
    cout << "\nMatrix A:\n";
    A.M_Out(a_columns, a_rows);
    cout << "\nMatrix B:\n";
    B.M_Out(b_columns, b_rows);
    op_Switch(A, B);
    return 0;
}
