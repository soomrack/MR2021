//
// Created by shlyk on 27.12.2021.
//
#ifndef UNTITLED3_MATRIX_H
#define UNTITLED3_MATRIX_H
typedef enum {
    RANDOM,
    ZERO,
    IDENTITY,
    ONES
}Matrix_type;

class Matrix {
private:
    unsigned int rows = 0;
    unsigned int cols = 0;
    double *matrix;
public:
    Matrix(unsigned int rows, unsigned int cols, Matrix_type type);
    Matrix();
    Matrix(const Matrix &other);
    Matrix(Matrix &&other) noexcept;
    ~Matrix();
public:
    Matrix& operator= (const Matrix &other);
    Matrix& operator= (Matrix &&other) noexcept;
    Matrix operator+ (const Matrix &other);
    Matrix operator- (const Matrix &other);
    Matrix operator* (const Matrix &other);
    void set_random();
    void set_zero();
    void set_ones();
    void set_identity();
    double trace();
    double det();
    void print();
private:
    void memory_allocation();
    void free_memory();
};
#endif //UNTITLED3_MATRIX_H
