#include <iostream> //библиотека функций для работ с матрицами
#include <string.h>
#include<math.h>
#include "Matrix.Libryary.h"
using namespace std;

Matrix::Matrix() //матрица нулевого размера
{ 
	rows = 0;
	cols = 0;
	data = nullptr;
	arr = nullptr;
}

Matrix::Matrix(int rows, int cols) //обычный конструктор с параметрами
{
	this->rows = rows;
	this->cols = cols;

	data = new int[rows * cols]; //создание последовательного динамического двумерного массива
	arr = new int* [rows];
	for (int i = 0; i < rows; i++)
	{
		arr[i] = &data[i * cols];
	}
}

Matrix::Matrix(int rows, int cols, int type) { //Конструктор единичной и нулевой матриц заданного размера
	this->rows = rows;
	this->cols = cols;

	data = new int[rows * cols]; //создание последовательного динамического двумерного массива
	arr = new int* [rows];
	for (int i = 0; i < rows; i++)
	{
		arr[i] = &data[i * cols];
	}
	
	switch (type) //заполнение единичной и нулевоц матриц
	{
	case 0: //создание нулевой матрицы
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				arr[i][j] = 0;
			}
		}
		break;

	case 1: //создание единичной матрицы
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				arr[i][j] = 0;
				arr[i][i] = 1;
			}
		}
		break;

	default:
		rows = 0;
		cols = 0;
		data = nullptr;
		arr = nullptr;
	}
}

Matrix::Matrix(const Matrix& other_matrix)	//конструктор копирования
{
	this->rows = other_matrix.rows;
	this->cols = other_matrix.cols;

	this->data = new int[rows * cols]; //создание последовательного динамического двумерного массива
	memcpy(this->data, other_matrix.data, sizeof(int) * rows * cols); //инициализация массива матрицы

	this->arr = new int* [rows];
	for (int i = 0; i < rows; i++)
	{
		this->arr[i] = &data[i * cols];
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
	if ((this->rows != other_matrix.rows) || (this->cols != other_matrix.cols))
	{
		return Matrix();
	}

	Matrix result(this->rows, this->cols);
	for (int i = 0; i < rows; i++)				 //инициализация динамического двумерного массива
	{
		for (int j = 0; j < cols; j++)
		{
			result.arr[i][j] = this->arr[i][j] + other_matrix.arr[i][j];
		}
	}
	return result;
}

Matrix Matrix::operator *(const Matrix& other_matrix) //перегрузка оператора *
{
	if (this->cols != other_matrix.rows)
	{
		return Matrix();
	}

	Matrix result(this->rows, other_matrix.cols);

	//инициализация динамического двумерного массива
	for (int row = 0; row < this->rows; row++)
	{
		for (int col = 0; col < other_matrix.cols; col++)
		{
			result.arr[row][col] = 0;
			for (int i = 0; i < other_matrix.rows; i++)
			{
				result.arr[row][col] += this->arr[row][i] * other_matrix.arr[i][col];
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

	this->rows = other_matrix.rows;
	this->cols = other_matrix.cols;

	delete[] this->data;
	delete[] this->arr;

	this->data = new int[rows * cols]; //создание последовательного динамического двумерного массива
	memcpy(this->data, other_matrix.data, sizeof(int) * rows * cols); //инициализация массива матрицы

	this->arr = new int* [rows];
	for (int i = 0; i < rows; i++)
	{
		this->arr[i] = &data[i * cols];
	}

	return *this;
}

void Matrix::print()
{
	cout << endl;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << arr[i][j] << ' ';
		}
		cout << endl;
	}
}

int Matrix::trace()
{
	int trace = 0;
	for (int i = 0; i < rows; i++)
	{
		trace += arr[i][i];
	}
	return trace;
}


Matrix Matrix::minor(int row, int col, const Matrix a)
{
	Matrix result(a.rows - 1, a.cols - 1);

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