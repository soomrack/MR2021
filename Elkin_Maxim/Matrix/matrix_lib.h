#pragma once
#include <iostream>
#include <vector>

class Matrix {
private:
    unsigned int rows = 0;
    unsigned int columns = 0;
    double** data = nullptr;
    double* data_line = nullptr;
private:
    void allocate_mem(unsigned int, unsigned int);
    void clear_mem();
    void sort_rows(unsigned int);
public:
    Matrix(unsigned int rows = 0, unsigned int columns = 0);
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
    template<unsigned int lines, unsigned int cols>
    void set_matrix(double (&arr)[lines][cols]); //
    void set_values_cmd();
    void set_value(unsigned int,unsigned int,double);
};