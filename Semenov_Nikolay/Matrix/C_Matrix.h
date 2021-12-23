#ifndef C_MATRIX_C_MATRIX_H
#define C_MATRIX_C_MATRIX_H

#include <cstdlib>
#include <iostream>

class Matrix {
private:
    int height = 0;
    int width = 0;
    int *data;
    void erase(int* data) const;
public:
    Matrix(int height, int width); //Initialising
    Matrix(const Matrix &Matrix); //For copying
    Matrix(Matrix &&Matrix) noexcept; //Moving
    ~Matrix(); //Destructor
    void Rand(int height, int width); //Fill matrix with random values
    void Identity();
    void Zero();
    void Output();
    Matrix operator + (const Matrix &other);
    Matrix operator - (const Matrix &other);
    Matrix operator * (const Matrix &other);
    int Trace();
    double Determinant();
};
#endif //C_MATRIX_C_MATRIX_H