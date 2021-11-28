#include <iostream>
#include <cmath>

#include "library.h"


Matrix::Matrix(){
    height = 1;
    width = 1;
    data = (double *)malloc(height * width * sizeof(double));
    data[0]=0;
}

Matrix::Matrix(int height, int width) {
    this->height = height;
    this -> width = width;
    data = (double *)malloc(height * width * sizeof(double));
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if(i == j) {data[i*width+j] = 1;}
            else{data[i*width+j] = 0;}
        }
    }
}

Matrix::Matrix(int height, int width, double *data) {
    this->height = height;
    this -> width = width;
    this->data = (double *)malloc(height * width * sizeof(double));
    for (int i = 0; i < width*height; ++i) {
        this->data[i]=data[i];
    }
}

Matrix::Matrix(Matrix &&m) {
    height=m.height;
    width=m.width;
    free(data);
    data = m.data;
    m.data = nullptr;
}

//Конструктор копирования
Matrix::Matrix(const Matrix &m) {
    height=m.height;
    width=m.width;
    data = (double *)malloc(height * width * sizeof(double));
    memcpy(data,  m.data,height * width * (sizeof(double)));
}

void Matrix::Print() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            std::cout<< data[i*width+j]<<' ';
        }
        std::cout << '\n';
    }
}

double Matrix::Trace() {
    if (this->width != this->height){
        return std::nanf("");
    }
    double Temp=1;
    for (int i = 0; i < height; ++i) {
        Temp*= data[i*width+i];
    }
    return Temp;
}

