#include <iostream>
#include <cstring>
#include <typeinfo>

#ifndef MAIN_CPP_MATRIX_LIB_H
#define MAIN_CPP_MATRIX_LIB_H

class Matrix {
public:;
private:
    int m_height;
    int m_width;
    double **data;
public:
    /* Конструктор по умолчанию */
    /*Matrix(int height = 2, int width = 2) {
        m_height = height;
        m_width = width;
        //data = (double **) malloc(m_height * m_width * sizeof(double));
        data=new double* [m_height];
        for (int row = 0; row < m_height; row++) {
            data[row]= new double [m_width];
        }
    }*/
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

