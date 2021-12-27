#include "library.h"
#include <iostream>


Matrix::Matrix (unsigned int height, unsigned int width, double value) {
    this->height = height;
    this->width = width;
    data = (double *) malloc(height * height * sizeof(double));
    if (data == nullptr){
        this->height = 0;
        this->width = 0;
    } else for (int i = 0; i < height*width; i++) {
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
    } else for (int i = 0; i < height*width; i++) {
            memcpy(this->data,data, height*width*sizeof(double));
        };
}


Matrix::Matrix(const Matrix &m){
    height=m.height;
    width=m.width;
    data=(double *)malloc(height*width*sizeof(double));
    memcpy(data, m.data, height*width*sizeof(double));
}

Matrix::Matrix(Matrix &&m)   {
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
    memcpy(data, m.data, height * width * (sizeof(double)));
    return *this;
}

Matrix Matrix::operator + (const Matrix &m) {
    Matrix result(height,width);
    if ((height !=m.height)||(width!=m.width)) {
        std::cout << "Matrix can not be summered" << std::endl;
        height=0;
        width=0;
    }
    result.print();
    for (int i = 0; i <height*width; i++) {
        result.data[i] = m.data[i]+data[i];
    };
    return result;
}



void Matrix::print() {
    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= width; j++)
            std::cout << data[j + ((i - 1) * width)-1] << ' ';
        std::cout << std::endl;
    };
}

void Matrix::Matrix_1() {
    if (width == height) {
        data = (double *) malloc(height * height * sizeof(double));
        for (int i = 1; i <= height; i++) {
            for (int j = 1; j <= height; j++) {
                if (i == j)
                    data[j + (i - 1) * height - 1] = 1;
                else data[j + (i - 1) * height - 1] = 0;
            };
        };
    }
    else std::cout << "Matrix can't be made"<<std::endl;
}

void Matrix::trace() {
    int trace;
    trace=0;
    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= height; j++) {
            if (i == j)
                trace=trace+data[j + (i - 1) * width-1];
        };
    };
    std::cout <<trace<<std::endl;
}

void Matrix::determinant(){
    if(height==width) {
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
    else
        std::cout << "Matrix is not square" <<std::endl ;
}

Matrix::~Matrix() {
    free(data);
}