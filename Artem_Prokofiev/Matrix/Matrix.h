#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

class Matrix {
public:
    unsigned int rows;
    unsigned int cols;
    double * data;

public:
    double trace(const Matrix A); // trace of matrix
    Matrix sum(const Matrix A, const Matrix B); // sum of matrix
    Matrix transposition(const Matrix A); // matrix transposition
    Matrix Minor(int rows, int cols, const Matrix A); // matrix minors
    Matrix add(const Matrix A); //matrix of additions
    double det(const Matrix A); // matrix determinant
    Matrix mult(const Matrix A, const Matrix B); // matrix multiplication
    Matrix mult_scalar(const double scalar, const Matrix A); // matrix multiplication by scalar
    Matrix single(const unsigned int size); // unit matrix
    Matrix power(const Matrix A, const unsigned int power); // degree of raise of the matrix
    void print(const Matrix A); // put matrix on the screen
};

#endif //MATRIX_MATRIX_H
