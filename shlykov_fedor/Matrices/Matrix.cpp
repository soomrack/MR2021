#include <iostream>
#include <ctime>
#include "Matrix.h"
#include <cstring>
#include <random>

using namespace std;

Matrix::Matrix(unsigned int rows, unsigned int cols, Matrix_type type) {
    this->rows = rows;
    this->cols = cols;
    memory_allocation();
    switch (type) {
        case RANDOM: set_random();break;
        case IDENTITY: set_identity(); break;
        case ONES: set_ones(); break;
        case ZERO: set_zero(); break;
        default: set_zero(); break;
    }
}

Matrix::Matrix(){
    rows = (unsigned int) 0;
    cols = (unsigned int) 0;
    matrix = nullptr;
}

Matrix::~Matrix() {
    free_memory();
}

Matrix::Matrix(const Matrix &other) {
    rows = other.rows;
    cols = other.cols;
    memory_allocation();
    memcpy(matrix, other.matrix, other.rows * other.cols * sizeof(double));
}

Matrix::Matrix(Matrix &&other) noexcept {
    rows = other.rows;
    cols = other.cols;
    matrix = other.matrix;
    other.matrix = nullptr;
    other.rows = (unsigned int) 0;
    other.cols = (unsigned int) 0;
}

Matrix Matrix::operator- (const Matrix &other){     //Перегрузка оператора вычитания
    if ((rows != other.rows) || (cols != other.cols)) {
        return Matrix();
    }
    Matrix temp(rows, cols, ZERO);
    for (unsigned int i = 0; i < rows * cols; ++i) {
        temp.matrix[i] = this->matrix[i] - other.matrix[i];
    }
    return temp;
}

Matrix Matrix::operator + (const Matrix &other){        //Перегрузка оператора сложения
    if ((rows != other.rows) || (cols != other.cols)) {
        return Matrix();
    }
    Matrix temp(rows, cols, ZERO);
    for (unsigned int i = 0; i < rows * cols; ++i) {
        temp.matrix[i] = matrix[i] + other.matrix[i];
    }
    return temp;
}

Matrix Matrix::operator * (const Matrix &other){        //Перегрузка оператора умножения
    if (cols != other.rows){
        return Matrix();
    }
    Matrix temp(rows, cols, ZERO);
    for (unsigned int i = 0; i < rows; ++i) {
        for (unsigned int j = 0; j < cols; ++j) {
            for (unsigned int k = 0; k < rows; ++k) {
                temp.matrix[j + i * cols] += matrix[k + i * cols] * other.matrix[j + k * (rows)];
            }
        }
    }
    return temp;
}

Matrix& Matrix::operator= (const Matrix &other){      //Перегрузка оператора присваивания
    if (&other == this) {
        return *this;
    }
    rows = other.rows;
    cols = other.cols;
    free_memory();
    memory_allocation();
    memcpy(matrix, other.matrix, other.rows * other.cols * sizeof(double));
    return *this;
}

Matrix& Matrix::operator= (Matrix &&other) noexcept {       //Перегрузка оператора присваивания для перемещения
    if (&other == this) {
        return *this;
    }
    rows = other.rows;
    cols = other.cols;
    free_memory();
    matrix = other.matrix;
    other.matrix = nullptr;
    other.rows = (unsigned int) 0;
    other.cols = (unsigned int) 0;
    return *this;
}

void Matrix::set_random() {
    for (unsigned int i = 0; i < rows * cols; ++i) {
        matrix[i] = rand();
    }
}

void Matrix::set_zero(){
    for (unsigned int i = 0; i < rows * cols; ++i) {
        matrix[i] = 0.0;
    }
}

void Matrix::set_ones(){
    for (unsigned int i = 0; i < rows * cols; ++i) {
        matrix[i] = 1.0;
    }
}

void Matrix::set_identity(){
    set_zero();
    for (unsigned int i = 0; i < rows; ++i) {
        matrix[i + i * rows] = 1.0;
    }
}

double Matrix::trace() {
    double matrix_trace = 0.0;
    for (unsigned int i = 0; i < rows; ++i) {
        matrix_trace += matrix[i + i * rows];
    }
    return matrix_trace;
}

double Matrix::det(){
    if (rows != cols) {
        return 0.0;
    }
    Matrix temp(*this);
    double det = 1.0;
    double div = 0.0;           //Хранит результат деления элементов строк для последующей триангуляция матрицы
    for (unsigned int i = 0; i < rows-1; ++i) {
        if ( abs( temp.matrix[i+cols*i])<0.001){
            return 0;
        }
        for (unsigned int j = i + 1; j < cols; ++j) {
            div = -(temp.matrix[i + cols * j] / temp.matrix[i + cols * i]);
            for (unsigned int k = i; k < rows; ++k) {
                temp.matrix[k + j * cols] += temp.matrix[k + i * cols] * div;
            }
        }
    }
    for (unsigned int i = 0; i < rows; ++i) {
        det *= temp.matrix[i + i*cols];
    }
    return det;
}
void Matrix::print() {
    for (unsigned int i = 0; i < rows; ++i) {
        for (unsigned int j = 0; j < cols; ++j) {
            cout << matrix[j + i * cols] << "\t";
        }
        cout << endl;
    }
}

void Matrix::memory_allocation() {
    matrix = new double[rows*cols];
}

void Matrix::free_memory() {
    delete [] matrix;
}
