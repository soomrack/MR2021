#include <iostream>
#include <ctime>
#include <cstring>
#include "library.h"

// Конструктор по умолчанию
Matrix::Matrix(){
    this->rows = 0;
    this->cols = 0;
    data = nullptr;
}

//Конструктор для набора матриц вручную
Matrix::Matrix(int rows, int cols, int *arr, unsigned int size) {
    if (size == rows*cols){
        this->rows = rows;
        this->cols = cols;
        data = new int[rows * cols];
        memcpy(data, arr,4*size);
    } else {
        Matrix();
    }

}

//Конструктор для стандартных матриц (нулевая(type = 0) и единичная(type = 1)). При любых других оздается случайная матрица.
Matrix::Matrix(int rows, int cols, Matrix_Type type, int value){
    this->rows = rows;
    this->cols = cols;
    data = new int[rows * cols];
    switch (type){
        case ZEROS:
            Matrix::set_zeros(value);
            break;
        case IDENTITY:
            Matrix::set_identity(value);
            break;
        case TEMPORARY:
            set_temporary(rows, cols);
            break;
        case RANDOM:
            set_random(value);
            break;
        default:
            Matrix::set_zeros(0);
            break;

    }
}

void Matrix::set_zeros( int value){
    for (int i = 0; i < rows * cols; i++){
        data[i] = value;
    }
}

void Matrix::set_identity(int value){
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (i == j){
                data[j + rows * i] = value;
            } else{
                data[j + rows * i] = 0;
            }
        }
    }

}
void Matrix::set_temporary( int weight, int height){
    this->rows = weight;
    this->cols = height;
    this->data = new int[rows * cols];
}
void Matrix::set_random( int value){
    for (int i = 0; i < rows * cols; i++){
        data[i] = rand() % value;
    }
}
//Деструктор
Matrix::~Matrix() {
    delete [] data;
}

//Конструктор копирования
Matrix::Matrix(const Matrix &source) {
    this->rows = source.rows;
    this->cols = source.cols;
    this->data = new int[rows * cols];
    memcpy(data,source.data,4*rows * cols);
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
    this->rows = source.rows;
    this->cols = source.cols;
    this->data = new int[rows * cols];
    memcpy(this->data,source.data,4*rows * cols);
    return *this;
}

//Перегрузка оператора присваивания для оператора перемещения
Matrix & Matrix::operator= (Matrix &&source) noexcept {
    this->rows = source.rows;
    this->cols = source.cols;
    delete [] this->data;
    this->data = new int[rows * cols];
    this->data = source.data;
    source.data = nullptr;
    source.rows = 0;
    source.cols = 0;
    return *this;
}

//Перегрузка оператора вычитания
Matrix Matrix::operator- (const Matrix &other){
    if (this->rows != other.rows || this->cols != other.cols){
        Matrix result;
        return result;
    }else{
        Matrix result(other.rows, other.cols, TEMPORARY,0 );
        for (int i = 0; i < cols*rows; ++i) {
            result.data[i] = this->data[i] - other.data[i];
        }
        return result;
    }

}

//Перегрузка оператора сложения
Matrix Matrix::operator+ (const Matrix &other){
    if (this->rows != other.rows || this->cols != other.cols){
        Matrix result;
        return result;;
    }else{
        Matrix result(other.rows, other.cols, TEMPORARY,0 );
        for (int i = 0; i < cols*rows; ++i) {
            result.data[i] = this->data[i] + other.data[i];
        }
        return result;
    }

}
//Перегрузка оператора умножения
Matrix Matrix::operator* (const Matrix &other){
    if (this->cols != other.rows){
        Matrix result;
        return result;
    }else{
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

}
//След матрицы
int Matrix::tr() {
    int matrix_trace = 0;
    for (int i = 0; i < this->rows || i < this->cols ; ++i) {
        matrix_trace += data[i + rows * i];
    }
    return matrix_trace;
}
//Вывод на экран
void Matrix::print() {
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->cols; ++j) {
            std::cout << this->data[j + rows * i] << "\t";
        }
        std::cout << std::endl;
    }
}

// Определитель меодом Гаусса
int Matrix::det(){
    int det = 1;
    Matrix tmp(this->rows, this->cols, TEMPORARY,0 );
    memcpy(tmp.data,this->data,4*rows*cols );
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
    return det;
}
