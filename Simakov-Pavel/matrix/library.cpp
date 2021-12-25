#include "library.h"
#include <iomanip>
#include <iostream>

Matrix::Matrix(int rows, int columns) // constructor with parameters
{
    this -> rows = rows;
    this -> columns = columns;
    this -> elements = new double[rows*columns];

}

Matrix::Matrix(int range, char type, int nothing) // constructor for 0-1 order
{
    this -> rows = range;
    this -> columns = range;
    elements = new double[rows * columns];
    if (type == '0')
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                elements[i * columns + j] = 0.;
            }
        }
    }
    if (type == '1')
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                if (i == j) elements[i * columns + j] = 1.;
                else elements[i * columns + j] = 0.;
            }
        }
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

void Matrix::output()
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
    this -> rows = m.rows;
    this -> columns = m.columns;
    this -> elements = new double [rows*columns];
    memcpy(this -> elements, m.elements, rows*columns*sizeof(double));
}

Matrix::Matrix(Matrix &&m) noexcept // move
{
    this -> rows = m.rows;
    this -> columns = m.columns;
    this -> elements = m.elements;
    m.elements = nullptr;
    m.rows = 0;
    m.columns = 0;
}

Matrix & Matrix::operator = (const Matrix & m) // overload assignment
{
    if (this == &m) return *this;
    this -> rows = m.rows;
    this -> columns = m.columns;
    delete[] this -> elements;
    this -> elements = new double[rows*columns];
    for (int i = 0; i < (rows*columns); i++)
    {
        this -> elements[i] = m.elements[i];
    }
    memcpy(elements, m.elements, rows*columns*sizeof(double));
    return *this;
}

Matrix Matrix::operator + (const Matrix& m) // overload +
{
    if ((rows != m.rows) || (columns != m.columns))
    {
        std::cout << "the size of the matrices does not match" << std::endl;
        return Matrix (0,0);
    }

    Matrix sum(rows, columns);
    for (int i = 0; i < rows*columns; i++)
    {
        sum.elements[i] = this -> elements[i] + m.elements[i];
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
    this -> rows = m.rows;
    this -> columns = m.columns;
    delete[] this -> elements;
    this -> elements = m.elements;
    m.elements = nullptr;
    m.rows = 0;
    m.columns = 0;
}

int Matrix::trace()
{
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
    memset(cut.elements, 0, (rows-1)*(columns-1)*8);
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
            cut.elements[cut.columns*i + j] = elements[columns*(skipped_row + 1) + (j+skipped_column)];
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
    switch (rows)
    {
        case 0:
        {
            std::cout << "null matrix error" << std::endl;
            return -1;
        }
        case 1:
        {
            return elements[0];
        }
        case 2:
        {
            return elements[0]*elements[3] - elements[1]*elements[2];
        }
        default:
            for (int i = 0; i < rows; i++)
            {
                determ += pow(-1,i+2) * elements[i] * minor(0,i);
            }
            return determ;
    }

}