#pragma once
#include <string.h>
using namespace std;


class Matrix
{
private:
	int rows;
	int cols;
	int** arr;
	string name;

public:
	Matrix(int rows, int cols, string name); //конструктор для создания матрицы
	Matrix(const Matrix& other_matrix) ;	//конструктор копирования (А=В)
	void Inicialization(const Matrix A); //конструктор инициализации матрицы
	Matrix operator +(const Matrix& B); //перегрузка оператора +
	Matrix operator *(const Matrix& B); //перегрузка оператора *
	Matrix& operator =(const Matrix& other_matrix); //перегрузка оператора =
	void Print(); //вывод матрицы на экран
	int Trace(); //вычисление следа матрицы
	Matrix Minor(int row, int col, const Matrix a); //вычисление минора матрицы
	double Det(const Matrix a); //вычисление определителя матрицы
	~Matrix(); //деструктор матрицы для очистки 
};
	