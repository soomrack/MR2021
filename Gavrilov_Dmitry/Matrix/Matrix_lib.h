
#ifndef MATRIX_MATRIX_LIB_H
#define MATRIX_MATRIX_LIB_H
#include <iostream>

enum Matrix_type {
    ZERO_MATRIX = 0,
    IDENITY_MATRIX = 1,
    RAND_MATRIX = 2
};

class Matrix {
private:

    unsigned int rows;
    unsigned int columns;
    int * data;
    void creat_zero_matrix();
    void creat_identity_matrix();
    void creat_random_matrix();
public:

    Matrix(unsigned int rows = 0, unsigned int columns =0  , int type = ZERO_MATRIX );
    ~Matrix();
    Matrix(const Matrix &other);
    Matrix(Matrix &&other) noexcept;

    Matrix operator+ (const Matrix &);
    Matrix operator- (const Matrix &);
    Matrix operator* (const Matrix &);
    Matrix & operator= (Matrix &&) noexcept;
    Matrix & operator= (const Matrix &);

    int trace();
    double determinate();
    void print();
};

#endif //MATRIX_MATRIX_LIB_H
