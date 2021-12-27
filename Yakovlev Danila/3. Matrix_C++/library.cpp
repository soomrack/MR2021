#include "library.h"

Matrix:: Matrix() { //матрица
        rows = rows=0;
        columns = columns=0;
        data = new double [rows * columns];
}

Matrix:: Matrix(int rows, int columns) { //матрица с заданными размерами
        rows = rows;
        columns = columns;
        data = new double [rows * columns];
}

Matrix:: Matrix(const Matrix &m) { //конструктор копирования
        rows = m.rows;
        columns = m.columns;
        data = new double [rows * columns];
        memcpy(data, m.data,sizeof(double)* rows * columns);
}

void Matrix:: create(int place_in_line,int place_in_the_column, double numeric_value) {//создание матрицы - присваивание значения
    if ((place_in_line<0)||(place_in_the_column<0)){
        printf("Error");
    }
    else{
        data[place_in_line*columns + place_in_the_column] = numeric_value;
    }
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
    if ((rows!=m.rows)||(columns!=m.columns)){
        printf("Error. Матрицы не равны по размерам");
    }
    else{
        Matrix res(rows, columns);
        for (int i = 0; i < rows * columns; i++)
            res.data[i] = data[i] + m.data[i];
        return res;
    }
}

Matrix Matrix:: operator - (Matrix &m) { //операция разности
    if ((rows!=m.rows)||(columns!=m.columns)){
        printf("Error. Матрицы не равны по размерам");
    }
    else{
        Matrix res(rows, columns);
        for (int i = 0; i < rows * columns; i++) {
            res.data[i] = data[i] - m.data[i];
        }
        return res;
    }
}

Matrix Matrix:: operator * (Matrix &m) { //операция умножения
    if (rows!=m.columns){
        printf("Error. Число строк в первой матрице не равно столбцам второй матрицы");
    }
    else{
        Matrix res2(rows, m.columns);
                for (int i = 0; i < rows*m.columns; i++) {
                    res2.data[i]=0;
                    for (int j = 0; j < m.columns; j++) {//(i+1)%(m.columns)==jj && ((i+1)%(rows)==(ii)
                    res2.data[i] = res2.data[i] + data[(i/rows)*m.columns+j] * m.data[(i%m.columns)+j*m.columns];
                    /*
                     * data[(i/rows)*m.columns+j] - идем по строке. целочисленное деление на длинну строки(=колво столбцов), чтобы, прибавив строку, получить
                     * на какой мы строке и передвижение по строке уже с помощью +j
                     *
                     * m.data[(i%m.columns)+j*m.columns] - идем по столбцу. остаток от деления на столбец покажет на каком мы столбце и дальше
                     * передвигаемся вдоль него прибавляя при каждом переходе длину строки(=колво столбцов)
                     */
                    printf("%.0f*%.0f + ",data[(i%rows)*m.columns+j],m.data[(i%m.columns)+j*m.columns]);
                }
                    printf("*\n");
            }
        return res2;
    }
}

Matrix:: Matrix (Matrix &&m) noexcept{ //конструктор перемещений
    rows = m.rows;
    columns = m.columns;
    data = m.data;
}

void Matrix:: zero_matrix() { //нулевая матрица
        for (int i = 0; i < rows * columns; i++)
            data[i] = 0;
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
    if ((rows!=0)&&(columns!=0)){
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                if (i==j) {
                    trace = trace+data[i*columns+j];
                }
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




