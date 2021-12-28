#include <iostream>
#include <cmath>

#include "library.h"


Matrix::Matrix(){
    height = 1;
    width = 1;
    data = (double *)malloc(sizeof(double));
    if (data == nullptr){
        this->height = 0;
        this->width = 0;
        return;
    }
    data[0]=0.0;
}

Matrix::Matrix(int height, int width) {
    this->height = height;
    this->width = width;
    data = (double *)malloc(height * width * sizeof(double));
    if (data == nullptr){
        this->height = 0;
        this->width = 0;
        return;
    }
    for (int i = 0; i < height * width; ++i){
            data[i] = 0.0;
    }
}

template<unsigned int S>
Matrix::Matrix(int height, int width, double (&data)[S]) {
    this->height = height;
    this->width = width;
    this->data = (double *)malloc(height * width * sizeof(double));
    if (this->data == nullptr){
        this->height = 0;
        this->width = 0;
        return;
    }
    memcpy(this->data,  data,height * width * (sizeof(double)));
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
        return;
    }
    memcpy(data,  m.data,height * width * (sizeof(double)));
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
        return *this;
    }
    memcpy(data, m.data, height * width * (sizeof(double)));
    return *this;
}

Matrix Matrix::operator+ (const Matrix &m){
    if ((m.width != width) or (m.height != height)){
        std::cout<<"Summation error\n";
        return Matrix(0,0);
    }

    Matrix result(m.height, m.width);

    for (int i = 0; i < result.height * result.width; ++i) {
        result.data[i] = data[i] + m.data[i];
    }
    return result;
}


Matrix Matrix::operator* (const Matrix &m){
    if (m.height != width){
        std::cout<<"Multiplication error\n";
        return Matrix(0,0);
    }
    Matrix result(m.height, m.width);

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < m.width; ++j) {
            double Temp = 0.0;
            for (int k = 0; k < m.height; ++k) {
                Temp += data[ i * width + k] * m.data[m.width * k + j];
            }
            result.data[i * width + j] = Temp;
        }
    }

    return result;
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

