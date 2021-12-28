#include "library.h"

Matrix:: Matrix() { //матрица по умолчанию
    this -> rows = rows=0;
    this -> columns = columns=0;
    data = nullptr;
}

Matrix:: Matrix(unsigned int rows,unsigned  int columns) { //матрица с заданными размерами
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

void Matrix:: set_value(unsigned int place_in_line,unsigned int place_in_the_column, double numeric_value) {//создание матрицы - присваивание значения
    data[place_in_line*columns + place_in_the_column] = numeric_value;
}

Matrix &Matrix::operator = (Matrix &&m) noexcept{//перегрузка операции присваивания
    rows = m.rows;
    columns = m.columns;
    free (data);
    data = new double [rows * columns];
    memcpy(data, m.data,sizeof(double)* rows * columns);
    return *this;
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

Matrix:: Matrix (Matrix &&m) noexcept{ //конструктор перемещений
    rows = m.rows;
    columns = m.columns;
    data = m.data;
    m.rows=0;
    m.columns=0;
    m.data=nullptr;
}

void Matrix:: zero_matrix() { //нулевая матрица
    for (int i = 0; i < rows * columns; i++)
        data[i] = 0;
}

void Matrix:: unit_matrix() { //единичная матрица
    for (int i = 0; i < rows * columns; i++){
        if ((i/columns)==(i%columns)){ //номер строки = номеру столбца
            data[i] = 1;
        }
        else{
            data[i] = 0;
        }
    }
}

double Matrix:: trace(){ //след матрицы
    double trace=0.0;
    for (int i = 0; i < rows * columns; i++){
        if ((i/rows)==(i%columns)){
            trace = trace+data[i];
        }
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
        free (data);
}




