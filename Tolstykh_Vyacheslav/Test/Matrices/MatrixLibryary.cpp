#include <iostream>
#include <string.h>
#include<math.h>
#include "MatrixLibryary.h"
using namespace std;

Matrix::Matrix() //простой конструктор создает матрицу нулевой длины
{
	width = 0;
	height = 0;
	data = nullptr;
}

Matrix::Matrix(unsigned int width, unsigned int height) //стандартный конструктор c параметрами
{
	this->width = width;
	this->height = height;
	data = new int[width * height];
}

Matrix::Matrix(unsigned int width, unsigned int height, int* other) //стандартный конструктор с указателем
{
	this->width = width;
	this->height = height;
	data = new int[width * height];
	memcpy(data, other, width * height * sizeof(int));
}

Matrix::Matrix(unsigned int width, unsigned int height, MatrixType type) { //Конструктор единичной и нулевой матриц
	switch (type)
	{
	case ZERO:
		this->width = width;
		this->height = height;
		data = new int[width * height];
		void set_zero();
		break;
	case IDENTITY:
		this->width = width;
		this->height = height;
		data = new int[width * height];
		void set_identity();
		break;
	default:
		data = nullptr;
		width = 0;
		height = 0;
	}
}

void Matrix::set_zero()
{
	for (int i = 0; i < width * height; i++)
	{
		data[i] = 0;
	}
}

void Matrix::set_identity()
{
	set_zero();
	for (int i = 0; i < std::min(width, height); i++)
	{
		data[height * i + i] = 1;
	}
}

void Matrix::print() //вывод на экран
{
	for (int i = 0; i < width * height; i++)
	{
		cout<<data[i];
		if ((i + 1) % height == 0)
		{
			cout << endl;
		}
	}
}

Matrix::Matrix(const Matrix& other) //конструктор копирования
{
	width = other.width;
	height = other.height;
	data = new int[width * height];
	memcpy(data, other.data, sizeof(int) * width * height);
}

Matrix::Matrix(Matrix&& other) noexcept //Конструктор перемещения (переноса)
{
	width = other.width;
	height = other.height;
	data = other.data;
	other.width = 0;
	other.height = 0;
	other.data = nullptr;
}

Matrix Matrix::operator +(const Matrix& other) //перегрузка оператора сложения
{
	if ((width != other.width) || (height != other.height))
	{
		return Matrix();
	}
	Matrix result(width, height);
	for (int i = 0; i < height*width; i++)
	{
		result.data[i] = data[i] + other.data[i];
	}
	return result;
}

Matrix Matrix::operator -(const Matrix& other) //перегрузка оператора вычитания
{
	if ((width != other.width) || (height != other.height))
	{
		return Matrix();
	}
	Matrix result(width, height);
	for (int i = 0; i < height * width; i++)
	{
		result.data[i] = data[i] - other.data[i];
	}
	return result;
}

Matrix Matrix::operator *(const Matrix& other) //перегрузка оператора умножения
{
	if (height != other.width)
	{
		return Matrix();
	}
	Matrix result(width, other.height);
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < other.height; j++) {
			result.data[i * other.height + j] = 0;
			for (int k = 0; k < height; k++) {
				result.data[i * other.height + j] += (data[height * i + k] * result.data[k * other.height + j]);
			}
		}
	}
	return result;
}

Matrix& Matrix::operator =(const Matrix& other) //перегрузка оператора присваивания 
{
	if (&other == this) return *this;
	width = other.width;
	height = other.height;
	delete[] data;
	data = new int[width * height];
	memcpy(data, other.data, sizeof(int) * width * height);
	return *this;
}

int Matrix::trace()
{
	int tr = 0;
	for (int i = 0; i < std::min(height, width); i++){
		tr += data[height * i + i];
	}
	return tr;
}

double Matrix::minor_det(unsigned int n, unsigned int m) { //Определитель минора указанного элемента
	Matrix result((width) - 1, (height) - 1);
	int row = 0;
	int col = 0;
	for (int i = 0; i < result.width; i++) {
		if (i == n) {
			row++;
		}
		for (int j = 0; j < result.height; j++) {
			if (j == m) {
				col++;
			}
			result.data[result.height * i + j] = data[height * (row + i) + (j + col)];
		}
		col = 0;
	}
	return result.det();
}

double Matrix::det() {
	if (width != height) { //Неквадратная
		return -1.;
	}
	if (width == 1) { //С одним элементом
		return data[0];
	}
	if (width == 2) { // 2 на 2
		return (data[0] * data[3]) - (data[2] * data[1]);
	}
	//Остальные виды матриц через алгебраическое дополнение
	int determinant = 0;
	for (int i = 0; i < height; i++) {
		determinant = determinant + pow(-1, i + 2) * data[i] * minor_det(0, i);
	}
	return determinant;
}

Matrix::~Matrix()
{
	delete[] data;
	data = nullptr;
}
