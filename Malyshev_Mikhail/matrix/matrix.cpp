#include "matrix.h"
#include <iostream>
#include <cstring>

Matrix::Matrix(int height, int width) { // инициализация матрицы
    this->height = height;
    this->width = width;
    data = (int *) malloc(height * width * sizeof(int));
    std::cout << "zero matrix has been created" << std::endl;
    for (int i = 0; i < (height * width); i++) {
        data[i] = 0;
    }
}

void Matrix::set_values(int n_row, int n_col, int value) { //заполнение одного элемента матрицы
    this->data[(n_row-1)*width+(n_col-1)] = value;
}

void Matrix::set_unit() { // единичная матрица
    this->height = height;
    this->width = width;
    if (height != width) {
        std::cout << "not square matrix" << std::endl;
    }
    else {
        for (int i = 0; i < (height * width); i++) {
            if (i%(height+1) == 0) {
                data[i] = 1;
            }
            else {
                data[i] = 0;
            }
        }
    }
}

Matrix::Matrix(const Matrix &m) { // копирование
    this->height = m.height;
    this->width = m.width;
    this->data = (int *) malloc(height * width * sizeof(int));
    std::memcpy(this->data, m.data, width * height * sizeof(int));
}
Matrix &Matrix :: operator =(const Matrix& m) { // перегрузка =
    this->height = m.height;
    this->width = m.width;
    free(data);
    data = (int *) malloc(height * width * sizeof(int));
    std::memcpy(this->data, m.data, height * width * sizeof(int));
    return *this;
}

Matrix Matrix :: operator +(const Matrix &m){ // перегрузка +
    if ((this -> height != m.height) || (this -> width != m.width))
    {
        Matrix Error(0,0);
        return Error;
    }
    else
    {
        Matrix Sum(height, width);
        for (int i = 0; i < height * width; i++) {
            Sum.data[i] = data[i] + m.data[i];
        }
        return Sum;
    }
}

Matrix Matrix :: operator -(const Matrix &m){ // перегрузка -
    if ((this -> height != m.height) || (this -> width != m.width))
    {
        Matrix Error(0,0);
        return Error;
    }
    else
    {
        Matrix Sub(height, width);
        for (int i = 0; i < height * width; i++) {
            Sub.data[i] = data[i] - m.data[i];
        }
        return Sub;
    }
}

Matrix Matrix :: operator *(const Matrix& m) { //перегрузка *
    if (this -> width != m.height){
        Matrix Error(0,0);
        return Error;
    }
    else {
        Matrix Mult(this -> height, m.width);

        int element = 0;
        for (int k = 0, j = 0; k < this -> height * m.width; k++) {

            for (int i = 0; i < this->width; i++) {
                element += this->data[i+j*this->width] * m.data[j+i*m.width];
            }
            Mult.data[k] = element;
            if ((k+1)%(this->width) == 0) {
                j++;
            };
        }
        return Mult;
    }
}

Matrix::~Matrix() { // деструктор
    free(data);
}

int Matrix::trace() { // след матрицы
    int tr = 0;
    if (height == width) {
        for (int i = 0; i < (height * width); i++) {
            if (i%(height+1) == 0) {
                tr += data[i];
            }
        }
        return tr;
    }
    else {
        std::cout << "not square matrix" << std::endl;
        return 0;
    }
}

void Matrix::print() { // вывод матрицы на экран
    std::cout << "matrix \n";
    for (int i = 0; i < (height * width); i++) {
        std::cout << data[i] << " ";
        if ((i + 1) % width == 0) {
            std::cout << "" << std::endl;
        }
    }
}