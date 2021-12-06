#include <iostream>
#include <ctime>
#include "library.h"
//Конструктор для набора матриц вручную
Matrix::Matrix(int rows, int cols) {
    this->rows = rows;
    this->cols = cols;
    content = new int[rows * cols];
    for (int i = 0; i < rows; ++i) {
        std::cout << "Row number " << i+1 << std::endl;
        for (int j = 0; j < cols; ++j) {
            std::cin >> content[j + rows * i];
        }
    }
}

//Конструктор для стандартных матриц (нулевая(type = 0) и единичная(type = 1)). При любых других оздается случайная матрица.
Matrix::Matrix(int rows, int cols, int type){
    this->rows = rows;
    this->cols = cols;
    srand(time(NULL));
    content = new int[rows * cols];
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            switch (type){
                case 0:
                    content[j + rows * i] = 0;
                    break;
                case 1:
                    if ( rows != cols){
                        std::cout << "Matrix must be square" << std::endl;
                        exit(1);
                    }
                    if (i == j){
                        content[j + rows * i] = 1;
                    } else{
                        content[j + rows * i] = 0;
                    }
                    break;
                case 3:
                    this->rows = rows;
                    this->cols = cols;
                    break;
                default:
                    content[j + rows * i] = rand() %20;
                    break;

            }
        }
    }
}


//Деструктор
Matrix::~Matrix() {
    delete [] content;
}

//Конструктор копирования
Matrix::Matrix(const Matrix &other) {
    this->rows = other.rows;
    this->cols = other.cols;
    if (this->rows != other.rows || this->cols != other.cols){
        std::cout << "Matrix aren't equal" << std::endl;
        exit(1);
    }
    this->content = new int [rows*cols];
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            this->content[j + rows * i] = other.content[j + rows * i];
        }
    }
}

//Конструктор перемещения
Matrix::Matrix(Matrix &&other) noexcept {
    this->rows = other.rows;
    this->cols = other.cols;
    if (this->rows != other.rows || this->cols != other.cols){
        std::cout << "Matrix aren't equal" << std::endl;
        exit(1);
    }
    this->content = other.content;
    other.content = nullptr;
    other.rows = 0;
    other.cols = 0;
}

//Перегрузка оператора присваивания
Matrix & Matrix::operator = (const Matrix &other){
    if (&other == this) {
        return *this;
    }
    this->rows = other.rows;
    this->cols = other.cols;
    if (this->rows != other.rows || this->cols != other.cols){
        std::cout << "Matrix aren't equal" << std::endl;
        exit(1);
    }
    this->content = new int [rows*cols];
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            this->content[j + rows * i] = other.content[j + rows * i];
        }
    }
    return *this;
}

//Перегрузка оператора присваивания для оператора перемещения
Matrix & Matrix::operator = (Matrix &&other) noexcept {
    if (this->rows != other.rows || this->cols != other.cols){
        std::cout << "Matrix aren't equal" << std::endl;
        exit(1);
    }
    this->rows = other.rows;
    this->cols = other.cols;
    delete [] this->content;
    this->content = new int [rows*cols];
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            this->content[j + rows * i] = other.content[j + rows * i];
        }
    }
    other.content = nullptr;
    other.rows = 0;
    other.cols = 0;
    return *this;
}

//Перегрузка оператора вычитания
Matrix Matrix::operator- (const Matrix &other){
    if (this->rows != other.rows || this->cols != other.cols){
        std::cout << "Matrix aren't equal" << std::endl;
        exit(1);
    }
    Matrix temp(this->rows, this->cols, 9);
    temp.content = new int [rows*cols];
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            temp.content[j + rows * i] = this->content[j + rows * i] - other.content[j + rows * i];
        }
    }
    return temp;
}

//Перегрузка оператора сложения
Matrix Matrix::operator+ (const Matrix &other){
    if (this->rows != other.rows || this->cols != other.cols){
        std::cout << "Matrix aren't equal" << std::endl;
        exit(1);
    }
    Matrix temp(this->rows, this->cols, 0);
    temp.content = new int [this->rows*this->cols];
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            temp.content[j + rows * i] = this->content[j + rows * i] + other.content[j + rows * i];
        }
    }
    return temp;
}
//Перегрузка оператора умножения
Matrix Matrix::operator * (const Matrix &other){
    if (this->cols != other.rows){
        std::cout << "It's impossible to do the operation" << std::endl;
        exit(1);
    }
    Matrix temp(this->rows, this->cols, 3);
    temp.content = new int [this->rows*other.cols];
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            temp.content[j + rows * i] = 0;
            for (int k = 0; k < other.rows; ++k) {
                temp.content[j + rows * i] += this->content[k + rows * i] * other.content[j + rows * k];
            }
        }
    }
    return temp;
}
//След матрицы
int Matrix::tr() {
    int matrix_trace = 0;
    if (this->rows != this->cols) {
        std::cout << "Matrix isn't square" << std::endl;
        exit(1);
    }
    for (int i = 0; i < this->rows; ++i) {
        matrix_trace += content[i + rows * i];
    }
    return matrix_trace;
}
//Вывод на экран
void Matrix::print() {
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->cols; ++j) {
            std::cout << this->content[j + rows * i] << "\t";
        }
        std::cout << std::endl;
    }
}

// Определитель меодом Гаусса
double Matrix::det(){
    double det;
    return det;
}
