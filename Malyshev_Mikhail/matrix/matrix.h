#ifndef UNTITLED2_MATRIX_H
#define UNTITLED2_MATRIX_H

class Matrix {
private:
    unsigned int height;
    unsigned int width;
    int *data;
public:
    Matrix();
    Matrix(unsigned int height, unsigned int width); // создания матрицы заданных размеров
    Matrix(const Matrix& m); // конструктор копирования
    Matrix(Matrix&& m) noexcept; // конструктор переноса
    ~Matrix(); //деструктор
    Matrix operator +(const Matrix& m); //перегрузка +
    Matrix operator -(const Matrix& m); //перегрузка +
    Matrix operator *(const Matrix& m); //перегрузка *
    Matrix& operator =(const Matrix& m); //перегрузка =
    Matrix& operator= (Matrix &&m) noexcept;
    void set_zeros(); // заполнение нулями
    void set_unit(); // единичная матрица
    void set_values(unsigned int n_row, unsigned int n_col, int value); // заполнение одного элемента матрицы по вдресу
    void print(); //вывод матрицы на консоль
    int trace(); //вычисление следа матрицы
};

#endif //UNTITLED2_MATRIX_H
