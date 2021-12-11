#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <iostream>

typedef enum{
    IDENTITY,
    ONES,
    ZEROS,
    RANDOM,
} MatrixType;

class Matrix{
private:
    unsigned int height = 0;
    unsigned int width = 0;
    double* data_1d = nullptr;
    double** data_2d = nullptr;
public:
    explicit Matrix(unsigned int height = 0, unsigned int width = 0, double value = 0.0);
    Matrix(unsigned int height, unsigned int width, MatrixType type);
    Matrix(unsigned int height, unsigned int width, double *arr);
    Matrix(const Matrix& other);
    Matrix(Matrix&& other) noexcept;
    Matrix& operator= (const Matrix& other);
    Matrix& operator= (Matrix&& m) noexcept;
    ~Matrix();
public:
    double get(unsigned int row, unsigned int col);
    int set(unsigned int row, unsigned int col, double value);
public:
    unsigned int get_height();
    unsigned int get_width();
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
private:
    void set_identity();
    void set_ones();
    void set_zeros();
    void set_random();
private:
    void apply_forward_elimination();
    void alloc_memory(unsigned int height, unsigned int width);
    void free_memory();
};

#endif //MATRIX_MATRIX_H
