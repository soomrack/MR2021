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
	Matrix(int rows, int cols);
	Matrix(int rows, int cols, int type);
	Matrix(const Matrix& other_matrix);
	Matrix(Matrix&& other_matrix) noexcept;
	Matrix operator +(const Matrix& other_matrix);
	Matrix operator *(const Matrix& other_matrix);
	Matrix& operator =(const Matrix& other_matrix);
	Matrix minor(int row, int col, const Matrix a);
	void print();
	int trace();
	double det(const Matrix a);
	~Matrix();
};
