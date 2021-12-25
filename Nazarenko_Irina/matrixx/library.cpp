#include "library.h"
#include <iostream>


Matrix::Matrix (int height, int width) {
    this->height = height;
    this->width = width;
    data = (double *) malloc(height * height * sizeof(double));
    for (int i = 0; i < height*width; i++) {
        data[i] = 0;
    }
}

Matrix::Matrix (int height, int width, double *data) {
    this->height = height;
    this->width = width;
    this->data = (double *) malloc(height * width * sizeof(double));
    for (int i = 0; i < height*width; i++) {
        this->data[i]=data[i];
    }
}

Matrix::Matrix (int height) {
    this->height = height;
    width=height;
    data = (double *) malloc(height * height * sizeof(double));
    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= height; j++) {
            if (i == j)
                data[j + (i - 1) * height - 1] = 1;
            else data[j + (i - 1) * height - 1] = 0;
        }
    }
}

Matrix::Matrix(const Matrix &m){
    height=m.height;
    width=m.width;
    data=(double *)malloc(height*width*sizeof(double));
    memcpy(data, m.data, height*width*sizeof(double));
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

Matrix & Matrix::operator + (const Matrix &m) {
    if (this->width !=m.height)
        std::cout << "Matrix can not be multiplied" << std::endl;
    Matrix Plus(this->height,this->width);
    for (int i = 1; i <=this->height; i++) {
        for (int j = 1; j <= this->width; j++) {
            Plus.data[j + (i - 1) * m.width - 1] = m.data[j + (i - 1) * m.width - 1]+this->data[j + (i - 1) * m.width - 1];
        }
    }
    Plus.print();
    return Plus;
}

void Matrix::print() {
    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= width; j++)
            std::cout << data[j + ((i - 1) * width)-1] << ' ';
        std::cout << std::endl;
    }
}

void Matrix::trace() {
    int trace;
    trace=1;
    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= height; j++) {
            if (i == j)
                trace=trace*data[j + (i - 1) * width-1];
        }
    }
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
            case 4:   std::cout << "This program can't calculate determinant for matrix with height>3" <<std::endl;
                break;
        }

    }
    else
        std::cout << "Matrix is not square" <<std::endl ;
}

Matrix::~Matrix() {
    free(data);
}
