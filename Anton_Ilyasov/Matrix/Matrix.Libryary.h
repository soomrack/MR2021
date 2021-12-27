#pragma once
#include <string.h>
using namespace std;

class Matrix
{
private:
	int rows;
	int cols;
	int** arr;
	int* data;
public:
	Matrix();
	Matrix(unsigned int rows, unsigned int cols, int* other_matrix);
	Matrix(unsigned int rows, unsigned int cols, int type);
	Matrix(const Matrix& other_matrix);
	Matrix(Matrix&& other_matrix) noexcept;
public:
	Matrix operator +(const Matrix& other_matrix);
	Matrix operator -(const Matrix& other_matrix);
	Matrix operator *(const Matrix& other_matrix);
	Matrix& operator =(const Matrix& other_matrix);
	Matrix minor(unsigned int row, unsigned int col, const Matrix a);
public:
	void print();
	int trace();
	void set_zeros();
	void set_ones();
	void set_identity();
	double det(const Matrix a);
	~Matrix();
};
