#ifndef INC_3__MATRIX_C___LIBRARY_H
#define INC_3__MATRIX_C___LIBRARY_H
#include <iostream>
#include <cstring>
#include <cstdio>

class Matrix {
private:
    unsigned int rows; // строки
    unsigned int columns; //столбцы
    double *data;
public:
    Matrix(); //обычная матрица
    Matrix(unsigned int rows,unsigned int columns);//матрица с заданными размерами
    Matrix(const Matrix &m); //конструктор копирования
    Matrix(Matrix &&m) noexcept;//конструктор перемещений
    Matrix & operator = (Matrix &&m) noexcept; //приравнивание через перенос
    Matrix & operator = (const Matrix &m); //перегрузка операции присваивания
    Matrix operator + (Matrix &m); //операция сложения
    Matrix operator - (Matrix &m); //операция разности
    Matrix operator * (Matrix &m); //операция умножения
    ~Matrix(); //деструктор
public:
    void set_value(unsigned int place_in_line,unsigned  int place_in_the_column, double numeric_value); //присваивание значения
    void zero_matrix(); //нулевая матрица
    void unit_matrix(); //единичная матрица
    double trace();//след матрицы
    int print(); //вывод матрицы в консоль
};
#endif //INC_3__MATRIX_C___LIBRARY_H