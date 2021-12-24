#pragma once
#include <iostream>
using namespace std;

class Matrix
{
private:
    double *data_line = nullptr;
    double **data = nullptr;
    int length = 0;
    int height = 0;
private:
    double** allocation_memory(unsigned int length, unsigned int height);
    void clear_memory();
    void sort_rows(unsigned int col);
public:    // Constructors and destructor
    Matrix(unsigned int length=0, unsigned int height=0);
    Matrix(const Matrix& other);
    Matrix(Matrix&& other) noexcept;
    ~Matrix();
public:    // Overloaded operators
    Matrix operator + (const Matrix &);
    Matrix operator - (const Matrix &);
    Matrix operator * (const Matrix &);
    Matrix & operator = (Matrix &&) noexcept;
    Matrix & operator = (const Matrix &);
public:    // Various methods
    void set_matrix(double *arr);
    void set_matrix_one(); //set 1 on main diagonal (even if matrix not square)
    void display();
    int trace(); //returns sum of numbers on main diagonal (even if matrix not square)
    double determinant ();
};
