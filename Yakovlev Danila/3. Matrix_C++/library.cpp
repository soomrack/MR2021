#include "library.h"

Matrix:: Matrix() { //матрица
        this -> rows = rows;
        this -> columns = columns;
        data = new double [rows * columns];
}
Matrix:: Matrix(int rows, int columns) { //матрица с заданными размерами
        this -> rows = rows;
        this -> columns = columns;
        data = new double [rows * columns];
}
Matrix:: Matrix(const Matrix &m) { //конструктор копирования
        rows = m.rows;
        columns = m.columns;
        data = new double [rows * columns];
        memcpy(data, m.data,sizeof(double)* rows * columns);
}
void Matrix:: create(int place_in_line, int place_in_the_column, double numeric_value) {
    data[place_in_line*columns + place_in_the_column] = numeric_value;
}
Matrix &Matrix::operator=(Matrix &&m) noexcept{//перегрузка операции присваивания
    rows = m.rows;
    columns = m.columns;
    free (data);
    data = new double [rows * columns];
    memcpy(data, m.data,sizeof(double)* rows * columns);
    return *this;
}
Matrix Matrix:: operator + (Matrix &m) { //операция сложения
        Matrix res(rows, columns);
        for (int i = 0; i < rows * columns; i++)
            res.data[i] = data[i] + m.data[i];
        return res;
}
Matrix Matrix:: operator - (Matrix &m) { //операция разности
        Matrix res(rows, columns);
        for (int i = 0; i < rows * columns; i++) {
            res.data[i] = data[i] - m.data[i];
        }
        return res;
}
Matrix Matrix:: operator * (Matrix &m) { //операция умножения
        Matrix res(rows, m.columns);
        for (int i = 0; i < rows*m.columns; i++) { //это для результата
            res.data[i]=0;
            for (int ii = 0; ii < rows; ii++) {//строки исходных матриц
                for (int jj = 0; jj < m.columns; jj++) {//столбцы исходных матриц
                    if (((i+1)%(m.columns+1)==jj)&&((i+1)/(m.columns+1)==ii)) {
                        res.data[i] = res.data[i] + data[ii] * m.data[jj]; // столбцы (i+1)%(m.columns+1)==jj строки (i+1)/(m.columns+1)==ii
                    }
                }
            }
        }
        return res;
}//----------------------------
Matrix:: Matrix (Matrix &&m) noexcept{ //конструктор перемещений
    rows = m.rows;
    columns = m.columns;
    data = m.data;
}
void Matrix:: zero_matrix() { //нулевая матрица
        for (int i = 0; i < rows * columns; i++)
            data[i] = 0;
}
void Matrix:: gq_matrix(){ //временная матрица для поиска ошибки в моей программе
    data[0] = 0;
    for (int i = 1; i < rows * columns; i++)
        data[i] = data[i-1]+1;
}
void Matrix:: unit_matrix() { //единичная матрица
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                if (i==j) {
                    data[i*columns+j] = 1;
                }
                else {
                    data[i*columns+j] = 0;
                }
            }
        }
}
double Matrix:: trace(){ //след матрицы
    double trace=0.0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (i==j) {
                trace = trace+data[i*columns+j];
            }
        }
    }
    return trace;
}
int Matrix:: print() {//вывод матрицы в консоль
    printf("Matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%.3lf\t",data[i*columns+j]);
        }
        printf("\n");
    }
    return 0;
}
Matrix:: ~Matrix() { //деструктор
        free (data);
}




