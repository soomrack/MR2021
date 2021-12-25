#pragma once
#include <iostream>
#include <vector>

typedef enum {
    ZEROS,
    ONES,
    IDENTITY,
    RANDOM
} Matrix_type;

class Matrix {
private:
    unsigned int rows = 0;
    unsigned int columns = 0;
    double** data = nullptr;
    double* data_line = nullptr;
public:
    //Matrix types: ZERO - filled with zeros;
    //              ONES - filled with ones;
    //              IDENTITY - identity matrix;
    //              RANDOM - filled with random values;
    Matrix(unsigned int rows = 0, unsigned int columns = 0, Matrix_type type = ZEROS);
    Matrix(const Matrix&);
    Matrix(Matrix&&) noexcept;
    ~Matrix();
public:
    Matrix operator+ (const Matrix &);
    Matrix operator- (const Matrix &);
    Matrix operator* (const Matrix &);
    Matrix & operator= (Matrix &&) noexcept;
    Matrix & operator= (const Matrix &);
public:
    double get_det();
    unsigned int get_rows() { return rows; }
    unsigned int get_columns() { return columns; }
    double get_value(unsigned int,unsigned int);
    Matrix get_transpose();
    void print_matrix();
public:
    void set_matrix_from_1d(double* arr);
    template<unsigned int height, unsigned int width>
    void set_matrix_from_2d(double (&arr)[height][width]); //
    void set_values_cmd();
    void set_value(unsigned int,unsigned int,double);
private:
    void allocate_mem(unsigned int, unsigned int);
    void clear_mem();
    void sort_rows(unsigned int);
private: //functions for filling matrix
    void set_zeros();
    void set_ones();
    void set_identity(); // if matrix isn't square fills with zeros
    void set_random();
};
