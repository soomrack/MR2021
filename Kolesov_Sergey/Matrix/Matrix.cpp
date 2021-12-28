//
// Created by Master on 05.12.2021.
//

#include "Matrix.h"
#include <iostream>
#include <cstring>

void Matrix::free_memory(){
    delete[] data;
    rows = 0;
    cols = 0;
}

Matrix::Matrix(unsigned int rows, unsigned int cols, double val){
    data = new double[rows*cols];
    this->rows = rows;
    this->cols = cols;

    for (int i=0; i<(rows*cols); i++)
        data[i] = val;
}

Matrix::Matrix(unsigned int rows, unsigned int cols, double* data){
    this->data = new double[rows*cols];
    memcpy(this->data, data, rows*cols*sizeof(double));
    this->rows = rows;
    this->cols = cols;
}

Matrix::Matrix(Matrix& clone){
    data = new double[clone.rows*clone.cols];
    memcpy(data, clone.data, clone.rows*clone.cols*sizeof(double));
    rows = clone.rows;
    cols = clone.cols;
}

Matrix::Matrix(Matrix&& clone) noexcept{
    data = clone.data;
    rows = clone.rows;
    cols = clone.cols;
    clone.data = nullptr;
    clone.rows = 0;
    clone.cols = 0;
}

Matrix::Matrix(MatrixType Type, unsigned int n){
    switch (Type) {
        case SINGLE:
            data = new double[n*n];
            rows = n;
            cols = n;
            memset(data, 0, n*n*sizeof(double));
            for (int i=0; i<n; i++)
                data[i*cols + i] = 1;
        case ZEROS:
            data = new double[n*n];
            rows = n;
            cols = n;
            memset(data, 0, n*n*sizeof(double));
        default:
            data = nullptr;
            rows = 0;
            cols = 0;
    }
}

Matrix& Matrix::operator= (const Matrix& clone){
    if (this == &clone)
        return *this;

    free_memory();
    data = new double[clone.rows*clone.cols];
    memcpy(data, clone.data, clone.rows*clone.cols*sizeof(double));
    rows = clone.rows;
    cols = clone.cols;

    return *this;
}

Matrix& Matrix::operator= (const Matrix&& clone) noexcept{
    data = clone.data;
    rows = clone.rows;
    cols = clone.cols;
    return *this;
}

double Matrix::operator() (unsigned int row, unsigned int col)
{
    if (row > rows || col > cols)
        return 0.0;
    return data[cols*row + col];
}

Matrix::~Matrix(){
    free_memory();
}

void Matrix::print(){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            std::cout << data[i * cols + j] << "  ";
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

void Matrix::transposition() {
    if (data != nullptr) {
        buf = new double[rows * cols];
        memcpy(buf, data, rows * cols * sizeof(double));

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < (cols); j++)
                data[j * cols + i] = buf[i * cols + j];
        }

        int temp = cols;
        cols = rows;
        rows = temp;
        delete[] buf;
    }
}

void Matrix::reverse() {
    if ((rows == cols)&&(det() != 0)){
        Matrix M(3,3,data);
        double det = this->det();
        M.transposition();
        M.print();

        for (int i = 0; i < rows; i++){
            for (int j = 0; j < cols; j++) {
                data[i * cols + j] = M.minorij(i, j) / det;
            }
        }
    }
}

void Matrix::normalization() {

    double sum = 0.0;
    for (int i = 0; i < rows * cols; i++)
        sum += data[i];
    for (int i = 0; i < rows * cols; i++)
        data[i] /= sum;
}

void Matrix::swap_rows(unsigned int row_first, unsigned int row_second){
    double temp = 0.0;
    for (int i = 0; i < cols; i++) {
        temp = data[row_first * cols + i];
        data[row_first * cols + i] = data[row_second * cols + i];
        data[row_second * cols + i] = temp;
    }
}

void Matrix::swap_cols(unsigned int col_first, unsigned int col_second){
    double temp = 0.0;
    for (int i = 0; i < rows; i++) {
        temp = data[i*cols + col_first];
        data[i*cols + col_first] = data[i*cols + col_second];
        data[i*cols + col_second] = temp;
    }
}

double Matrix::trace(){
    if (rows != cols)
        return 0.0;

    double tr = 0.0;
    for (int i = 0; i < rows; i++)
        tr += data[i * cols + i];

    return tr;
}

double Matrix::det(){
    if ((rows != cols)||(rows == 0))
        return 0.0;

    double det = 0.0;
    double temp_main = 1.0;
    double temp_side = 1.0;

    for (int i = 0; i < rows; i++) {
        temp_main = 1;
        temp_side = 1;
        for (int j = 0; j < rows; j++) {
            temp_main *= data[j * cols + (i+j)%cols];
            temp_side *= data[j * cols + (cols+i-j)%cols];
        }
        det += temp_main;
        det -= temp_side;
    }

    return det;
}

double Matrix::minorij(unsigned int row, unsigned int col){
    if ((rows != cols)||(rows < 2))
        return 0.0;

    if ((rows <= row )||(cols <= col))
        return 0.0;

    double min = 0.0;
    double temp_main = 1.0;
    double temp_side = 1.0;
    int count_main = 0;
    int count_side = 0;

    for (int i = 0; i < cols; i++) {
        temp_main = 1.0;
        temp_side = 1.0;
        count_main = 0;
        count_side = 0;

        for (int j = 0; j < rows; j++) {
            if ((j != row)&&((i + j) % cols != col)) {
                temp_main *= data[j * cols + (i + j) % cols];
                count_main++;
            }
            if ((j != row)&&((cols + i - j) % cols != col)) {
                temp_side *= data[j * cols + (cols + i - j) % cols];
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
        M.data[i] = data[i] + val.data[i];

    return M;
}

Matrix Matrix::operator- (const Matrix& val){
    if ((rows != val.rows) || (cols != val.cols)){
        Matrix M;
        return M;
    }

    Matrix M(rows, cols);

    for (int i = 0; i < rows * cols; i++)
        M.data[i] =data[i] - val.data[i];

    return M;
}

Matrix Matrix::operator* (double val){
    if (data == nullptr){
        Matrix M;
        return M;
    }

    Matrix M(rows, cols);

    for (int i = 0; i < rows * cols; i++)
        M.data[i] = data[i] * val;

    return M;
}

Matrix Matrix::operator* (const Matrix& val){
    if (cols != val.rows){
        Matrix M;
        return M;
    }

    Matrix M(rows, val.cols, 0.0);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < val.cols; j++) {
            for (int k = 0; k < cols; k++) {
                M.data[i * val.cols + j] += (data[cols * i + k] * val.data[k * val.cols + j]);
            }
        }
    }

    return M;
}

double Matrix::get(unsigned int row, unsigned int col) {
    if ((row >= rows)||(col >= cols))
        return 0.0;

    return data[row * cols + col];
}

void Matrix::set(unsigned int row, unsigned int col, double val) {
    if ((row <= rows) && (col <= cols))
        data[row * cols + col] = val;
}