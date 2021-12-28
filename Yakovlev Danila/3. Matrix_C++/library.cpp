#include "library.h"

Matrix:: Matrix() { //матрица по умолчанию
    this -> rows = 0;
    this -> columns = 0;
    data = nullptr;
}

Matrix:: Matrix(unsigned int rows,unsigned  int columns) { //матрица с заданными размерами
    this -> rows = rows;
    this -> columns = columns;
    data = new double [rows * columns];
}

Matrix:: Matrix(Matrix &m) { //конструктор копирования
    rows = m.rows;
    columns = m.columns;
    data = new double [rows * columns];
    memcpy(data, m.data,sizeof(double)* rows * columns);
}

Matrix:: Matrix (Matrix &&m) noexcept{ //конструктор перемещений
    rows = m.rows;
    columns = m.columns;
    data = m.data;
    m.rows=0;
    m.columns=0;
    m.data=nullptr;
}

Matrix &Matrix::operator = (Matrix &&m) noexcept{//приравнивание через перенос //****************************************
    rows = m.rows;
    columns = m.columns;
    data = m.data;
    memcpy(data, m.data,sizeof(double)* rows * columns);
    return *this;
}

Matrix &Matrix::operator = (Matrix &m){//перегрузка операции присваивания
    rows = m.rows;
    columns = m.columns;
    delete[] data;
    data = new double [rows * columns];
    memcpy(data, m.data,sizeof(double)* rows * columns);
    return *this;
}

void Matrix:: set_value(unsigned int row,unsigned int column, double numeric_value) {//присваивание значения
    if((row>rows)||(column>columns)){
        printf("Error. Going beyond the boundaries of the matrix");
    }
    else{
        data[row*columns + column] = numeric_value;
    }
}

Matrix Matrix:: operator + (Matrix &m) { //операция сложения
    if ((rows!=m.rows)||(columns!=m.columns)){
        printf("Error. The sizes of the matrices are not equal");
        return Matrix();
    }
    Matrix res(rows, columns);
    for (int i = 0; i < rows * columns; i++)
        res.data[i] = data[i] + m.data[i];
    return res;
}

Matrix Matrix:: operator - (Matrix &m) { //операция разности
    if ((rows!=m.rows)||(columns!=m.columns)){
        printf("Error. The sizes of the matrices are not equal");
        return Matrix();
    }
    Matrix res(rows, columns);
    for (int i = 0; i < rows * columns; i++) {
        res.data[i] = data[i] - m.data[i];
    }
    return res;
}

Matrix Matrix:: operator * (Matrix &m) { //операция умножения
    if (columns!=m.rows){
        printf("Error. The number of columns in the first matrix is not equal to the number of rows in the second matrix");
        return Matrix();
    }
    Matrix res2(rows, m.columns);
    for (int i = 0; i < columns*m.rows; i++) {
        res2.data[i]=0;
        for (int j = 0; j < columns; j++) {
            res2.data[i] = res2.data[i] + data[(i/columns)*columns+j] * m.data[(i%columns)+j*columns];
            /*
             * (i/columns) - номер строки множителей матрицы 1.
             * (i/columns)*m.columns+j - номер множителя матрицы 1 (движется вдоль строки матрицы 1)
             *
             *(i%m.columns) - номер столбца множителей матрицы 2.
             *(i%m.columns)+j*m.columns - номер множителя матрицы 2 (движется вдоль столбца матрицы 2)
            */
        }
    }
    return res2;
}


void Matrix:: zero_matrix() { //нулевая матрица
    for (int i = 0; i < rows * columns; i++)
        data[i] = 0.0;
}

void Matrix:: unit_matrix() { //единичная матрица
    zero_matrix();
    for (unsigned int i = 0; i < rows * columns; i=i+columns+1){
        data[i] = 1.0;
    }
}

double Matrix:: trace(){ //след матрицы
    double trace=0.0;
    for (unsigned int i = 0; i < rows * columns; i=i+columns+1){
        trace = trace+data[i];
    }
    return trace;
}

int Matrix:: print() {//вывод матрицы в консоль
    printf("\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%.3lf\t",data[i*columns+j]);
        }
        printf("\n");
    }
    return 0;
}

Matrix:: ~Matrix() { //деструктор
    delete[] data;
}