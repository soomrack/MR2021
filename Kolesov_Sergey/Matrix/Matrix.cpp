//
// Created by Master on 05.12.2021.
//

#include "Matrix.h"
#include <iostream>
#include <cstring>

void Matrix::free_memory(){
    delete[] ptr_d;
    rows = 0;
    cols = 0;
}

Matrix::Matrix(unsigned int rows, unsigned int cols, double val){
    ptr_d = new double[rows*cols];
    this->rows = rows;
    this->cols = cols;

    for (int i=0; i<(rows*cols); i++)
        ptr_d[i] = val;
}

Matrix::Matrix(unsigned int rows, unsigned int cols, double* data){
    ptr_d = new double[rows*cols];
    memcpy(ptr_d, data, rows*cols*sizeof(double));
    this->rows = rows;
    this->cols = cols;
}

Matrix::Matrix(Matrix& clone){
    ptr_d = new double[clone.rows*clone.cols];
    memcpy(ptr_d, clone.ptr_d, clone.rows*clone.cols*sizeof(double));
    rows = clone.rows;
    cols = clone.cols;
}

Matrix::Matrix(Matrix&& clone) noexcept{
    ptr_d = clone.ptr_d;
    rows = clone.rows;
    cols = clone.cols;
    clone.ptr_d = nullptr;
    clone.rows = 0;
    clone.cols = 0;
}

Matrix::Matrix(char Type, unsigned int n){
    switch (Type) {
        case 'E':
            ptr_d = new double[n*n];
            rows = n;
            cols = n;
            memset(ptr_d, 0, n*n*sizeof(double));
            for (int i=0; i<n; i++)
                ptr_d[i*cols + i] = 1;
        case 'O':
            ptr_d = new double[n*n];
            rows = n;
            cols = n;
            memset(this->ptr_d, 0, n*n*sizeof(double));
        default:
            ptr_d = nullptr;
            rows = 0;
            cols = 0;

    }
}

Matrix& Matrix::operator= (const Matrix& clone){
    if (this == &clone)
        return *this;

    free_memory();
    ptr_d = new double[clone.rows*clone.cols];
    memcpy(ptr_d, clone.ptr_d, clone.rows*clone.cols*sizeof(double));
    rows = clone.rows;
    cols = clone.cols;

    return *this;
}

double Matrix::operator() (unsigned int row, unsigned int col)
{
    if (row > rows || col > cols)
        return 0.0;
    return ptr_d[cols*row + col];
}

Matrix::~Matrix(){
    free_memory();
}

void Matrix::print(){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            std::cout << ptr_d[i * cols + j] << "  ";
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

void Matrix::transposition() {
    if (ptr_d != nullptr) {
        ptr_b = new double[rows * cols];
        memcpy(ptr_b, ptr_d, rows * cols * sizeof(double));

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < (cols); j++)
                ptr_d[j * cols + i] = ptr_b[i * cols + j];
        }

        int temp = cols;
        cols = rows;
        rows = temp;
        delete[] ptr_b;
    }
}

void Matrix::reverse() {
    if ((rows == cols)&&(det() != 0)){
        Matrix M(3,3,ptr_d);
        double det = this->det();
        M.transposition();
        M.print();

        for (int i = 0; i < rows; i++){
            for (int j = 0; j < cols; j++) {
                ptr_d[i * cols + j] = M.minorij(i + 1, j + 1) / det;
            }
        }
    }
}

void Matrix::normalization() {
    double sum = 0;
    for (int i = 0; i < rows * cols; i++)
        sum += ptr_d[i];
    for (int i = 0; i < rows * cols; i++)
        ptr_d[i] /= sum;
}

void Matrix::swap_rows(unsigned int row_first, unsigned int row_second){
    double temp = 0;
    for (int i = 0; i < cols; i++) {
        temp = ptr_d[(row_first - 1) * cols + i];
        ptr_d[(row_first - 1) * cols + i] = ptr_d[(row_second - 1) * cols + i];
        ptr_d[(row_second - 1) * cols + i] = temp;
    }
}

