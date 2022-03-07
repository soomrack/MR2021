#pragma once
#include <cstring>
using namespace std;

class Matrix {

private:
    unsigned int row=1;
    unsigned int col=1;
    unsigned int size=1;
    double *data;

public:
    Matrix(unsigned int row, unsigned int col, int value);
    Matrix(unsigned int size);
    ~Matrix();
    Matrix();
    Matrix(const Matrix& m);
    Matrix(Matrix&& m) noexcept ;
    void print();
    double det();
    double trace();

public:
    Matrix& operator =(const Matrix& m);
    Matrix operator =(Matrix &&m);
    Matrix operator +(const Matrix& m);
    Matrix operator -(const Matrix& m);
    Matrix operator *(const Matrix& m);
};






