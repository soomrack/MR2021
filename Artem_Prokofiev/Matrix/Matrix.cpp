#include "Matrix.h"
#include <cmath>
#include <iostream>
#include <cstring>


enum{
ERRSQUIRE = -1, // Size error! Not squire matrix!
ERRNUMBER = -2, // Assignment error! There is no such element in the matrix!
};

Matrix::Matrix(){  // default matrix
    this -> rows = 0;
    this -> cols = 0;
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

int Matrix::value(int num_row, int num_col, double value) {  // put a value for element
    if ((num_col>cols)||(num_row>rows)){
        return ERRNUMBER;
    }
    data[cols*num_row + num_col] = value;
}

void Matrix::print() {  // put matrix on the screen
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

void Matrix::set_zero(){  // zero matrix
    for (int i = 0; i < cols*rows; i++)
    {
        data[i] = 0;
    }
}

int Matrix::set_identity_matrix(){  // unit matrix
    if (rows != cols){
        return ERRSQUIRE;
    }
    set_zero();
    int j = 0;
    for (int i = 0; i < rows && j<cols; i++ && j++)
    {
        if (i == j)
        {
            data[i * cols + j] = 1;
        }
    }
}

double Matrix::trace(){  // trace of matrix
    double trace_matrix = 0.0;
    if (cols != rows)
    {
        trace_matrix = NAN;
        return trace_matrix;
    }
    for (int i = 0; i < rows; i++)
    {
        trace_matrix += data[i*cols+i];
    }
    return trace_matrix;
}

Matrix Matrix::mult_scalar(const double scalar, const Matrix)  // matrix multiplication on scalar
{
    Matrix Result(rows, cols);
    for (int i = 0; i < rows*cols; i++) {
        data[i] = scalar * data[i];
    }
}

Matrix Matrix :: operator+(const Matrix &other){ // operator sum of matrix
    if ((this -> cols != other.cols) || (this -> rows != other.rows))
    {
        Matrix result;
        return result;
    }
    else
    {
        Matrix result(rows, cols);
        for (unsigned int i = 0; i < rows * cols; i++) {
            result.data[i] = data[i] + other.data[i];
        }
        return result;
    }
}

Matrix Matrix :: operator-(const Matrix &other) // operator matrix difference
{
    if ((this -> cols != other.cols) || (this -> rows != other.rows))
    {
        Matrix result;
        return result;
    }
    else
    {
        Matrix result(rows, cols);
        for (unsigned int i = 0; i < rows * cols; i++) {
            result.data[i] = data[i] - other.data[i];
        }
        return result;
    }
}

Matrix Matrix::operator * (const Matrix &other) { // operator matrix multiplication
    if (this -> cols != other.rows) {
        Matrix result;
        return result;
    }
    Matrix result(rows, other.cols);
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                for (int k = 0; k < other.cols; k++) {
                    result.data[cols * i + j] += (this->data[cols * i + k] * other.data[cols * k + j]);
                }
            }
        }
    return result;
}


Matrix Matrix::minor(int rows, int cols, const Matrix A) { // matrix minors
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
}

Matrix Matrix::addition(const Matrix A) { // additions of matrix
    Matrix result (A.rows, A.cols);
    for (int i = 0; i < A.rows; i++)
    {
        for (int j = 0; j <  A.cols; j++)
        {
            result.data[i*A.cols + j] = pow((-1), i + j) * determinant(minor(i, j, A));
        }
    }
    return result;
}

double Matrix::determinant(const Matrix A) { // matrix determinant
    double det = 0.0;
    if(A.rows != A.cols) {
        det = NAN;
        return det;
    }
    switch (A.rows) {
        case 1:
            return A.data[0];
        case 2:
            return (A.data[0] * A.data[3] - A.data[1] * A.data[2]);
        default: {
            Matrix dop = addition(A);
            for (int j = 0; j < A.cols; j++) {
                det += A.data[j] * dop.data[j];
            }
            return det;
        }
    }
}

extern Matrix Matrix::transposition(const Matrix A) { // matrix transposition
    Matrix result (A.cols, A.rows);
    for (int i = 0; i < A.rows; i++) {
        for (int j = 0; j < A.cols; j++) {
            result.data[j * A.rows + i] = A.data[i * A.cols + j];
        }
    }
    return result;
}

Matrix::~Matrix() { // Destructor
    delete[] data;
}