void Matrix::swap_cols(unsigned int col_first, unsigned int col_second){
    double temp = 0;
    for (int i = 0; i < rows; i++) {
        temp = ptr_d[i*cols + col_first-1];
        ptr_d[i*cols + col_first-1] = ptr_d[i*cols + col_second-1];
        ptr_d[i*cols + col_second-1] = temp;
    }
}

double Matrix::trace(){
    if (rows != cols)
        return 0.0;

    double tr = 0;
    for (int i = 0; i < rows; i++)
        tr += ptr_d[i * cols + i];

    return tr;
}

double Matrix::det(){
    if ((rows != cols)||(rows == 0))
        return 0.0;

    double det = 0;
    double temp_main = 1;
    double temp_side = 1;

    for (int i = 0; i < rows; i++) {
        temp_main = 1;
        temp_side = 1;
        for (int j = 0; j < rows; j++) {
            temp_main *= ptr_d[j * cols + (i+j)%cols];
            temp_side *= ptr_d[j * cols + (cols+i-j)%cols];
        }
        det += temp_main;
        det -= temp_side;
    }

    return det;
}

double Matrix::minorij(unsigned int row, unsigned int col){
    if ((rows != cols)||(rows < 2))
        return 0.0;

    if ((rows < row-1 )||(cols < col-1))
        return 0.0;

    double min = 0;
    double temp_main = 1;
    double temp_side = 1;
    int count_main = 0;
    int count_side = 0;

    for (int i = 0; i < cols; i++) {
        temp_main = 1;
        temp_side = 1;
        count_main = 0;
        count_side = 0;

        for (int j = 0; j < rows; j++) {
            if ((j != row - 1)&&((i + j) % cols != col - 1)) {
                temp_main *= ptr_d[j * cols + (i + j) % cols];
                count_main++;
            }
            if ((j != row - 1)&&((cols + i - j) % cols != col - 1)) {
                temp_side *= ptr_d[j * cols + (cols + i - j) % cols];
                count_side++;
            }
        }

        if (count_main == rows-1)
            min += temp_main;
        if (count_side == rows-1)
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
    if ((rows != val.rows) || (cols != val.cols)){
        Matrix M;
        return M;
    }

    Matrix M(rows, cols, 0.0);

    for (int i = 0; i < rows * cols; i++)
        M.ptr_d[i] = ptr_d[i] + val.ptr_d[i];

    return M;
}

Matrix Matrix::operator- (const Matrix& val){
    if ((rows != val.rows) || (cols != val.cols)){
        Matrix M;
        return M;
    }

    Matrix M(rows, cols);

    for (int i = 0; i < rows * cols; i++)
        M.ptr_d[i] = ptr_d[i] - val.ptr_d[i];

    return M;
}

Matrix Matrix::operator* (double val){
    if (ptr_d == nullptr){
        Matrix M;
        return M;
    }

    Matrix M(rows, cols);

    for (int i = 0; i < rows * cols; i++)
        M.ptr_d[i] = ptr_d[i] * val;

    return M;
}

Matrix Matrix::operator* (const Matrix& val){
    if (cols != val.rows){
        Matrix M;
        return M;
    }

    Matrix M(rows, val.cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < val.cols; j++) {
            for (int k = 0; k < cols; k++) {
                M.ptr_d[i * val.cols + j] += (ptr_d[cols * i + k] * val.ptr_d[k * val.cols + j]);
            }
        }
    }

    return M;
}

double Matrix::get(unsigned int row, unsigned int col) {
    if ((row > rows)||(col > cols))
        return 0.0;

    return ptr_d[(row-1)* cols + col-1];
}

void Matrix::set(unsigned int row, unsigned int col, double val) {
    if ((row <= rows) && (col <= cols))
        ptr_d[(row - 1) * cols + col - 1] = val;
}