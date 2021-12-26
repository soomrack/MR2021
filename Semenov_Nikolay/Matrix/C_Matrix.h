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
    void set_Random(int height, int width);
    void set_Identity();
    void set_Zero();
    void output();
    Matrix operator+ (const Matrix &other);
    Matrix operator- (const Matrix &other);
    Matrix operator* (const Matrix &other);
    int trace(); // Сумма главной диагонали матрицы
    double determinant(); // Определитель матрицы
};
#endif //C_MATRIX_C_MATRIX_H