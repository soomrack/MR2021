#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <iostream>

typedef enum{
    IDENTITY_MATRIX,
    UPPER_TRIANG_MATRIX_OF_ONES,
    LOWER_TRIANG_MATRIX_OF_ONES,
} SpecialType;


class Matrix{
private:
    int height;
    int width;
    double** data;
public:
    Matrix(int height, int width);
    Matrix(int height, int width, SpecialType type);
    Matrix(int height, int width, double value);
    Matrix(const Matrix& m);
    Matrix(Matrix&& m) noexcept;
    Matrix& operator= (const Matrix& m);
    ~Matrix();
public:
    double get(int i, int j);
    void set(int i, int j, double value);
public:
    Matrix operator+ (const Matrix& m);
    Matrix operator- (const Matrix& m);
    Matrix operator* (const Matrix& m);
public:
    double tr();
    double det();
public:
    friend std::ostream& operator<< (std::ostream &out, const Matrix& m);
    void print();
};


#endif //MATRIX_MATRIX_H
