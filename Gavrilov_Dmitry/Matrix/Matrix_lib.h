
#ifndef MATRIX_MATRIX_LIB_H
#define MATRIX_MATRIX_LIB_H
#include <iostream>

class Matrix {
private:
    unsigned int rows;
    unsigned int columns;
    int * data;

public:
    Matrix(unsigned int rows, unsigned int columns, unsigned int type);
    ~Matrix();
    Matrix(const Matrix &other);
    Matrix(Matrix &&other) noexcept;

    Matrix operator+ (const Matrix &);
    Matrix operator- (const Matrix &);
    Matrix operator* (const Matrix &);
    Matrix & operator= (Matrix &&) noexcept;
    Matrix & operator= (const Matrix &);

    int tr();
    double det();
    void print();
};

#endif //MATRIX_MATRIX_LIB_H
