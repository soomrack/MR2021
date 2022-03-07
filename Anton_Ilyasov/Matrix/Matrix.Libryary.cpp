#include <iostream> //библиотека функций для работ с матрицами
#include <string.h>
#include<math.h>
#include "Matrix.Libryary.h"
using namespace std;

Matrix::Matrix() //простой конструктор
{
	rows = 0;
	cols = 0;
	data = nullptr;
	arr = nullptr;
}

Matrix::Matrix(unsigned int rows, unsigned int cols, int* other_matrix) //матрица создается на основе исходного массива
{
	this->rows = rows;
	this->cols = cols;
	data = new int[rows * cols];
	memcpy(data, other_matrix, rows * cols * sizeof(int));
	arr = new int* [rows];
	for (int i = 0; i < rows; i++)
	{
		arr[i] = &data[i * cols];
	}
}

Matrix::Matrix(unsigned int rows, unsigned int cols, int value) //все элементы матрицы принимают значение value
{
	this->rows = rows;
	this->cols = cols;
	data = new int[rows * cols];
	for (int i = 0; i < cols * rows; i++) 
	{
		data[i] = value;
	}
	arr = new int* [rows];
	for (int i = 0; i < rows; i++)
	{
		arr[i] = &data[i * cols];
	}
}

Matrix::Matrix(unsigned int rows, unsigned int cols, MatrixType type) { //Конструктор единичной матрицы
	this->rows = rows;
	this->cols = cols;
	data = new int[rows * cols];
	arr = new int* [rows];
	for (int i = 0; i < rows; i++)
	{
		arr[i] = &data[i * cols];
	}
	switch (type)
	{
	case IDENTITY:
		set_identity();
		break;
	default:
		set(0);
		break;
	}
}

Matrix::Matrix(const Matrix& other_matrix) //конструктор копирования
{
	rows = other_matrix.rows;
	cols = other_matrix.cols;
	data = new int[rows * cols];
	memcpy(data, other_matrix.data, sizeof(int) * rows * cols);
	arr = new int* [rows];
	for (int i = 0; i < rows; i++)
	{
		arr[i] = &data[i * cols];
	}
}

Matrix::Matrix(Matrix&& other_matrix) noexcept //Конструктор перемещения
{
	rows = other_matrix.rows;
	cols = other_matrix.cols;
	data = other_matrix.data;
	arr = other_matrix.arr;
	other_matrix.rows = 0;
	other_matrix.cols = 0;
	other_matrix.data = nullptr;
	other_matrix.arr = nullptr;
}

Matrix Matrix::operator +(const Matrix& other_matrix) //перегрузка оператора +
{
	if ((rows != other_matrix.rows) || (cols != other_matrix.cols))
	{
		return Matrix();
	}
	Matrix result(rows, cols, 0);
	for (int i = 0; i < cols * rows; i++)
	{
		result.data[i] = data[i] + other_matrix.data[i];
	}
	return result;
}

Matrix Matrix::operator -(const Matrix& other_matrix) //перегрузка оператора -
{
	if ((rows != other_matrix.rows) || (cols != other_matrix.cols))
	{
		return Matrix();
	}
	Matrix result(rows, cols, 0);
	for (int i = 0; i < cols * rows; i++)
	{
		result.data[i] = data[i] - other_matrix.data[i];
	}
	return result;
}

Matrix Matrix::operator *(const Matrix& other_matrix) //перегрузка оператора *
{
	if (cols != other_matrix.rows)
	{
		return Matrix();
	}
	Matrix result(rows, other_matrix.cols, 0);
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < other_matrix.cols; col++)
		{
			result.arr[row][col] = 0;
			for (int i = 0; i < other_matrix.rows; i++)
			{
				result.arr[row][col] += arr[row][i] * other_matrix.arr[i][col];
			}
		}
	}
	return result;
}

Matrix& Matrix::operator =(const Matrix& other_matrix) //перегрузка оператора присваивания 
{
	if (&other_matrix == this)
	{
		return *this;
	}
	rows = other_matrix.rows;
	cols = other_matrix.cols;
	delete[] data;
	delete[] arr;
	data = new int[rows * cols];
	memcpy(data, other_matrix.data, sizeof(int) * rows * cols);
	arr = new int* [rows];
	for (int i = 0; i < rows; i++)
	{
		arr[i] = &data[i * cols];
	}
	return *this;
}

void Matrix::print()
{
	for (int i = 0; i < rows * cols; i++)
	{
		cout << data[i] << ' ';
		if ((i + 1) % cols == 0)
		{
			cout << endl;
		}
	}
}

void Matrix::set(int value) //все элементы матрицы принимают значение value
{
	for (int i = 0; i < cols * rows; i++) 
	{
		data[i] = value;
	}
}


void Matrix::set_identity() //единичная матрица из исходной
{
	set(0);
	for (int i = 0; i < std::min(cols, rows); i++)
	{
		arr[i][i] = 1;
	}
}

int Matrix::trace()
{
	int trace = 0;
	for (int i = 0; i < std::min(cols, rows); i++) 
	{
		trace += arr[i][i];
	}
	return trace;
}

Matrix Matrix::minor(unsigned int row, unsigned int col, const Matrix a)
{
	Matrix result(a.rows - 1, a.cols - 1, 0);
	int offsetRow = 0; //Смещение индекса строки в матрице
	int offsetCol = 0; //Смещение индекса столбца в матрице
	for (int i = 0; i < result.rows; i++)
	{
		//Пропустить row-ую строку
		if (i == row)
		{
			offsetRow = 1; //Как только встретили строку, которую надо пропустить, делаем смещение для исходной матрицы
		}
		offsetCol = 0; //Обнулить смещение столбца
		for (int j = 0; j < result.cols; j++)
		{
			//Пропустить col-ый столбец
			if (j == col)
			{
				offsetCol = 1; //Встретили нужный столбец, проускаем его смещением
			}
			result.arr[i][j] = a.arr[i + offsetRow][j + offsetCol];
		}
	}
	return result;
}

double Matrix::det(const Matrix a)
{
	double tempdet = 0.;
	if (a.rows != a.cols)
	{
		return -1.;
	}
	switch (a.rows)
	{
	case 1:
		return a.arr[0][0];
	case 2:
		return a.arr[0][0] * a.arr[1][1] - a.arr[1][0] * a.arr[0][1];
	default:
		for (int j = 0; j < a.cols; j++)
		{
			tempdet += pow(-1, j) * a.arr[0][j] * det(minor(0, j, a));
		}
		return tempdet;
	}
}

Matrix::~Matrix()
{
	delete[] data;
	delete[] arr;
	data = nullptr;
	arr = nullptr;
}