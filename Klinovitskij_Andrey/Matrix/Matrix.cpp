#include <iostream>
#include "Matrix.h"
#include <cstring>
#include <stdlib.h>

#define ANSI_COLOR_RESET   "\x1b[0m"

#define ANSI_COLOR_RED   "\x1b[0;91;40m"
#define ANSI_COLOR_ORANGE "\x1b[0;93;40m"
#define ANSI_COLOR_GREEN "\x1b[0;92;40m"

#define ERROR_TYPE 1
#define WARNING_TYPE 1

#define ALLOCATE_ERROR 1
#define SUM_ERROR 2
#define SUB_ERROR 3
#define MUL_ERROR 4

#pragma once

void Errors(int type, int place) {
    if (type == ERROR_TYPE)
        std::cout << "\n\n" << ANSI_COLOR_RED << "ERROR" << ANSI_COLOR_RESET << "\n";
    else
        std::cout << "\n\n" << ANSI_COLOR_ORANGE << "WARNING" << ANSI_COLOR_RESET << "\n";
    switch (place) {
        case 1:
            std::cout << "Can't allocate memory\n";
            break;
        case 2:
            std::cout << "in " << ANSI_COLOR_GREEN << "'+'"
                      << ANSI_COLOR_RESET << ". Matrix A and B must be the same size\n\n\n";
            break;
        case 3:
            std::cout << "in " << ANSI_COLOR_GREEN << "'+'"
                      << ANSI_COLOR_RESET << ". Matrix A and B must be the same size\n\n\n";
            break;
        case 4:
            std::cout << "in " << ANSI_COLOR_GREEN << "'+'"
                      << ANSI_COLOR_RESET << ". Must be A col = B row\n\n\n";
            break;
    }

}

Matrix::Matrix(int height, int width) {
    this->height = height;
    this->width = width;
    if (!(data = (int *) malloc(height * width * sizeof(int)))) {
        Errors(ERROR_TYPE, ALLOCATE_ERROR);
        this->data = 0;
        this->height = 0;
        this->width = 0;
    }
}

Matrix::Matrix(const Matrix &other) {
    this->height = other.height;
    this->width = other.width;
    this->data = (int *) malloc(height * width * sizeof(int));
    std::memcpy(this->data, other.data, width * height * sizeof(int));
}


Matrix::~Matrix() {
    free(data);
}

void Matrix::free(int *data) {
    if (height != 0 && width != 0 && data != nullptr)
        delete[] data;
}

void Matrix::set_random(int height, int width) {
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
        Errors(ERROR_TYPE, SUM_ERROR);
        Matrix Error(0, 0);
        return Error;
    }
    Matrix sum(this->height, this->width);
    for (int counter = 0; counter < this->width * other.height; counter++)
        sum.data[counter] = this->data[counter] + other.data[counter];
    sum.out();
    return sum;
}

Matrix Matrix::operator-(const Matrix &other) {
    if ((this->width != other.width) || (this->height != other.height)) {
        Errors(ERROR_TYPE, SUB_ERROR);
        Matrix Error(0, 0);
        return Error;
    }
    Matrix sub(this->height, this->width);
    for (int counter = 0; counter < this->width * other.height; counter++)
        sub.data[counter] = this->data[counter] - other.data[counter];
    sub.out();
    return sub;
}

Matrix Matrix::operator*(const Matrix &other) {
    int sum = 0;
    if (this->width != other.height) {
        Errors(ERROR_TYPE, MUL_ERROR);
        Matrix Error(0, 0);
        return Error;
    }
    Matrix result(this->height, other.width);
    for (int i = 0, j = 0; i < this->height * other.width; i++) {
        for (int k = 0; k < this->width; k++)
            sum += this->data[k + j * this->width] * other.data[i - j * other.width + k * other.width];
        result.data[i] = sum;
        sum = 0;
        if ((i + 1) % (this->width + 1) == 0) j++;
    }
    result.out();
    return result;
}

Matrix::Matrix(Matrix &&other) noexcept {
    this->height = other.height;
    this->width = other.width;
    this->data = other.data;
    other.data = nullptr;
    other.height = 0;
    other.width = 0;
}


Matrix &Matrix::operator=(const Matrix &other) {
    this->width = other.width;
    this->height = other.height;
    if (!(data = (int *) malloc(height * width * sizeof(int)))) {
        Errors(ERROR_TYPE, ALLOCATE_ERROR);
        this->data = 0;
        this->height = 0;
        this->width = 0;
    }
    std::memcpy(this->data, other.data, width * height * sizeof(int));
}

Matrix &Matrix::operator=(Matrix &&other) noexcept {
    if (this == &other) {
        return *this;
    }
    free(data);
    width = other.width;
    height = other.height;

    if (!(data = (int *) malloc(height * width * sizeof(int)))) {
        Errors(ERROR_TYPE, ALLOCATE_ERROR);
        this->data = 0;
        this->height = 0;
        this->width = 0;
    }

    other.width = 0;
    other.height = 0;
    other.data = nullptr;
    return *this;
}

int Matrix::trace() {
    int trace = 0;
    for (int row = 0; row < width; row++)
        trace += data[row * width + row];
    std::cout << trace << std::endl;
}