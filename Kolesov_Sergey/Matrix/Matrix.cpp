//
// Created by Master on 05.12.2021.
//

#include "Matrix.h"
#include <iostream>
#include <cstring>

void Matrix::rid_memory(){
    delete[] this->ptr_d;
    this->rows = 0;
    this->cols = 0;
}

Matrix::Matrix(unsigned int rows, unsigned int cols, double val){
    this->ptr_d = new double[rows*cols];
    this->rows = rows;
    this->cols = cols;

    for (int i=0; i<(rows*cols); i++)
        this->ptr_d[i] = val;
}

Matrix::Matrix(unsigned int rows, unsigned int cols, double* data){
    this->ptr_d = new double[rows*cols];
    memcpy(this->ptr_d, data, rows*cols*8);
    this->rows = rows;
    this->cols = cols;
}

Matrix::Matrix(Matrix& clone){
    this->ptr_d = new double[clone.rows*clone.cols];
    memcpy(this->ptr_d, clone.ptr_d, clone.rows*clone.cols*8);
    this->rows = clone.rows;
    this->cols = clone.cols;
}

Matrix::Matrix(char Type, unsigned int n){
    switch (Type) {
        case 'E':
            this->ptr_d = new double[n*n];
            this->rows = n;
            this->cols = n;
            memset(this->ptr_d, 0, n*n*8);
            for (int i=0; i<n; i++)
                this->ptr_d[i*this->cols+i] = 1;
        case 'O':
            this->ptr_d = new double[n*n];
            this->rows = n;
            this->cols = n;
            memset(this->ptr_d, 0, n*n*8);
        default:
            this->ptr_d = nullptr;
            this->rows = 0;
            this->cols = 0;

    }
}

Matrix& Matrix::operator= (const Matrix& clone){
    if (this == &clone)
        return *this;

    rid_memory();
    this->ptr_d = new double[clone.rows*clone.cols];
    memcpy(this->ptr_d, clone.ptr_d, clone.rows*clone.cols*8);
    this->rows = clone.rows;
    this->cols = clone.cols;

    return *this;
}

Matrix::~Matrix(){
    rid_memory();
}

