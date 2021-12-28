#include <iostream>
#include <ctime>
#include "Matrix.h"
#include <cstring>
#include <random>

using namespace std;

Matrix::Matrix(int rows, int cols, Matrix_type type) {
    this->rows = rows;
    this->cols = cols;
    memory_allocation();
    if (matrix != nullptr) {            //Проверка успешного выделения памяти
        switch (type) {
            case RANDOM: set_random();break;
            case IDENTITY: set_identity(); break;
            case ONES: set_ones(); break;
            case ZERO: set_zero(); break;
            default: set_zero(); break;
        }
    }
    else {
        this->cols = 0;
        this->rows = 0;
    }
}

Matrix::Matrix(){
    this->rows = 0;
    this->cols = 0;
    matrix = nullptr;
}

Matrix::~Matrix() {
    free_memory();
}

Matrix::Matrix(const Matrix &other) {
    this->rows = other.rows;
    this->cols = other.cols;
    memory_allocation();
    if (matrix != nullptr) {
        memcpy(matrix, other.matrix, other.rows * other.cols * sizeof(double));
    }
    else {
        this->rows = 0;
        this->cols = 0;
    }
}

Matrix::Matrix(Matrix &&other) noexcept {
    this->rows = other.rows;
    this->cols = other.cols;
    this->matrix = other.matrix;
    other.matrix = nullptr;
    other.rows = 0;
    other.cols = 0;
}

Matrix Matrix::operator- (const Matrix &other){     //Перегрузка оператора вычитания
    if ((rows != other.rows) || (cols != other.cols)) {
        return Matrix();
    }
    Matrix temp(rows, cols, ZERO);
    for (int i = 0; i < rows * cols; ++i) {
        temp.matrix[i] = this->matrix[i] - other.matrix[i];
    }
    return temp;
}

Matrix Matrix::operator + (const Matrix &other){        //Перегрузка оператора сложения
    if ((rows != other.rows) || (cols != other.cols)) {
        return Matrix();
    }
    Matrix temp(rows, cols, ZERO);
    for (int i = 0; i < rows * cols; ++i) {
        temp.matrix[i] = matrix[i] + other.matrix[i];
    }
    return temp;
}

Matrix Matrix::operator * (const Matrix &other){        //Перегрузка оператора умножения
    if (this->cols != other.rows){
        return Matrix();
    }
    Matrix temp(rows, cols, ZERO);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            for (int k = 0; k < rows; ++k) {
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
    if (matrix != nullptr) {
        memcpy(matrix, other.matrix, other.rows * other.cols * sizeof(double));
    }
    else {
        this->cols = 0;
        this->rows = 0;
    }
    return *this;
}

Matrix& Matrix::operator= (Matrix &&other) noexcept {       //Перегрузка оператора присваивания для перемещения
    if (&other == this) {
        return *this;
    }
    this->rows = other.rows;
    this->cols = other.cols;
    free_memory();
    this->matrix = other.matrix;
    other.matrix = nullptr;
    other.rows = 0;
    other.cols = 0;
    return *this;
}

void Matrix::set_random() {
    srand(time(nullptr));
    for (int i = 0; i < rows * cols; ++i) {
        matrix[i] = rand() % 3;
    }
}

void Matrix::set_zero(){
    for (int i = 0; i < rows * cols; ++i) {
        matrix[i] = 0.0;
    }
}

void Matrix::set_ones(){
    for (int i = 0; i < rows * cols; ++i) {
        matrix[i] = 1.0;
    }
}

void Matrix::set_identity(){
    set_zero();
    for (int i = 0; i < rows; ++i) {
        matrix[i + i * rows] = 1.0;
    }
}

double Matrix::trace() {
    double matrix_trace = 0.0;
    for (int i = 0; i < rows; ++i) {
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
    for (int i = 0; i < rows-1; ++i) {
        for (int j = i + 1; j < cols; ++j) {
            div = -(temp.matrix[i + cols * j] / temp.matrix[i + cols * i]);
            for (int k = i; k < rows; ++k) {
                temp.matrix[k + j * cols] += temp.matrix[k + i * cols] * div;
            }
        }
    }
    for (int i = 0; i < rows; ++i) {
        det *= temp.matrix[i + i*cols];
    }
    return det;
}

int Matrix::max_position(int pos){
    int max_pos = pos;
    double max = abs(matrix[max_pos]);
    for (int j = pos + cols; j < rows * cols; j += cols) {
        if (abs(matrix[j]) > max) {
            max_pos = j;
            max = abs(matrix[j]);
        }
    }
    return max_pos;
}

void Matrix::print() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
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
