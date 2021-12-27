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

Matrix::Matrix(int width, int height) //стандартный конструктор c параметрами
{
	this->width = width;
	this->height = height;
	data = new int[width * height];
}

Matrix::Matrix(int width, int height, int* other) //стандартный конструктор с указателем
{
	this->width = width;
	this->height = height;
	data = new int[width * height];
	memcpy(data, other, width * height * sizeof(int));
}

Matrix::Matrix(int width, int height, int type) { //Конструктор единичной и нулевой матриц
	this->width = width;
	this->height = height;
	data = new int[width * height]; 
	switch (type)
	{
	case 0: 
		for (int i = 0; i < width* height; i++)
		{
			data[i] = 0;
		}
		break;
	case 1:
		for (int i = 0; i < width * height; i++)
		{
			data[i] = 0;
			for (int i = 0; i < width; i++) {
				data[height * i + i] = 1;
			}
		}
		break;
	default:
		width = 0;
		height = 0;
		data = nullptr;
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
	this->width = other.width;
	this->height = other.height;
	this->data = new int[width * height];
	memcpy(this->data, other.data, sizeof(int) * width * height);
}

Matrix::Matrix(Matrix&& other) noexcept //Конструктор перемещения
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
	if ((this->width != other.width) || (this->height != other.height))
	{
		return Matrix();
	}
	Matrix result(this->width, this->height);
	for (int i = 0; i < height*width; i++)
	{
		result.data[i] = this->data[i] + other.data[i];
	}
	return result;
}

Matrix Matrix::operator *(const Matrix& other) //перегрузка оператора умножения
{
	if (this->height != other.width)
	{
		return Matrix();
	}
	Matrix result(this->width, other.height);
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < other.height; j++) {
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
	this->width = other.width;
	this->height = other.height;
	delete[] this->data;
	this->data = new int[width * height];
	memcpy(this->data, other.data, sizeof(int) * width * height);
	return *this;
}

int Matrix::trace()
{
	int trace = 0;
	for (int i = 0; i < this->width; i++) 
	{
		trace += this->data[height * i + i];
	}
	return trace;
}

double Matrix::minor_det(int n, int m) { //Определитель минора указанного элемента
	Matrix result((this->width) - 1, (this->height) - 1);
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
			result.data[result.height * i + j] = this->data[height * (row + i) + (j + col)];
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
		return this->data[0];
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
