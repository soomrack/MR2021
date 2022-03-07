#include "library.h"
#include <iostream>

Matrix::Matrix(){
    height = 0;
    width = 0;
    data = nullptr;
}


Matrix::Matrix (unsigned int height, unsigned int width, double value) {
    this->height = height;
    this->width = width;
    data = (double *) malloc(height * height * sizeof(double));
    if (data == nullptr){
        this->height = 0;
        this->width = 0;
        return;
    }
    for (int i = 0; i < height*width; i++) {
        data[i] = value;
    }

}


Matrix::Matrix (unsigned int height, unsigned int width, double *data) {
    this->height = height;
    this->width = width;
    this->data = (double *) malloc(height * width * sizeof(double));
    if (data == nullptr){
        this->height = 0;
        this->width = 0;
        return;
    }
    for (int i = 0; i < height*width; i++) {
        memcpy(this->data,data, height*width*sizeof(double));
    };
}


Matrix::Matrix(const Matrix &m){
    height=m.height;
    width=m.width;
    data=(double *)malloc(height*width*sizeof(double));
    if (data == nullptr){
        height = 0;
        width = 0;
        return;
    }
    memcpy(data, m.data, height*width*sizeof(double));
}

Matrix::Matrix(Matrix &&m)    noexcept {
    height = m.height;
    width = m.width;
    free(data);
    data = m.data;
    m.data = nullptr;
}

Matrix & Matrix::operator= (const Matrix &m) {
    if (&m == this)
        return *this;
    width = m.width;
    height = m.height;
    free(data);
    data = (double *) malloc(height * width * sizeof(double));
    if (data == nullptr){
        height = 0;
        width = 0;
        return * this;
    }
    memcpy(data, m.data, height * width * (sizeof(double)));
    return * this;
}

Matrix Matrix::operator + (const Matrix &m) {
    Matrix result(height,width);
    if ((height !=m.height)||(width!=m.width)) {
        std::cout << "Matrix can not be summered" << std::endl;
        result.height=0;
        result.width=0;
        return result;
    }
    for (int i = 0; i <height*width; i++) {
        result.data[i] = m.data[i]+data[i];
    };
    return result;
}

Matrix Matrix::operator * (const Matrix &m) {
    Matrix result(height,width);
    if (width !=m.height) {
        std::cout << "Matrix can not be multiplied" << std::endl;
        result.height=0;
        result.width=0;
        return result;
    }
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < m.width; ++j) {
            double temp = 0.0;
            for (int k = 0; k < m.height; ++k) {
                temp += data[ i * width + k] * m.data[m.width * k + j];
            }
            result.data[i * width + j] = temp;
        }
    }
    return result;
}


void Matrix::print() {
    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= width; j++)
            std::cout << data[j + ((i - 1) * width)-1] << ' ';
        std::cout << std::endl;
    };
}

void Matrix::identity_matrix() {
    if (width != height) {
        std::cout << "Matrix can't be made" << std::endl;
        return;
    };
    zero_matrix();
    for (int i = 0; i < height*width; i=i+height+1) {
        data[i] = 1.0;
    };
}

void Matrix::zero_matrix(){
    for (int i = 0; i < height*width; i++) {
        data[i] = 0.0;
    };
}

void Matrix::trace() {
    if (width != height) {
        std::cout << "Trace can't be found" << std::endl;
        return;
    };
    double trace;
    trace = 0.0;
    for (int i = 0; i < height * width; i = i + height + 1) {
        trace = trace + data[i];
    }
    std::cout << trace << std::endl;

}

void Matrix::determinant(){
    if(height!=width) {
        std::cout << "Matrix is not square" <<std::endl ;
        return;
    }
    switch (height){
        case 1: std::cout << data[0]<<std::endl;
            break;
        case 2:   std::cout << data[3]*data[2]- data[1]*data[2] <<std::endl;
            break;
        case 3:   std::cout << data[0]*data[4]*data[8]+ data[1]*data[5]*data[6]+data[2]*data[3]*data[7]-(data[2]*data[4]*data[6]+ data[0]*data[7]*data[5]+data[1]*data[3]*data[8]) <<std::endl;
            break;
        default:   std::cout << "This program can't calculate determinant for matrix with height>3" <<std::endl;
            break;
        };


}

Matrix::~Matrix() {
    free(data);
}