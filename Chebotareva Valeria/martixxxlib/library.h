#ifndef MARTIXXXLIB_LIBRARY_H
#define MARTIXXXLIB_LIBRARY_H

#include <iostream>
#include <cstring>
using namespace std;

class Matrix {
private:
    unsigned int column = 1;
    unsigned int row = 1;
public:
    double *data;


    Matrix() {
        column = 0;
        row = 0;
        data = nullptr;
    }

    //конструктор единичной мцы
    Matrix(unsigned int column);

    //конструктор для нулевой, ну или для матрицы, чтобы заполнить одним числом все ячейки
    Matrix(unsigned int column, unsigned int row, double value);

    // конструктор копирования
    Matrix(const Matrix &m);

    //конструктор перемещения
    Matrix(Matrix&& m) noexcept;


    //обнуление матрицы
    void become_null();

    //для задания матрицы
    void set_matrix(unsigned int column, unsigned int row, double value);

    //ф-я для вывода ф-ии
    void print();

    //ф-я для следа матрицы
    double trace();

    //перегрузка операторов
    Matrix operator+(const Matrix &other);

    Matrix operator*(const Matrix &other);

    Matrix operator*(double scalar);

    Matrix operator-(const Matrix &other);
};
#endif //MARTIXXXLIB_LIBRARY_H
