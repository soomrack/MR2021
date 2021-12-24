#include "Matrix.h"
#include <cmath>
#include <iostream>
#include <cstring>


Matrix::Matrix(){  // default matrix
    this -> rows = rows = 0;
    this -> cols = cols = 0;
    data = new double [rows * cols];
}

Matrix::Matrix(int rows, int cols) { // create Matrix
    this -> rows = rows;
    this -> cols = cols;
    try {
        data = new double [rows * cols];
    } catch (std::bad_alloc& e) {
        printf("Could not create matrix\n");
    }
}

void Matrix::assigning(int num_row, int num_col, double value) {  // put a value for element
    data[cols*num_row + num_col] = value;
}

void Matrix::print() {  // put matrix on the screen
    std::cout << "matrix \n";
    for (int i = 0; i < (cols * rows); i++)
    {
        printf ("%.2f\t", data[i]);
        if ((i+1)%cols == 0)
        {
            printf("\n");
        }
    }
}

Matrix :: Matrix(const Matrix &other) { // copying the matrix
    this -> rows = other.rows;
    this -> cols = other.cols;
    this -> data = new double [rows * cols];
    memcpy(this -> data, other.data,sizeof(double)* rows * cols);
}

Matrix::Matrix(Matrix &&other) noexcept { //moving of matrix
    this -> rows = other.rows;
    this -> cols = other.cols;
    this -> data = other.data;
    other.data = nullptr;
    other.rows = 0;
    other.cols = 0;
}

Matrix & Matrix::operator = (Matrix &&other) noexcept { // reloading the assignment operator to move
    this -> rows = other.rows;
    this -> cols = other.cols;
    delete [] this -> data;
    this -> data = other.data;
    other.data = nullptr;
    other.rows = 0;
    other.cols = 0;
    return *this;
}

void Matrix::zero(){  // zero matrix
    for (int i = 0; i < cols*rows; i++)
    {
        data[i] = 0;
    }
}

void Matrix::single(){  // unit matrix
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (rows == cols)
            {
                if (i == j)
                {
                    data[i * cols + j] = 1;
                }
                else
                {
                    data[i * cols + j] = 0;
                }
            }
            else
            {
                std::cout << "Not squire matrix\n";
            }
        }
    }
}

double Matrix::trace()  // trace of matrix
{
    double trace_matrix = 0;
    for (int i = 0; i < rows; i++)
    {
        trace_matrix += data[i*cols+i];
    }
    return trace_matrix;
}



Matrix Matrix::Mult_scalar(const double scalar, const Matrix)  // matrix multiplication on scalar
{
    Matrix Result(rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            data[i * cols + j] = scalar * data[i * cols + j];
        }
    }
}

Matrix Matrix :: operator+(const Matrix &other){ // operator sum of matrix
    if ((this -> cols != other.cols) || (this -> rows != other.rows))
    {
        Matrix Result;
        std::cout << "Different sizes of matrix\n" << std::endl;
        return Result;
    }
    else
    {
        Matrix Result(rows, cols);
        for (unsigned int i = 0; i < rows * cols; i++) {
            Result.data[i] = data[i] + other.data[i];
        }
        return Result;
    }
}

Matrix Matrix :: operator-(const Matrix &other) // operator matrix difference
{
    if ((this -> cols != other.cols) || (this -> rows != other.rows))
    {
        Matrix Result;
        std::cout << "Different sizes of matrix\n" << std::endl;
        return Result;
    }
    else
    {
        Matrix Result(rows, cols);
        for (unsigned int i = 0; i < rows * cols; i++) {
            Result.data[i] = data[i] - other.data[i];
        }
        return Result;
    }
}

Matrix Matrix::operator * (const Matrix &other) { // operator matrix multiplication
    if (this -> cols != other.rows) {
        Matrix Result;
        std::cout << "Incorrect sizes of matrix\n" << std::endl;
        return Result;
    }
    else {
        Matrix Result(rows, other.cols);
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                for (int k = 0; k < other.cols; k++) {
                    Result.data[cols * i + j] += (this->data[cols * i + k] * other.data[cols * k + j]);
                }
            }
        }
        return Result;
    }
}

Matrix Matrix::Minor(int rows, int cols, const Matrix A) { // matrix minors
    Matrix result(A.rows-1, A.cols-1);
    int k = 0;
    for (int i = 0; i < A.rows; i++)
    {
        for (int j = 0; j < A.cols; j++)
        {
            if ((i == rows) || (j == cols))
            {
                continue;
            }
            result.data[k] = A.data[i * A.cols + j];
            k++;
        }
    }
    return result;
};

Matrix Matrix::addition(const Matrix A) { // additions of matrix
    Matrix result (A.rows, A.cols);
    for (int i = 0; i < A.rows; i++)
    {
        for (int j = 0; j <  A.cols; j++)
        {
            result.data[i*A.cols + j] = pow((-1), i + j) * determinant(Minor(i, j, A));
        }
    }
    return result;
}

double Matrix::determinant(const Matrix A) { // matrix determinant
    if(A.rows != A.cols) {
        std::cout << "Not squire matrix\n" << std::endl;
    }
    else {
        double D = 0;
        switch (A.rows) {
            case 1:
                return A.data[0];
            case 2:
                return (A.data[0] * A.data[3] - A.data[1] * A.data[2]);
            default: {
                Matrix Dop = addition(A);
                for (int j = 0; j < A.cols; j++) {
                    D += A.data[j] * Dop.data[j];
                }
                return D;
            }
        }
    }
}

extern Matrix Matrix::transposition(const Matrix A) {
    Matrix Result (A.cols, A.rows);
    for (int i = 0; i < A.rows; i++) {
        for (int j = 0; j < A.cols; j++) {
            Result.data[j * A.rows + i] = A.data[i * A.cols + j];
        }
    }
    return Result;
}

Matrix::~Matrix() { // Destructor
    delete[] data;
}