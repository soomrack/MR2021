#include "library.h"
#include <iostream>

//конструктор единичной мцы
Matrix::Matrix(unsigned int column) {
    this->column = column;
    row = column;
    become_null();
    data = new double[column * row];
    for (int i = 0; i < column * row; i = i + column + 1)
        data[i] = 1;
}

//конструктор для заполнения матрицы одним значением/нулевой мцы
Matrix::Matrix(unsigned int column, unsigned int row, double value) {
    this->column = column;
    this->row = row;
    data = new double[row * column];
    for (int i = 0; i < row * column; i++) {
        data[i] = value;
    }
}

// конструктор копирования
Matrix::Matrix(const Matrix &m) {
    row = m.row;
    column = m.column;
    delete(data);
    data = (double *) malloc(row * column * sizeof(double));
    memcpy(this->data, m.data, row * column * sizeof(double));
}

//конструктор перемещения
Matrix::Matrix(Matrix &&m) noexcept {
    row = m.row;
    column = m.column;
    data = m.data;
    m.row = 0;
    m.column = 0;
    m.data = nullptr;
}

//перегрузка операторов
Matrix Matrix::operator*(double scalar) {
    Matrix Result = *this;
    for (int i = 0; i < row * column; i++) {
        Result.data[i] = data[i] * scalar;
    }
    return Result;
}

Matrix Matrix::operator*(const Matrix &other) {
    if ((column) == (other.row)) {
        Matrix Result(row, other.column, 0.0);
        for (int i = 0; i < (row); i++) {
            for (int j = 0; j < Result.column; ++j) {
                for (int jj = 0; jj < Result.row; jj++) {
                    Result.data[i * Result.column + j] = Result.data[i * Result.column + j] +
                                                         data[(column) * i + jj] * other.data[other.column * jj + j];
                }
            }
        }
        return Result;
    } else
        cout
                << "ошибка операции умножения матриц: число столбцов первой матрицы должно совпадать с числом строк второй матрицы!";
}

Matrix Matrix::operator+(const Matrix &other) {
    if ((row == other.row) && (column == other.column)) {
        Matrix Result(other.column, other.row, 0.0);
        for (int i = 0; i < Result.row * Result.column; i++) {
            Result.data[i] = data[i] + other.data[i];
        }
        return Result;
    } else cout << "ошибка операции сложения матриц: матрицы должны быть одного размера\n" << endl;
}

Matrix Matrix::operator-(const Matrix &other) {
    if ((row == other.row) && (column == other.column)) {
        Matrix Result(other.column, other.row, 0.0);
        for (int i = 0; i < Result.row * Result.column; i++) {
            Result.data[i] = data[i] + other.data[i];
        }
        return Result;
    } else cout << "ошибка операции вычитания матриц: матрицы должны быть одного размера\n" << endl;
}

//ф-я для обнуления матрицы
void Matrix::become_null() {
    for (int i = 0; i < row * column; i++) {
        data[i] = 0.0;
    }
}

//вывод матрицы на консоль
void Matrix::print() {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            cout << data[column * i + j] << " ";
        }
        cout << endl;
    }
    cout << "\n" << endl;
}

//след матрицы
double Matrix::trace() {
    double trace = 0;
    if (column == row) {
        for (int i = 0; i < row * column; i = i + column + 1) {
            trace = trace + data[i];
        }
    } else cout << "ошибка операции нахождения следа матрицы: матрица должна быть квадратной\n" << endl;
    return trace;
}




