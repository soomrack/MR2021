#ifndef INC_3__MATRIX_C___LIBRARY_H
#define INC_3__MATRIX_C___LIBRARY_H
#include <iostream>
#include <cstring>
#include <cstdio>

class Matrix {
private:
    int rows = 0; // строки
    int columns = 0; //столбцы
    double *data;
public:
    Matrix(); //обычная матрица +
    Matrix(int rows, int columns); //матрица с заданными размерами +
    void create(int place_in_line, int place_in_the_column, double numeric_value); //+++ок++
    Matrix(const Matrix &m); //конструктор копирования +
    Matrix(Matrix &&m) noexcept;//конструктор перемещений +
    Matrix & operator = (Matrix &&m) noexcept; //перегрузка операции присваивания
    Matrix operator + (Matrix &m); //операция сложения   +++ок++
    Matrix operator - (Matrix &m); //операция разности   +++ок++
    Matrix operator * (Matrix &m); //операция умножения---не работает---
    void zero_matrix(); //нулевая матрица   +++ок++
    void gq_matrix(); //временная матрица для поиска ошибки в моей программе +++ок++
    void unit_matrix(); //единичная матрица +++ок++
    double trace();//след матрицы           +++ок++
    int print(); //вывод матрицы в консоль  +++ок++
    ~Matrix(); //деструктор                 +++ок++
};
#endif //INC_3__MATRIX_C___LIBRARY_H