void Matrix::print(){
    for (int i = 0; i < this->rows; i++){
        for (int j = 0; j < this->cols; j++){
            std::cout << this->ptr_d[i * this->cols + j] << "  ";
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

void Matrix::transposition() {
    if (this->ptr_d != nullptr) {
        this->ptr_b = new double[this->rows * this->cols];
        memcpy(this->ptr_b, this->ptr_d, this->rows * this->cols * 8);

        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < (this->cols); j++)
                this->ptr_d[j * this->cols + i] = this->ptr_b[i * this->cols + j];
        }

        int temp = this->cols;
        this->cols = this->rows;
        this->rows = temp;
        delete[] this->ptr_b;
    }
}

void Matrix::reverse() {
    if ((this->rows == this->cols)&&(this->det() != 0)){
        Matrix M(3,3,this->ptr_d);
        double det = this->det();
        M.transposition();
        M.print();

        for (int i = 0; i < this->rows; i++){
            for (int j = 0; j < this->cols; j++) {
                this->ptr_d[i * this->cols + j] = M.minorij(i + 1, j + 1) / det;
            }
        }
    }
}

void Matrix::swap_rows(unsigned int row1, unsigned int row2){
    double temp = 0;
    for (int i = 0; i < this->cols; i++) {
        temp = this->ptr_d[(row1 - 1) * this->cols + i];
        this->ptr_d[(row1 - 1) * this->cols + i] = this->ptr_d[(row2 - 1) * this->cols + i];
        this->ptr_d[(row2 - 1) * this->cols + i] = temp;
    }
}

void Matrix::swap_cols(unsigned int col1, unsigned int col2){
    double temp = 0;
    for (int i = 0; i < this->rows; i++) {
        temp = this->ptr_d[i*this->cols + col1-1];
        this->ptr_d[i*this->cols + col1-1] = this->ptr_d[i*this->cols + col2-1];
        this->ptr_d[i*this->cols + col2-1] = temp;
    }
}

double Matrix::trace(){
    if (this->rows != this->cols)
        return 0;

    double tr = 0;
    for (int i = 0; i < this->rows; i++)
        tr += this->ptr_d[i * this->cols + i];

    return tr;
}

double Matrix::det(){
    if ((this->rows != this->cols)||(this->rows == 0))
        return 0;

    double det = 0;
    double temp_main = 1;
    double temp_side = 1;

    for (int i = 0; i < this->rows; i++) {
        temp_main = 1;
        temp_side = 1;
        for (int j = 0; j < this->rows; j++) {
            temp_main *= this->ptr_d[j * this->cols + (i+j)%this->cols];
            temp_side *= this->ptr_d[j * this->cols + (this->cols+i-j)%this->cols];
        }
        det += temp_main;
        det -= temp_side;
    }

    return det;
}

double Matrix::minorij(unsigned int row, unsigned int col){
    if ((this->rows != this->cols)||(this->rows < 2))
        return 0;

    if ((this->rows < row-1 )||(this->cols < col-1))
        return 0;

    double min = 0;
    double temp_main = 1;
    double temp_side = 1;
    int count_main = 0;
    int count_side = 0;

    for (int i = 0; i < this->cols; i++) {
        temp_main = 1;
        temp_side = 1;
        count_main = 0;
        count_side = 0;

        for (int j = 0; j < this->rows; j++) {
            if ((j != row - 1)&&((i + j) % this->cols != col - 1)) {
                temp_main *= this->ptr_d[j * this->cols + (i + j) % this->cols];
                count_main++;
            }
            if ((j != row - 1)&&((this->cols + i - j) % this->cols != col - 1)) {
                temp_side *= this->ptr_d[j * this->cols + (this->cols + i - j) % this->cols];
                count_side++;
            }
        }

        if (count_main == this->rows-1)
            min += temp_main;
        if (count_side == this->rows-1)
            min -= temp_side;
    }

    return min;
}

double Matrix::complement(unsigned int row, unsigned int col){
        double min = this->minorij(row, col);

        if ((row + col) % 2)
            min = -min;

        return min;
}

Matrix Matrix::operator+ (const Matrix& val){
    if ((this->rows != val.rows) || (this->cols != val.cols)){
        Matrix M;
        return M;
    }

    Matrix M(this->rows, this->cols);

    for (int i = 0; i < this->rows * this->cols; i++)
        M.ptr_d[i] = this->ptr_d[i] + val.ptr_d[i];

    return M;
}

Matrix Matrix::operator- (const Matrix& val){
    if ((this->rows != val.rows) || (this->cols != val.cols)){
        Matrix M;
        return M;
    }

    Matrix M(this->rows, this->cols);

    for (int i = 0; i < this->rows * this->cols; i++)
        M.ptr_d[i] = this->ptr_d[i] - val.ptr_d[i];

    return M;
}

Matrix Matrix::operator* (double val){
    if (this->ptr_d == nullptr){
        Matrix M;
        return M;
    }

    Matrix M(this->rows, this->cols);

    for (int i = 0; i < this->rows * this->cols; i++)
        M.ptr_d[i] = this->ptr_d[i] * val;

    return M;
}

Matrix Matrix::operator* (const Matrix& val){
    if (this->cols != val.rows){
        Matrix M;
        return M;
    }

    Matrix M(this->rows, val.cols);

    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < val.cols; j++) {
            for (int k = 0; k < this->cols; k++) {
                M.ptr_d[i * val.cols + j] += (this->ptr_d[this->cols * i + k] * val.ptr_d[k * val.cols + j]);
            }
        }
    }

    return M;
}

double Matrix::get(unsigned int row, unsigned int col) {
    if ((row > this->rows)||(col > this->cols))
        return 0;

    return this->ptr_d[(row-1)* this->cols + col-1];
}

void Matrix::set(unsigned int row, unsigned int col, double val) {
    if ((row <= this->rows) && (col <= this->cols))
        this->ptr_d[(row - 1) * this->cols + col - 1] = val;
}