#include <iostream>
#include "Matrix.h"

using namespace std;

void matrixSum(Matrix A, Matrix B) {
    if ((A.MatrixSizeHeight() == B.MatrixSizeHeight()) && (A.MatrixSizeWidth() == B.MatrixSizeWidth())) {
        cout << "\nFinal matrix:\n";
        for (int i = 0; i < A.MatrixSizeHeight() * A.MatrixSizeWidth(); i++)
            A.data[i] = A.data[i] + B.data[i];
        A.MatrixOut(A.MatrixSizeWidth(), A.MatrixSizeHeight());
    } else {
        cout << "\n\nERROR\n\nMatrix A and B must be the same size";
        exit(0);
    }
}

void matrixSub(Matrix A, Matrix B) {
    if ((A.MatrixSizeHeight() == B.MatrixSizeHeight()) && (A.MatrixSizeWidth() == B.MatrixSizeWidth())) {
        cout << "\nFinal matrix:\n";
        for (int i = 0; i < A.MatrixSizeWidth() * A.MatrixSizeHeight(); i++)
            A.data[i] = A.data[i] - B.data[i];
        A.MatrixOut(A.MatrixSizeWidth(), A.MatrixSizeHeight());
    } else {
        cout << "\n\nERROR\n\nMatrix A and B must be the same size";
        exit(0);
    }
}

void matrixMul(Matrix A, Matrix B) {
    int sum = 0;
    if (A.MatrixSizeWidth() == B.MatrixSizeHeight()) {
        cout << "\nFinal matrix:\n";
        Matrix C(A.MatrixSizeHeight(), B.MatrixSizeWidth());
        for (int i = 0, j = 0; i < A.MatrixSizeHeight() * B.MatrixSizeWidth(); i++) {
            for (int k = 0; k < A.MatrixSizeWidth(); k++)
                sum += A.data[k+j*A.MatrixSizeWidth()] * B.data[i - j * B.MatrixSizeWidth() + k * B.MatrixSizeWidth()];
            C.data[i] = sum;
            sum = 0;
            if ((i+1) % (A.MatrixSizeWidth()+1)==0) j++;
        }
        C.MatrixOut(C.MatrixSizeWidth(), C.MatrixSizeHeight());
    } else {
        cout << "\n\nERROR\n\nMatrix A and B must be commutative (columns A = rows B)";
        exit(0);
    }
}

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
            matrixSum(A, B);
            break;
        case '-':
            matrixSub(A, B);
            break;
        case '*':
            matrixMul(A, B);
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
