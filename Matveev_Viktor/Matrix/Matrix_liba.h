#pragma once
#include <iostream>
using namespace std;

class Matrix
{
private:
    double **Matr;
    int length;
    int height;

public:

    // Constructors and destructor
    Matrix();
    Matrix(unsigned int length, unsigned int height);
    Matrix(Matrix&&) noexcept;
    ~Matrix();

    // Overloaded operators
    Matrix operator + (const Matrix &);
    Matrix operator - (const Matrix &);
    Matrix operator * (const Matrix &);
    Matrix & operator = (Matrix &&) noexcept;
    Matrix & operator = (const Matrix &);

    // Various methods
    double** alloc(unsigned int length, unsigned int height);
    void vanish(double**);
    template<size_t N> void Create_Matrix(double (&arr)[N]);
    void Create_Matrix_One();
    void Display();
    int Trace();
    double Determinant ();
    void sort_rows(unsigned int col);
};
