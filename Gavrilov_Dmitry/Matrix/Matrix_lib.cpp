#include <iostream>
#include <ctime>
#include "Matrix_lib.h."

Matrix::Matrix(unsigned int rows,unsigned int columns,unsigned int type){
    this->rows = rows;
    this->columns = columns;
    srand(time(NULL));

    data = new int[rows * columns];

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            switch (type){
                case 0:
                    data[j + rows * i] = 0;
                    break;
                case 1:
                    if ( rows != columns){
                        std::cout << "Matrix must be square" << std::endl;
                    }
                    if (i == j)  data[j + rows * i] = 1;
                    else data[j + rows * i] = 0;
                    break;
                default:
                    data[j + rows * i] = rand() %10;
                    break;

            }
        }
    }
}

Matrix::~Matrix() {
    delete [] data;
}

Matrix::Matrix(const Matrix &other) {
    this->rows = other.rows;
    this->columns = other.columns;
    this->data = new int [rows*columns];
    memcpy(data,other.data,sizeof(int)*rows * columns);
}

Matrix::Matrix(Matrix &&other) noexcept {
    this->rows = other.rows;
    this->columns = other.columns;
    this->data = other.data;
    other.data = nullptr;
    other.rows = 0;
    other.columns = 0;
}

Matrix & Matrix::operator = (const Matrix &other){
    this->rows = other.rows;
    this->columns = other.columns;
    this->data = new int [rows*columns];
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            this->data[j + rows * i] = other.data[j + rows * i];
        }
    }
    return *this;
}

Matrix & Matrix::operator = (Matrix &&other) noexcept {
    this->rows = other.rows;
    this->columns = other.columns;
    delete [] this->data;
    this->data = new int [rows*columns];

    memcpy(data,other.data,sizeof(int)*rows * columns);

    other.data = nullptr;
    other.rows = 0;
    other.columns = 0;
    return *this;
}

Matrix Matrix::operator- (const Matrix &other){
    if (this->rows != other.rows || this->columns != other.columns){
        std::cout << "Matrix aren't equal" << std::endl;
        exit(1);
    }
    Matrix temp(this->rows, this->columns, 9);
    temp.data = new int [rows*columns];
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            temp.data[j + rows * i] = this->data[j + rows * i] - other.data[j + rows * i];
        }
    }
    return temp;
}

Matrix Matrix::operator+ (const Matrix &other){
    if (this->rows != other.rows || this->columns != other.columns){
        std::cout << "Matrix aren't same" << std::endl;
        exit(1);
    }
    Matrix temp(this->rows, this->columns, 0);
    temp.data = new int [this->rows*this->columns];
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            temp.data[j + rows * i] = this->data[j + rows * i] + other.data[j + rows * i];
        }
    }
    return temp;
}

Matrix Matrix::operator * (const Matrix &other){
    if (this->columns != other.rows){
        std::cout << "Error, wrong size of matrix" << std::endl;
        exit(1);
    }
    Matrix temp(this->rows, this->columns, 3);
    temp.data = new int [this->rows*other.columns];
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            temp.data[j + rows * i] = 0;
            for (int k = 0; k < other.rows; ++k) {
                temp.data[j + rows * i] += this->data[k + rows * i] * other.data[j + rows * k];
            }
        }
    }
    return temp;
}

int Matrix::trace() {
    int matrix_trace = 0;
    if (this->rows != this->columns) {
        std::cout << "Matrix isn't square" << std::endl;
        exit(1);
    }
    for (int i = 0; i < this->rows; ++i) {
        matrix_trace += data[i + rows * i];
    }
    return matrix_trace;
}

void Matrix::print() {
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->columns; ++j) {
            std::cout << this->data[j + rows * i] << "\t";
        }
        std::cout << std::endl;
    }
}


double Matrix::determinate(){
    double det = 1;
    int tmp;
    if(this->columns != this->columns)
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