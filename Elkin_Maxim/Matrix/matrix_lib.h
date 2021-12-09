#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

class Matrix {
private:
    unsigned int rows;
    unsigned int columns;
    double** data;
public:
    Matrix(unsigned int rows = 0, unsigned int columns = 0);
    Matrix(const Matrix&);
    Matrix(Matrix&&) noexcept;
    ~Matrix();

    Matrix operator+ (const Matrix &);
    Matrix operator- (const Matrix &);
    Matrix operator* (const Matrix &);
    Matrix & operator= (Matrix &&) noexcept;
    Matrix & operator= (const Matrix &);

    double** allocate_mem(unsigned int, unsigned int);
    void clear_mem(double**);
    double get_det();
    unsigned int get_rows();
    unsigned int get_columns();
    double get_value(unsigned int,unsigned int);
    void print_matrix();
    Matrix get_transpose();
    template<unsigned int lines, unsigned int cols>
    void set_matrix(double (&arr)[lines][cols]);
    void set_values_cmd();
    void set_value(unsigned int,unsigned int,double);
    void sort_rows(unsigned int);
};