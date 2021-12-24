#pragma once
#include <iostream>
#include <vector>

class Matrix {
private:
    unsigned int rows = 0;
    unsigned int columns = 0;
    double** data = nullptr;
    double* data_line = nullptr;
//functions for filling matrix
private:
    void zeros();
    void ones();
    void identity();
    void random();
private:
    void allocate_mem(unsigned int, unsigned int);
    void clear_mem();
    void sort_rows(unsigned int);
public:
    //Matrix types: '0' - filled with zeros;
    //              '1' - filled with ones;
    //              'E' - identity matrix;
    //              'R' - filled with random values;
    Matrix(unsigned int rows = 0, unsigned int columns = 0, char type = 'E');
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
    unsigned int get_rows();
    unsigned int get_columns();
    double get_value(unsigned int,unsigned int);
    Matrix get_transpose();
    void print_matrix();
public:
    void set_matrix_from_1d(double* arr);
    template<unsigned int lines, unsigned int cols>
    void set_matrix_from_2d(double (&arr)[lines][cols]); //
    void set_values_cmd();
    void set_value(unsigned int,unsigned int,double);
};