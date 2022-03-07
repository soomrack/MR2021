
#ifndef MATRIX_MATRIX_LIB_H
#define MATRIX_MATRIX_LIB_H
#include <iostream>

typedef enum  {
    ZERO_MATRIX,
    IDENITY_MATRIX,
    RAND_MATRIX
}Matrix_type;

class Matrix {
private:

    unsigned int rows;
    unsigned int columns;
    int * data;
    void creat_zero_matrix();
    void creat_identity_matrix();
    void creat_random_matrix();
public:

    Matrix(unsigned int rows = 0, unsigned int columns =0  , Matrix_type type = ZERO_MATRIX );
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
