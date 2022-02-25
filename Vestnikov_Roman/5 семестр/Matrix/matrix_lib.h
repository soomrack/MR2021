#include <iostream>
#include <cstring>

#ifndef MATRIX_LIB_H
#define MATRIX_LIB_H

class Matrix {
private:
    unsigned int height = 0;
    unsigned int width = 0;
    double *data_1 = nullptr;
    double **data_2 = nullptr;
public:
    explicit Matrix(unsigned int height = 0, unsigned int width = 0);
    Matrix(const Matrix &matrix);
    Matrix(Matrix &&matrix) noexcept;
    ~Matrix();
public:
    void set_array(double *array);
    void set_random();
    void set_identity();
    void set_zero();
    void print();
public:
    double det();
    double trace();
public:
    Matrix &operator=(const Matrix &matrix);
    Matrix &operator=(Matrix &&) noexcept;
    Matrix operator+(const Matrix &matrix);
    Matrix operator-(const Matrix &matrix);
    Matrix operator*(const Matrix &matrix);
private:
    void sort_rows(unsigned int col);
    void memory_allocation(unsigned int height, unsigned int width);
    void memory_clearing();
};

#endif //MATRIX_LIB_H
