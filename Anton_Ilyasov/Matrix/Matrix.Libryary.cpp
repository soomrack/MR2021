#include <iostream> //библиотека функций для работ с матрицами
#include <string.h>
#include<math.h>
#include "Matrix.Libryary.h"
using namespace std;


Matrix::Matrix(int rows, int cols, string name)
{
	this->rows = rows;
	this->cols = cols;
	this->name = name;
	//создание динамического двумерного массива
	this->arr = new int* [rows];
	for (int i = 0; i < rows; i++)
	{
		this->arr[i] = new int[cols];
	}
}

Matrix::Matrix(const Matrix& other_matrix)	//конструктор копирования
{
	this->rows = other_matrix.rows;
	this->cols = other_matrix.cols;

	//создание динамического двумерного массива
	this->arr = new int* [rows];
	for (int i = 0; i < rows; i++)
	{
		this->arr[i] = new int[cols];
	}

	//инициализация динамического двумерного массива
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			this->arr[i][j] = other_matrix.arr[i][j];
		}
	}
}

void Matrix::Inicialization(const Matrix A) //инициализация динамического двумерного массива
{
	setlocale(LC_ALL, "ru");
	cout << "Последовательно, начиная от первого элемента, введите значения матрицы " << name << ", размером " << rows << " x " << cols << endl;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cin >> arr[i][j];
		}
	}
}

Matrix Matrix::operator +(const Matrix& B) //перегрузка оператора +
{
	if ((this->rows != B.rows) || (this->cols != B.cols))
	{
		std::cout << "Матрицы разных размеров. Как я посчитаю их сумму? :(\n";
	}

	Matrix result(this->rows, this->cols, "result");

	//инициализация динамического двумерного массива
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			result.arr[i][j] = this->arr[i][j] + B.arr[i][j];
		}
	}
	return result;
}

Matrix Matrix::operator *(const Matrix& B) //перегрузка оператора *
{
	if (this->cols != B.rows)
	{
		std::cout << "Число столбцов первой матрицы не равно числу строк второй матрицы. Как я выполню умножение? :(\n";
	}
	Matrix result(this->rows, B.cols, "result");
	//инициализация динамического двумерного массива
	for (int row = 0; row < this->rows; row++) {
		for (int col = 0; col < B.cols; col++) {
			result.arr[row][col] = 0;
			for (int i = 0; i < B.rows; i++) {
				result.arr[row][col] += this->arr[row][i] * B.arr[i][col];
			}
		}
	}
	return result;
}

Matrix& Matrix::operator =(const Matrix& other_matrix) //перегрузка оператора =
{
	this->rows = other_matrix.rows;
	this->cols = other_matrix.cols;

	for (int i = 0; i < rows; i++)
	{
		delete[] arr[i];
	}
	delete[] arr;

	//создание динамического двумерного массива
	this->arr = new int* [rows];
	for (int i = 0; i < rows; i++)
	{
		this->arr[i] = new int[cols];
	}

	//инициализация динамического двумерного массива
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			this->arr[i][j] = other_matrix.arr[i][j];
		}
	}
	return *this;
}


void Matrix::Print()
{
	cout << endl;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << arr[i][j] << ' ';
		}
		cout << "\n";
	}
}

int Matrix::Trace()
{
	setlocale(LC_ALL, "ru");
	int trace = 0;
	if (rows != cols)
	{
		cout << "Ваша матрица не квадратная. Как я Вам найду главную диагональ:( ?";
	}
	else
	{
		for (int i = 0; i < rows; i++)
		{
			trace += arr[i][i];
		}
	}
	return trace;
}


Matrix Matrix::Minor(int row, int col, const Matrix a)
{
	Matrix result(a.rows - 1, a.cols - 1, "result");

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

double Matrix::Det(const Matrix a)
{
	setlocale(LC_ALL, "ru");
	double det = 0;
	if (a.rows != a.cols)
	{
		cout << "Ваша матрица не квадратная. Как я Вам найду ее определитель:( ?";
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
			det += pow(-1, j) * a.arr[0][j] * Det(Minor(0, j, a));
		}
		return det;
	}
}

Matrix::~Matrix()
{
	for (int i = 0; i < rows; i++)
	{
		delete[] arr[i];
		arr[i] = nullptr;
	}
	delete[] arr;
	arr = nullptr;
}