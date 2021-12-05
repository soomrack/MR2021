#include "Matrix.h"
#include <math.h>
#include <cstdlib>
#include <iostream>

double Matrix::trace(const Matrix A)
{
    double sum = 0;
    for (int i = 0; i < A.rows; i++)
    {
        sum += A.data[i*A.cols+i];
    }
    return sum;
}

Matrix Matrix::sum(const Matrix A, const Matrix B)
{
    if ((A.rows != B.rows) || (A.cols != B.cols))
    {
        std::cout << "Матрицы разных размеров\n";
        return A;
    }
    else
    {
        Matrix result = {A.rows, A.cols};
        result.data = (double *) malloc(result.rows * result.cols * sizeof(double));
        for (int i = 0; i < A.rows; i++)
        {
            for (int j = 0; j < A.cols; j++)
            {
                result.data[i*A.cols+j] = A.data[i*A.cols+j] + B.data[i*A.cols+j];
            }

        }
        return result;
    }
}

extern Matrix Matrix::transposition(const Matrix A) {
    Matrix result = {A.cols, A.rows};
    result.data = (double *) malloc(result.rows * result.cols * sizeof(double));
    for (int i = 0; i < A.rows; i++) {
        for (int j = 0; j < A.cols; j++) {
            result.data[j * A.rows + i] = A.data[i * A.cols + j];
        }
    }
    return result;
}

Matrix Matrix::Minor(int rows, int cols, const Matrix A)
        {
        Matrix result = {A.rows-1, A.cols-1};
        result.data = (double *) malloc(result.rows * result.cols * sizeof(double));
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

Matrix Matrix::add(const Matrix A)
{
    Matrix result = {A.rows, A.cols};
    result.data = (double *) malloc(result.rows * result.cols * sizeof(double));
    for (int i = 0; i < A.rows; i++)
    {
        for (int j = 0; j < A.cols; j++)
        {
            result.data[i*A.cols + j] = pow((-1), i + j) * det(Minor(i, j, A));
        }
    }
    return result;
}

double Matrix::det(const Matrix A)
{
    double D = 0;
    switch (A.rows)
    {
        case 1:
            return A.data[0];
        case 2:
            return (A.data[0] * A.data[3] - A.data[1] * A.data[2]);
        default:
        {
            Matrix Dop = add(A);
            for (int j = 0; j < A.cols; j++)
            {
                D += A.data[j] * Dop.data[j];
            }
            return D;
        }
    }
}

Matrix Matrix::mult(const Matrix A, const Matrix B)
{
    if (A.cols != B.rows)
    {
        std::cout << "Multiplication error \n";
        return A;
    }
    else
    {
        Matrix result = {A.rows, B.cols};
        result.data = (double *) malloc(result.rows * result.cols * sizeof(double));
        for (int i = 0; i < A.rows; i++)
        {
            for (int j = 0; j < B.cols; j++)
            {
                result.data[i * B.cols + j] = 0;
                for (int k = 0; k < A.cols; k++) {
                    result.data[i * B.cols + j] += A.data[i * A.cols + k] * B.data[k * B.cols + j];
                }
            }
        }
        return result;
    }
}

Matrix Matrix::mult_scalar(const double constt, const Matrix A)
{
    Matrix result = {A.rows, A.cols};
    result.data = (double *) malloc(result.rows * result.cols * sizeof(double));
    for (int i = 0; i < A.rows; i++)
    {
        for (int j = 0; j < A.cols; j++)
        {
            result.data[i * A.cols + j] = constt * A.data[i * A.cols + j];
        }
    }
    return result;
}

Matrix Matrix::single(const unsigned int size)
{
    Matrix result = {size, size};
    result.data = (double *) malloc(result.rows * result.cols * sizeof(double));
    for (int i = 0; i < result.rows; i++)
    {
        for (int j = 0; j < result.cols; j++)
        {
            if (i == j)
            {
                result.data[i * result.cols + j] = 1;
            }
            else
            {
                result.data[i * result.cols + j] = 0;
            }
        }

    }
    return result;
}

double norm (const Matrix A)
{
    double max_sum = 0;
    for (int i = 0; i < A.rows; i++)
    {
        double sum = 0;
        for (int j = 0; j < A.cols; j++)
        {
            sum += A.data[i * A.cols + j];
        }
        if (i == 0)
        {
            max_sum = sum;
        }
        if (sum > max_sum)
        {
            max_sum = sum;
        }
    }
    return max_sum;
}

Matrix all_one(const unsigned int rows, const unsigned int cols) {
    Matrix result = {rows, cols};
    result.data = (double *) malloc(result.rows * result.cols * sizeof(double));
    for (int i = 0; i < result.rows; i++) {
        for (int j = 0; j < result.cols; j++) {
            result.data[i * result.cols + j] = 1;
        }
    }
    return result;
}

Matrix Matrix::power(const Matrix A, const unsigned int power)
{
    if (power == 0)
    {
        return all_one(A.rows, A.cols);
    }
    if (power == 1)
    {
        return A;
    }
    if (A.rows != A.cols)
    {
        std::cout << "only square matrix \n";
        return A;
    }
    Matrix result = A;
    for (int i = 0; i < (power-1); i++)
    {
        result = mult(result, A);
    }
    return result;
}

double factorial (int n)
{
    if (n == 0)
    {
        return 1;
    }
    double result = 1;
    for (int i = 1; i <= n; i++)
    {
        result = result * i;
    }
    return result;
}

extern void Matrix::print(const Matrix A)
{
    std::cout << "matrix \n";
    for (int i = 0; i < (A.cols * A.rows); i++)
    {
        printf ("%5.2lf     ", A.data[i]);
        if ((i+1)%A.cols == 0)
        {
            printf("\n");
        }
    }
}
