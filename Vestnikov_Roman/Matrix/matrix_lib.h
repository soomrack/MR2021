#include <iostream>

#ifndef MAIN_CPP_MATRIX_LIB_H
#define MAIN_CPP_MATRIX_LIB_H

class Matrix {
private:
    int m_height;
    int m_width;
    double **data;

public:
    Matrix(int height, int width);
    explicit Matrix(int height=2);

    ~Matrix() { delete data ; };

    Matrix(Matrix &&matrix) noexcept ;

    void creator();
    void random();
    void print();
    void identity();
    void zero();
    void determinant();
    void trace();
    void memory_update ();

    Matrix &operator= (const Matrix &matrix);
    Matrix operator+ (const Matrix &matrix);
    Matrix operator- (const Matrix &matrix);
    Matrix operator* (const Matrix &matrix);

};

#endif //MAIN_CPP_MATRIX_LIB_H
