#ifndef C_MATRIX_C_MATRIX_H
#define C_MATRIX_C_MATRIX_H

#include <cstdlib>
#include <iostream>

class Matrix {
private:
    unsigned int height;
    unsigned int width;
    int *data;
public:
    Matrix();
    Matrix(unsigned int height, unsigned int width);
    Matrix(const Matrix &Matrix);
    Matrix(Matrix &&Matrix) noexcept;
    ~Matrix();
public:
    Matrix& operator= (const Matrix &other);
    Matrix& operator= (Matrix &&other) noexcept;
    Matrix operator+ (const Matrix &other);
    Matrix operator- (const Matrix &other);
    Matrix operator* (const Matrix &other);
public:
    void set_Random();
    void set_Identity();
    void set_Zero();
public:
    int trace(); // Сумма главной диагонали матрицы
    double determinant(); // Определитель матрицы
public:
    void output();
};
#endif //C_MATRIX_C_MATRIX_H