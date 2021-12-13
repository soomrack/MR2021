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

/*void operationChoice(const Matrix A, const Matrix B) {
    char operation;
    cout << "Choose a matrix operation:\n"
            "\"+\" - addition (A+B)\n"
            "\"-\" - subtraction (A-B)\n"
            "\"*\" - multiplication (AxB)\n"
            "\"c\" - copying\n";
    cin >> operation;
    switch (operation) {
        case '+':
            Matrix C = A + B;
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

}*/

int main() {
    int a_rows, a_columns, b_rows, b_columns;
    assigningValues(&a_rows, &a_columns, &b_rows, &b_columns);
    Matrix A(a_rows, a_columns);
    Matrix B(b_rows, b_columns);
    A.random_input(a_rows, a_columns);
    B.random_input(b_rows, b_columns);
    cout << "\n Matrix A:\n";
    A.out();
    cout << "\n Matrix B:\n";
    B.out();
    //operationChoice(A, B);

    cout << "\n Matrix C (A+B):\n";
    Matrix C = A + B;

    cout << "\n Matrix D (A-B):\n";
    Matrix D = A - B;

    cout << "\n Matrix E (A*B):\n";
    Matrix E = A * B;

    cout << "\n Matrix F=A :\n";
    Matrix F = A;
    F.out();
    return 0;
}
