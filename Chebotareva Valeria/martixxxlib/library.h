#ifndef MARTIXXXLIB_LIBRARY_H
#define MARTIXXXLIB_LIBRARY_H
#include <iostream>
#include <cstring>
using namespace std;
class Matrix {
private:
    unsigned int column = 1;
    unsigned int row = 1;
    double *data;
public:
    Matrix();
    Matrix(unsigned int column);//конструктор единичной мцы
    Matrix(unsigned int column, unsigned int row, double value);//конструктор для нулевой, ну или для матрицы, чтобы заполнить одним числом все ячейки
    Matrix(const Matrix &m); // конструктор копирования
    Matrix(Matrix&& m) noexcept;//конструктор перемещения
    void become_null();//обнуление матрицы
    void set_matrix(unsigned int column, unsigned int row, double value);//для задания матрицы
    void print();//ф-я для вывода ф-ии
    double trace();//ф-я для следа матрицы
    Matrix operator+(const Matrix &other);//перегрузка операторов
    Matrix operator*(const Matrix &other);
    Matrix operator*(double scalar);
    Matrix operator-(const Matrix &other);
    Matrix operator = (Matrix &&other) noexcept;
    Matrix operator = (const Matrix &other);
};
#endif //MARTIXXXLIB_LIBRARY_H
