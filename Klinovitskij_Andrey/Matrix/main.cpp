#include <iostream>
#include "Matrix.h"

using namespace std;

void assigningValues(int *a_rows, int *a_columns, int *b_rows, int *b_columns) {
    cout << "Enter the number of rows of matrix A\n";
    cin >> *a_rows;
    cout << "Enter the number of columns of matrix A\n";
    cin >> *a_columns;
    cout << "Enter the number of rows of matrix B\n";
    cin >> *b_rows;
    cout << "Enter the number of columns of matrix B\n";
    cin >> *b_columns;
}

void operationChoice(const Matrix A, const Matrix B) {
    char operation;
    cout << "Choose a matrix operation:\n"
            "\"+\" - addition (A+B)\n"
            "\"-\" - subtraction (A-B)\n"
            "\"*\" - multiplication (AxB)\n"
            "\"c\" - copying\n";
    cin >> operation;
    switch (operation) {
        case '+':
            MatrixSum(A, B);
            break;
        case '-':
            MatrixSub(A, B);
            break;
        case '*':
            MatrixMul(A, B);
            break;
        case 'c':
            break;
        default:
            cout << "You make mistake";
            break;
    }

}

int main() {
    int a_rows, a_columns, b_rows, b_columns;
    assigningValues(&a_rows, &a_columns, &b_rows, &b_columns);
    Matrix A(a_rows, a_columns);
    Matrix B(b_rows, b_columns);
    A.MatrixRandom(a_rows, a_columns);
    B.MatrixRandom(b_rows, b_columns);
    cout << "\n Matrix A:\n";
    A.MatrixOut(a_columns, a_rows);
    cout << "\n Matrix B:\n";
    B.MatrixOut(b_columns, b_rows);
    operationChoice(A, B);
    return 0;
}
