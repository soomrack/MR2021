#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

class Matrix {

public:
    unsigned int rows;
    unsigned int cols;
    double * data;

public:
    Matrix();  // default matrix
    Matrix(int rows, int cols); // create Matrix

    ~Matrix(); // Destructor

    Matrix (const Matrix &other); // copying the matrix
    Matrix (Matrix &&other) noexcept; // moving of matrix
    Matrix & operator = (Matrix &&other) noexcept; // reloading the assignment operator to move
    Matrix operator + (const Matrix &other); // operator sum of matrix
    Matrix operator - (const Matrix &other); // operator matrix difference
    Matrix operator * (const Matrix &other); // operator matrix multiplication
    Matrix Mult_scalar(const double scalar,const Matrix); // matrix multiplication on scalar
    Matrix addition(const Matrix A);  // additions of matrix
    Matrix Minor(int rows, int cols, const Matrix A); // matrix minors
    Matrix transposition(const Matrix A); // matrix transposition

    double determinant(const Matrix A); // matrix determinant
    void assigning(int num_row, int num_col, double value); // put a value for element
    void print(); // put matrix on the screen
    void zero(); // zero matrix
    void single(); // unit matrix
    double trace(); // trace of matrix
};

#endif
