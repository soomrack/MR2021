#include "library.h"
#include <iomanip>
#include <iostream>
#include <cmath>

Matrix::Matrix()
{
    this->rows = 0;
    this->columns = 0;
    elements = nullptr;
}

Matrix::Matrix(unsigned int rows, unsigned int columns) // constructor with parameters
{
    this -> rows = rows;
    this -> columns = columns;
    this -> elements = new double[rows*columns];
}

Matrix::Matrix(unsigned int range,Type type) // constructor for 0-1 order
{
    rows = range;
    columns = range;
    elements = new double[rows * columns];
    switch (type) {
        case (TYPE_NULL):
        {
            fill_zeros();
            break;
        }
        case (TYPE_ONE):
        {
            fill_ones();
            break;
        }
        default:
        {
            std::cout << "wrong types of matrix" << std::endl;
            rows = 0;
            columns = 0;
            elements = nullptr;
        }
    }
}

void Matrix::fill_zeros()
{
    for (int i = 0; i < rows*columns; i++)
    {
        elements[i] = 0.;
    }
}

void Matrix::fill_ones()
{
    fill_zeros();
    for (int i = 0; i < rows*columns; i+=rows)
    {
        elements[i] = 1.;
    }
}

void Matrix::user_input()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            std::cout << i+1 << " " << j+1 <<": " << std::endl;
            std::cin >> elements[i*columns + j];
        }
    }
}

void Matrix::print()
{
    for (int i = 0; i < rows; i++)
    {
        std::cout << "\n";
        for (int j = 0; j < columns; j++)
        {
            std::cout << std::fixed << std::setprecision(2) << elements[i*columns + j] << "   ";
        }
    }
    std::cout << "\n";
}

Matrix::~Matrix() //destructor
{
    delete[] elements;
}

Matrix::Matrix(const Matrix &m) //copy
{
    rows = m.rows;
    columns = m.columns;
    elements = new double [rows*columns];
    memcpy(elements, m.elements, rows*columns*sizeof(double));
}

Matrix::Matrix(Matrix &&m) noexcept // move
{
    rows = m.rows;
    columns = m.columns;
    elements = m.elements;
    m.elements = nullptr;
    m.rows = 0;
    m.columns = 0;
}

Matrix & Matrix::operator = (const Matrix & m) // overload assignment
{
    if (this == &m) return *this;
    rows = m.rows;
    columns = m.columns;
    delete[] this -> elements;
    elements = new double[rows*columns];
    memcpy(elements, m.elements, rows*columns*sizeof(double));
    return *this;
}

Matrix Matrix::operator + (const Matrix& m) // overload +
{
    if ((rows != m.rows) || (columns != m.columns))
    {
        std::cout << "the size of the matrices does not match" << std::endl;
        return Matrix(0,0);
    }

    Matrix sum(rows, columns);
    sum.fill_zeros();
    for (int i = 0; i < rows*columns; i++)
    {
        sum.elements[i] = elements[i] + m.elements[i];
    }
    return sum;
}

Matrix Matrix::operator * (const Matrix& m) // overload *
{
    if (rows != m.columns)
    {
        std::cout << "the size of the matrices does not match" << std::endl;
        return Matrix (0,0);
    }
    Matrix compos(rows, m.columns);
    compos.fill_zeros();
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            for (int k = 0; k < m.columns; k++)
            {
                compos.elements[m.columns*i + j] += elements[columns*i + k] * m.elements[m.columns*k + j];
            }
        }
    }
    return compos;
}

Matrix & Matrix::operator = (Matrix && m) noexcept //overload for move
{
    if (this == &m) return *this;
    rows = m.rows;
    columns = m.columns;
    delete[] elements;
    elements = m.elements;
    m.elements = nullptr;
    m.rows = 0;
    m.columns = 0;
}

int Matrix::trace()
{
    if (rows != columns)
    {
        std::cout << "matrix should be square" << std::endl;
        return -1;
    }
    int sum = 0;
    for (int i = 0; i < rows; i++)
    {
        sum += elements[columns*i + i];
    }
    return sum;
}

double Matrix::minor(int number_row, int number_column)
{
    Matrix cut(rows-1, columns-1);
    cut.fill_zeros();
    int skipped_row = 0;
    int skipped_column = 0;
    for (int i = 0; i < cut.rows; i++)
    {
        {
            if (i == number_row) skipped_row++;
        }
        for (int j = 0; j < cut.columns; j++)
        {
            if (j == number_column) skipped_column++;
            cut.elements[cut.columns*i + j] = elements[columns*(skipped_row + i) + (j+skipped_column)];
        }
        skipped_column = 0;
    }
    return cut.det();
}
double Matrix::det()
{
    if (rows != columns)
    {
        std::cout << "matrix should be square" << std::endl;
        return -1;
    }
    double determ = 0;
    if (rows == 0)
    {
        std::cout << "null matrix error" << std::endl;
        return -1;
    }
    if (rows == 1)
    {
        return elements[0];
    }
    if (rows == 2)
    {
        return elements[0]*elements[3] - elements[1]*elements[2];
    }
    for (int i = 0; i < columns; i++)
    {
        determ += pow(-1,i+2) * elements[i] * minor(0,i);
    }
    return determ;
}