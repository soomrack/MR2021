#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <iostream>

typedef enum{
    IDENTITY,
    ONES,
    ZEROS,
    RANDOM,
} SpecialType;

class Matrix{
private:
    unsigned int height;
    unsigned int width;
    double** data;
public:
    explicit Matrix(unsigned int height = 0, unsigned int width = 0, double value = 0.0);
    Matrix(unsigned int height, unsigned int width, SpecialType type);
    Matrix(const Matrix& m);
    Matrix(Matrix&& m) noexcept;
    Matrix& operator= (const Matrix& m);
    Matrix& operator= (Matrix&& m) noexcept;
    ~Matrix();
public:
    double get(unsigned int row, unsigned int col);
    int set(unsigned int row, unsigned int col, double value);
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
    double** alloc_memory(unsigned int new_height, unsigned int new_width);
    void free_memory(double** freeing_data);
};

#endif //MATRIX_MATRIX_H
