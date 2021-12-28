#include <iostream>
#include <ctime>
#include "Matrix_lib.h."

Matrix::Matrix(unsigned int rows ,unsigned int columns, int type){
    rows = rows;
    columns = columns;

    data = new int[rows * columns];

    switch (type){
        case ZERO_MATRIX:
            creat_zero_matrix();
            break;
        case IDENITY_MATRIX:
            creat_identity_matrix();
            break;
        default:
            creat_random_matrix();
            break;
    }
}

void Matrix::creat_zero_matrix() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            data[j + rows * i] = 0;
        }
    }
}

void Matrix::creat_identity_matrix() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (rows != columns)
                std::cout << "Matrix must be square" << std::endl;
            if (i == j) data[j + rows * i] = 1;
            else data[j + rows * i] = 0;
        }
    }
}

void Matrix::creat_random_matrix() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            data[j + rows * i] = rand() % 10;
        }
    }
}


Matrix::~Matrix() {
    delete [] data;
}

Matrix::Matrix(const Matrix &other) {
    rows = other.rows;
    columns = other.columns;
    data = new int [rows*columns];
    memcpy(data,other.data,sizeof(int)*rows * columns);
}

Matrix::Matrix(Matrix &&other) noexcept {
    rows = other.rows;
    columns = other.columns;
    data = other.data;
    other.data = nullptr;
}

Matrix & Matrix::operator = (const Matrix &other){
    rows = other.rows;
    columns = other.columns;
    delete [] data;
    data = new int [rows*columns];
    memcpy(data,other.data,sizeof(int)*rows * columns);

    return *this;
}

Matrix & Matrix::operator = (Matrix &&other) noexcept {
    rows = other.rows;
    columns = other.columns;
    data = other.data;
    other.data = nullptr;
    return *this;
}

Matrix Matrix::operator- (const Matrix &other){
    if (rows != other.rows || columns != other.columns)
        std::cout << "Matrix aren't equal" << std::endl;

    Matrix temp(rows, columns);
    temp.data = new int [rows*columns];
    for (int i = 0; i < rows*columns; ++i){
        temp.data[i] = data[i] - other.data[i];
    }
    return temp;
}

Matrix Matrix::operator+ (const Matrix &other){
    if (rows != other.rows || columns != other.columns)
        std::cout << "Matrix aren't same" << std::endl;

    Matrix temp(rows, columns, ZERO_MATRIX);
    temp.data = new int [rows*columns];
    for (int i = 0; i < rows*columns; ++i){
        temp.data[i] = data[i] + other.data[i];
    }
    return temp;
}

Matrix Matrix::operator * (const Matrix &other){
    if (columns != other.rows){
        std::cout << "Error, wrong size of matrix" << std::endl;
        exit(1);
    }
    Matrix temp(rows, columns, ZERO_MATRIX);
    temp.data = new int [rows*other.columns];
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            temp.data[j + rows * i] = 0;
            for (int k = 0; k < other.rows; ++k) {
                temp.data[j + rows * i] += data[k + rows * i] * other.data[j + rows * k];
            }
        }
    }
    return temp;
}

int Matrix::trace() {
    int matrix_trace = 0;
    if (rows != columns)
        std::cout << "Matrix isn't square" << std::endl;

    for (int i = 0; i < rows; ++i) {
        if(INT_MAX - data[i + rows * i] > matrix_trace) //// overflow check
            matrix_trace += data[i + rows * i];
        else
            std::cout << "Too great a value " << std::endl;

    }
    return matrix_trace;
}

void Matrix::print() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            std::cout << data[j + rows * i] << "\t";
        }
        std::cout << std::endl;
    }
}


double Matrix::determinate(){
    double det = 1;
    int tmp;
    if(columns != columns)
        std::cout << "Enter a square matrix " << std::endl;

    for (int k = 0; k < rows - 1; k++) {
        for (int i = k + 1; i < rows; i++) {
            tmp = -data[i + rows * k] / data[k + rows * k];
            for (int j = 0; j < rows; j++) {
                data[j + rows * i] += data[k + rows * i] * tmp;
            }
        }
    }

    for (int i = 0; i < rows; i++) {
        det *= data[i + rows * i];
    }
    return det;
}