//
// Created by Master on 05.12.2021.
//

#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

typedef enum{
    SINGLE,
    ZEROS
} MatrixType;

class Matrix {
private:
    double * data;//data
    double * buf;//bufer
    unsigned int rows;
    unsigned int cols;

public:
    Matrix(unsigned int rows = 0, unsigned int cols = 0, double val = 0);
    Matrix(unsigned int rows, unsigned int cols, double* data);
    Matrix(Matrix& clone);
    Matrix(Matrix&& clone) noexcept;
    Matrix(MatrixType Type, unsigned int n); // square matrix nxn: E - single, O - all elements = 0.
    Matrix& operator= (const Matrix&  clone);
    Matrix& operator= (const Matrix&& clone) noexcept;
    ~Matrix();

public:
    void set(unsigned int row, unsigned int col, double val);
    double get(unsigned int row, unsigned int col); // return 0 if out of range
    double trace(); // return 0 if matrix not square
    double det();   // return 0 if matrix not square
    double minorij(unsigned int row, unsigned int col); // return 0 if matrix not square or out of range
    double complement(unsigned int row, unsigned int col); // return 0 if matrix not square or out of range

public:
    Matrix operator+ (const Matrix& val);
    Matrix operator- (const Matrix& val);
    Matrix operator* (double val);
    Matrix operator* (const Matrix& val);
    double operator() (unsigned int row, unsigned int col);// instead [i][j] use (i, j), return 0 if out of range

public:
    void print();
    void transposition();
    void reverse();
    void normalization();
    void swap_rows(unsigned int row_first, unsigned int row_second);
    void swap_cols(unsigned int col_first, unsigned int col_second);
    void free_memory();
};

#endif //MATRIX_MATRIX_H
