#include <iostream>
#include <ctime>
#include <cstring>
#include "Matrix.h"


Matrix::Matrix(){
    rows = 0;
    cols = 0;
    data = nullptr;
}


Matrix::Matrix(int rows, int cols, int *arr) {
        this->rows = rows;
        this->cols = cols;
        data = new int[rows * cols];
        memcpy(data, arr, sizeof(int) * length);
    }
}

Matrix::Matrix(int rows, int cols, Matrix_Type type, int value){
    this->rows = rows;
    this->cols = cols;
    data = new int[rows * cols];
    if (data == nullptr){
        return Matrix();
    }
}

void Matrix::zeros(){
    for (int i = 0; i < rows * cols; i++){
        data[i] = 0;
    }
}

void Matrix::identity(){
    zeros();
    for (int k = 0; k < rows*cols; ++k) {
        data[k + rows * k] = 1;
    }
}

void Matrix::diagonal(int value){
    zeros();
    for (int k = 0; k < rows*cols; ++k) {
        data[k + rows * k] = value;
    }
}

void Matrix::number(int value){
    for (int i = 0; i < rows * cols; i++){
        data[i] = value;
    }
}

void Matrix::random( int value){
    for (int i = 0; i < rows * cols; i++){
        data[i] = rand() % value;
    }
}
//Деструктор
Matrix::~Matrix() {
    delete [] data;
}

//Конструктор копирования
Matrix::Matrix(const Matrix &source)
{
    rows = source.rows;
    cols = source.cols;
    delete [] data;
    data = new int[rows * cols];
    memcpy(data,source.data,sizeof(int)*rows * cols);
}

//Конструктор перемещения
Matrix::Matrix(Matrix &&source) noexcept {
    this->rows = source.rows;
    this->cols = source.cols;
    this->data = source.data;
    source.data = nullptr;
    source.rows = 0;
    source.cols = 0;
}

//Перегрузка оператора присваивания
Matrix & Matrix::operator = (const Matrix &source){
    if (&source == this) {
        return *this;
    }
    rows = source.rows;
    cols = source.cols;
    delete [] data;
    data = new int[rows * cols];
    memcpy(data,source.data,sizeof(int)*rows * cols);
    return *this;
}

//Перегрузка оператора присваивания для оператора перемещения
Matrix & Matrix::operator= (Matrix &&source) noexcept {
    this->rows = source.rows;
    this->cols = source.cols;
    this->data = source.data;
    source.data = nullptr;
    source.rows = 0;
    source.cols = 0;
    return *this;
}

//Перегрузка оператора вычитания
Matrix Matrix::operator- (const Matrix &other){
    if (this->rows != other.rows || this->cols != other.cols){
        return Matrix();
    }
    Matrix result(other.rows, other.cols, TEMPORARY,0 );
    for (int i = 0; i < cols*rows; ++i) {
        result.data[i] = this->data[i] - other.data[i];
    }
    return result;

}

//Перегрузка оператора сложения
Matrix Matrix::operator+ (const Matrix &other){
    if (this->rows != other.rows || this->cols != other.cols){
        return Matrix();
    }
    Matrix result(other.rows, other.cols, TEMPORARY,0 );
    for (int i = 0; i < cols*rows; ++i) {
        result.data[i] = this->data[i] + other.data[i];
    }
    return result;

}
//Перегрузка оператора умножения
Matrix Matrix::operator* (const Matrix &other){
    if (this->cols != other.rows){
        return Matrix();
    }
    Matrix result(other.rows, other.cols, TEMPORARY,0 );
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            result.data[col + rows * row] = 0;
            for (int k = 0; k < other.rows; ++k) {
                result.data[col + rows * row] += this->data[k + rows * row] * other.data[col + rows * k];
            }
        }
    }
    return result;

}
//След матрицы
int Matrix::trace() {
    int matrix_trace = 0;
    for (int k = 0; k < rows || k < cols ; ++k) {
        matrix_trace += data[k + rows * k];
    }
    return matrix_trace;
}
//Вывод на экран
void Matrix::print() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << data[j + rows * i] << "\t";
        }
        std::cout << std::endl;
    }
}

// Определитель меодом Гаусса
int Matrix::det(){
    int det = 1;
    Matrix tmp(rows, cols, TEMPORARY,0 );
    memcpy(tmp.data,data,sizeof(int)*rows*cols );
    for (int diagonal = 0; diagonal < cols; ++diagonal) {
        if (tmp.data[diagonal + rows*diagonal] == 0){
            return 0;
        }
        for (int row = diagonal + 1; row < rows ; ++row) {
            int c = tmp.data[diagonal+row*rows]/tmp.data[diagonal+rows*diagonal];
            for (int col = diagonal; col < cols ; ++col) {
                tmp.data[col+row*rows] -= c * tmp.data[col+diagonal*rows];
            }

        }
    }
    for (int diagonal = 0; diagonal < cols; diagonal++){
        det *= tmp.data[diagonal + diagonal * rows];
    }
    tmp.data = nullptr;
    tmp.rows = 0;
    tmp.cols = 0;
    return det;
}
