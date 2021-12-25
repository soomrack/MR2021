#include <iostream>
#include <cmath>

#include "library.h"


Matrix::Matrix(){
    height = 1;
    width = 1;
    data = (double *)malloc(sizeof(double));
    data[0]=0;
}

Matrix::Matrix(int height, int width) {
    this->height = height;
    this->width = width;
    data = (double *)malloc(height * width * sizeof(double));
    if (data == nullptr){
        this->height = 0;
        this->width = 0;
    } else for (int i = 0; i < height * width; ++i){
            data[i] = 0;
    }
}

Matrix::Matrix(int height, int width, double (&data)[]) {
    this->height = height;
    this->width = width;
    this->data = (double *)malloc(height * width * sizeof(double));
    if (this->data == nullptr){
        this->height = 0;
        this->width = 0;
    } else for (int i = 0; i < width * height; ++i) {
        this->data[i] = data[i];
    }
}

Matrix::Matrix(Matrix &&m)  noexcept {
    height = m.height;
    width = m.width;
    free(data);
    data = m.data;
    m.data = nullptr;
}

Matrix::Matrix(const Matrix &m) {
    height = m.height;
    width = m.width;
    data = (double *)malloc(height * width * sizeof(double));
    if (data == nullptr){
        height = 0;
        width = 0;
    } else memcpy(data,  m.data,height * width * (sizeof(double)));
}

Matrix & Matrix::operator= (const Matrix &m) {
    if (&m == this) { return *this; }
    height = m.height;
    width = m.width;
    free(data);
    data = (double *) malloc(height * width * sizeof(double));
    if (data == nullptr){
        height = 0;
        width = 0;
    } else memcpy(data, m.data, height * width * (sizeof(double)));
    return *this;
}

Matrix Matrix::operator+ (const Matrix &m){
    if ((m.width != this->width) or (m.height != this->height)){
        std::cout<<"Summation error\n";
        return {0,0};
    }

    auto * matrix = new Matrix(m.height, m.width);
    //Проверка выделения памяти производится в конструкторе
    for (int i = 0; i < matrix->height * matrix->width; ++i) {
        matrix->data[i] = this->data[i] + m.data[i];
    }

    return * matrix;
}

Matrix Matrix::operator* (const Matrix &m){
    if (m.height != this->width){
        std::cout<<"Multiplication error\n";
        return {0,0};
    }
    auto * matrix = new Matrix(this->height, m.width);
    //Проверка выделения памяти производится в конструкторе
    for (int i = 0; i < this->height; ++i) {
        for (int j = 0; j < m.width; ++j) {
            double Temp = 0.0;
            for (int k = 0; k < m.height; ++k) {
                Temp += this->data[ i * this->width + k] * m.data[m.width * k + j];
            }
            matrix->data[i * width + j] = Temp;
        }
    }

    return * matrix;
}

void Matrix::print() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            std::cout<< data[i * width + j]<<' ';
        }
        std::cout << '\n';
    }
}

double Matrix::trace() {
    if (this->width != this->height){
        return std::nanf("");
    }
    double Temp = 0.0;
    for (int i = 0; i < height; ++i) {
        Temp+= data[i * width + i];
    }
    return Temp;
}

Matrix::~Matrix() {
    free(data);
}

