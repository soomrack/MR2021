#include <iostream>
#include "Matrix.h"

#pragma once

Matrix::Matrix(int height, int width) {
    this->height = height;
    this->width = width;
    data = (int *) malloc(height * width * sizeof(int));
}

Matrix::Matrix(const Matrix &other) {
    this->height = other.height;
    this->width = other.width;
    this->data = (int *) malloc(height * width * sizeof(int));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            this->data[width * i + j] = other.data[width * i + j];
        }
    }
}

Matrix::~Matrix() {
    free(data);
}

void Matrix::free(int *data) {
    if (height != 0 && width != 0 && data != NULL)
        delete[] data;
}

void Matrix::random_input(int height, int width) {
    for (int i = 0; i < height * width; i++)
        data[i] = rand() % 10;
}

void Matrix::out() {
    for (int i = 0; i < this->width * this->height; i++) {
        std::cout << data[i] << " ";
        if ((i + 1) % this->width == 0)
            std::cout << std::endl;
    }
}

int Matrix::size_height() {
    return height;
}

int Matrix::size_width() {
    return width;
}

/*
int Matrix::sum(Matrix A, Matrix B) {
    if ((A.size_height() != B.size_height()) && (A.size_width() != B.size_width())) {
        cout << "\n\nERROR\n\nMatrix A and B must be the same size";
        return 0;
    } else {
        cout << "\nFinal matrix:\n";
        for (int i = 0; i < A.size_height() * A.size_width(); i++)
            A.data[i] = A.data[i] + B.data[i];
        A.out();
    }
}

int Matrix::subtraction(Matrix A, Matrix B) {
    if ((A.size_height() != B.size_height()) && (A.size_width() != B.size_width())) {
        cout << "\n\nERROR\n\nMatrix A and B must be the same size";
        return 0;
    } else {
        cout << "\nFinal matrix:\n";
        for (int i = 0; i < A.size_width() * A.size_height(); i++)
            A.data[i] = A.data[i] - B.data[i];
        A.out();
    }
}

int Matrix::multiplication(Matrix A, Matrix B) {
    int sum = 0;
    if (A.size_width() != B.size_height()) {
        cout << "\n\nERROR\n\nMatrix A and B must be commutative (columns A = rows B)";
        return 0;
    }
    cout << "\nFinal matrix:\n";
    Matrix C(A.size_height(), B.size_width());
    for (int i = 0, j = 0; i < A.size_height() * B.size_width(); i++) {
        for (int k = 0; k < A.size_width(); k++)
            sum += A.data[k + j * A.size_width()] * B.data[i - j * B.size_width() + k * B.size_width()];
        C.data[i] = sum;
        sum = 0;
        if ((i + 1) % (A.size_width() + 1) == 0) j++;
        C.out();
    }
}
*/

Matrix Matrix::operator+(const Matrix &other) {
    if ((this->width != other.width) || (this->height != other.height)) {
        std::cout << "\n\nERROR\n\nMatrix A and B must be the same size";
        Matrix Error(0, 0);
        return Error;
    }
    Matrix Sum(this->height, this->width);
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            Sum.data[height * i + j] = this->data[height * i + j] + other.data[height * i + j];
        }
    }
    Sum.out();
    return Sum;
}

Matrix Matrix::operator-(const Matrix &other) {
    if ((this->width != other.width) || (this->height != other.height)) {
        std::cout << "\n\nERROR\n\nMatrix A and B must be the same size";
        Matrix Error(0, 0);
        return Error;
    }
    Matrix Sub(this->height, this->width);
    for (int i = 0; i < this->width; i++) {
        for (int j = 0; j < other.height; j++) {
            Sub.data[other.height * i + j] = this->data[other.height * i + j] - other.data[other.height * i + j];
        }
    }
    Sub.out();
    return Sub;
}

Matrix Matrix::operator*(const Matrix &other) {
    int sum = 0;
    if (this->width != other.height) {
        std::cout << "\nERROR\n\nMatrix A and B must be commutative (columns A = rows B)\n\n\n";
        Matrix Error(0, 0);
        return Error;
    }
    Matrix Mul(this->height, other.width);
    for (int i = 0, j = 0; i < this->height * other.width; i++) {
        for (int k = 0; k < this->width; k++)
            sum += this->data[k + j * this->width] * other.data[i - j * other.width + k * other.width];
        Mul.data[i] = sum;
        sum = 0;
        if ((i + 1) % (this->width + 1) == 0) j++;
    }
    Mul.out();
    return Mul;
}
