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
	Matrix(int rows, int cols, int* other_matrix);
	Matrix(int rows, int cols, int type);
	Matrix(const Matrix& other_matrix);
	Matrix(Matrix&& other_matrix) noexcept;
public:
	Matrix operator +(const Matrix& other_matrix);
	Matrix operator *(const Matrix& other_matrix);
	Matrix& operator =(const Matrix& other_matrix);
	Matrix minor(int row, int col, const Matrix a);
public:
	void print();
	int trace();
	double det(const Matrix a);
	~Matrix();
};
