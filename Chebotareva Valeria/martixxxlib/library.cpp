#include "library.h"

#include <iostream>

void Matrix::print() {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            cout << data[column * i + j] << " ";
        }
        cout << endl;
    }
    cout << "\n" << endl;
}

double Matrix::trace() {
    double trace = 0;
    if (column == row) {
        for (int i = 0; i < row; i++)
            for (int j = 0; j < column; j++) {
                if (i == j) {
                    trace = trace + data[column * i + j];
                }
            }
    } else cout << "ошибка операции нахождения следа матрицы: матрица должна быть квадратной\n" << endl;
    return trace;
}

Matrix Matrix::operator*(double scalar) {
    Matrix Result = *this;
    for (int i = 0; i < this->row; i++) {
        for (int j = 0; j < this->column; j++) {
            Result.data[this->column * i + j] = this->data[this->column * i + j] * scalar;
        }
    }
    return Result;
}

Matrix Matrix::operator*(const Matrix &other) {
    if ((this->column) == (other.row)) {
        Matrix Result(this->row, other.column, 0);
        for (int i = 0; i < (this->row); i++) {
            for (int j = 0; j <Result.column; ++j) {
                for (int jj = 0; jj < Result.row; jj++) {
                    Result.data[i * Result.column + j] = Result.data[i * Result.column + j]+this->data[(this->column)*i+jj]*other.data[other.column*jj+j];
                }
            }
        }
        return Result;
    } else cout << "ошибка операции умножения матриц: число столбцов первой матрицы должно совпадать с числом строк второй матрицы!";
}

Matrix Matrix::operator+(const Matrix &other) {
    if ((this->row == other.row) && (this->column == other.column)) {
        Matrix Result(other.column, other.row, 0);
        for (int i = 0; i < Result.row; i++) {
            for (int j = 0; j < Result.column; j++) {
                Result.data[Result.column * i + j] =
                        this->data[this->column * i + j] + other.data[other.column * i + j];
            }
        }
        return Result;
    } else cout << "ошибка операции сложения матриц: матрицы должны быть одного размера\n" << endl;
}

Matrix Matrix::operator-(const Matrix &other) {
    if ((this->row == other.row) && (this->column == other.column)) {
        Matrix Result(other.column, other.row, 0);
        for (int i = 0; i < Result.row; i++) {
            for (int j = 0; j < Result.column; j++) {
                Result.data[Result.column * i + j] =
                        this->data[this->column * i + j] - other.data[other.column * i + j];
            }
        }
        return Result;
    } else cout << "ошибка операции вычитания матриц: матрицы должны быть одного размера\n" << endl;
}


