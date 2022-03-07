#pragma once
#include <iostream>
using namespace std;

class Matrix
{
private:   //Useful things
    double *string = nullptr;
    double **Matr = nullptr;
    int length = 0;
    int height = 0;
private:   // Private methods
    double** alloc(unsigned int length, unsigned int height);
    void clear_memory();
    void sort_rows(unsigned int col);
public:    // Constructors and destructor
    Matrix();
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
    void create_matrix(double *arr);
    void create_matrix_one();
    void display();
    int trace();
    double determinant ();
};
