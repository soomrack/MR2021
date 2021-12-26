#ifndef UNTITLED2_MATRIX_H
#define UNTITLED2_MATRIX_H

class Matrix {
private:
    int height = 0;
    int width = 0;
    int *data;
public:
    Matrix(int height, int width); // ввод заданной матрицы
    Matrix(const Matrix& m); // конструктор копирования
    ~Matrix(); //деструктор
    Matrix operator +(const Matrix& m); //перегрузка +
    Matrix operator -(const Matrix& m); //перегрузка +
    Matrix operator *(const Matrix& m); //перегрузка *
    Matrix& operator =(const Matrix& m); //перегрузка =
    void set_unit(); // единичная матрица
    void set_values(int n_row, int n_col, int value); // заполнение одного элемента матрицы
    void print(); //вывод матрицы на консоль
    int trace(); //вычисление следа матрицы
};

#endif //UNTITLED2_MATRIX_H
