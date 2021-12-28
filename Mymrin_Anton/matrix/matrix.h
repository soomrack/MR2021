#pragma once
#include <cstring>
using namespace std;

class Matrix {
public:
    Matrix(unsigned int row, unsigned int col);
    Matrix(unsigned int row, unsigned int col, int null);
    Matrix(unsigned int size);
    ~Matrix();
    Matrix();
    Matrix(const Matrix& m);
    void print();
    double det();
    double trace();
private:
    unsigned int row=1;
    unsigned int col=1;
    unsigned int size=1;
    double *data;
public:
    Matrix& operator =(const Matrix& m);
    Matrix operator +(const Matrix& m);
    Matrix operator -(const Matrix& m);
    Matrix operator *(const Matrix& m);
};






