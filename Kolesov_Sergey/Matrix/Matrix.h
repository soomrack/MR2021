//
// Created by Master on 05.12.2021.
//

#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

class Matrix {
private:
    double * ptr_d;//data
    double * ptr_b;//bufer
    unsigned int rows;
    unsigned int cols;

public:
    Matrix(unsigned int rows = 0, unsigned int cols = 0, double val = 0);
    Matrix(unsigned int rows, unsigned int cols, double* data);
    Matrix(Matrix& clone);
    Matrix(char Type, unsigned int n);
    Matrix& operator= (const Matrix& val);
    ~Matrix();

public:
    void set(unsigned int row, unsigned int col, double val);
    double get(unsigned int row, unsigned int col);
    double trace();
    double det();
    double minorij(unsigned int row, unsigned int col);
    double complement(unsigned int row, unsigned int col);

public:
    Matrix operator+ (const Matrix& val);
    Matrix operator- (const Matrix& val);
    Matrix operator* (double val);
    Matrix operator* (const Matrix& val);
    double operator() (unsigned int row, unsigned int col);// instead [i][j] use (i, j)

public:
    void print();
    void transposition();
    void reverse();
    void normalization();
    void swap_rows(unsigned int row1, unsigned int row2);
    void swap_cols(unsigned int col1, unsigned int col2);
    void rid_memory();
};

#endif //MATRIX_MATRIX_H
