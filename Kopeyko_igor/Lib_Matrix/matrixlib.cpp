#include "matrixlib.h"
#include <iostream>
#include <iomanip>
#include <math.h>


Matrix::Matrix(){
    this -> rows = 0;
    this -> cols = 0;
    data = nullptr;
}

Matrix::Matrix(int rows, int cols) { //Простой конструктор
    this -> rows = rows;
    this -> cols = cols;
    data = new double [rows * cols];
}

Matrix::Matrix(int rows, int cols, int type) { //Конструктор единичной и нулевой матрицы (type = 0; type = 1)
    this -> rows = rows;
    this -> cols = cols;
    data = new double [rows * cols];
    switch(type){
        case 0: //создание нулевой матрицы
            this->set_nulls();
            break;
        case 1: //создание единичной матрицы
            this->set_ones();
            break;
        default:
            this->set_nulls();
            for(int i = 0; i < cols*rows; i++){
                data[i] = i;
            }
    }
}

void Matrix::print() { //Вывод на экран
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(j == 0) {
                std::cout <<"\n";
            }
            std::cout << std::fixed << std::setprecision(4) << "   " << data[cols * i + j];
        }
    }
    std::cout <<"\n";
}

void Matrix::set(int row, int col,double element){ //Присвоение значения элементу
    if(((row >= rows)||(row < 0)) || ((col >= cols)||(col < 0))){
        return;
    }
    data[cols*row + col] = element;
}

Matrix & Matrix::operator = (const Matrix &other){ //Перегрузка оператора присваивания
    this -> rows = other.rows;
    this -> cols = other.cols;
    delete[] this -> data;
    this -> data = new double [rows * cols];
    memcpy(this -> data, other.data,sizeof(double)* rows * cols);
    return *this;
}

Matrix::Matrix(const Matrix &other) { //Конструктор копирования
    this -> rows = other.rows;
    this -> cols = other.cols;
    this -> data = new double [rows * cols];
    memcpy(this -> data, other.data,sizeof(double)* rows * cols);
}

Matrix::~Matrix() { //Деструктор
    delete[] data;
}

Matrix::Matrix(Matrix &&other) noexcept { //Конструктор перемещения
    this -> rows = other.rows;
    this -> cols = other.cols;
    this -> data = other.data;
    other.data = nullptr;
    other.rows = 0;
    other.cols = 0;
}

Matrix & Matrix::operator = (Matrix &&other) noexcept { //Перезагрузка оператора присваивания для перемещения
    this -> rows = other.rows;
    this -> cols = other.cols;
    delete [] this -> data;
    this -> data = other.data;
    other.data = nullptr;
    other.rows = 0;
    other.cols = 0;
    return *this;
}

Matrix Matrix::operator + (const Matrix &other) { //Перезагрузка оператора сложения
    Matrix temp(this->rows, this->cols, 0);
    if((this->rows != other.rows) || (this->cols != other.cols)){ //В случае несовпадения размера вернем нулевую матрицу
        return temp;
    }
    for(int i = 0; i < rows*cols; i++){
        temp.data[i] = this -> data[i] + other.data[i];
    }
    return temp;
}

Matrix Matrix::operator * (const Matrix &other) { //Перезагрузка оператора умножения
    Matrix temp(this->rows, other.cols, 0); //Число строк первой и число столбцов второй
    //Число столбцов первой матрицы должно совпадать с числом строк второй
    if (this -> cols != other.rows) { //В случае несовпадения вернем нулевую матрицу
        return temp;
    }
    for(int i = 0; i < this->rows; i++) {
        for(int j = 0; j < other.cols; j++) {
            for(int k = 0; k < other.cols; k++) {
                temp.data[cols * i + j] += (this->data[cols * i + k] * other.data[cols * k + j]);
            }
        }
    }
    return temp;
}

void Matrix::set_nulls() {//Сделать матрицу нулевой
    for(int i = 0; i < rows*cols; i++){
        data[i] = 0.;
    }
}

void Matrix::set_ones() {//Сделать матрицу единичной
    int len = rows;
    if (cols < rows) {
        len = cols;
    }
    this->set_nulls();
    for(int i = 0; i < len; i++){
        data[cols * i + i]= 1.;
    }
}

double Matrix::tr() { //След матрицы
    double trace = 0;
    for (int i = 0; i < this -> rows; i++) {
        trace += this->data[cols * i + i];
    }
    return trace;
}

double Matrix::minor_det(int n, int m){ //Находит определитель минора указанного элемента
    Matrix temp((this -> rows) - 1, (this -> cols) - 1);
    int row = 0;
    int col = 0;
    for(int i = 0; i < temp.rows; i++){
        if (i == n) {
            row++;
        }
        for(int j = 0; j < temp.cols; j++){
            if (j == m){
                col++;
            }
            temp.data[temp.cols * i + j] = this -> data[cols*(row+i) + (j+col)];
        }
        col = 0;
    }
    return temp.det();
}

double Matrix::det() {
    if(rows != cols) { //Неквадратная
        return -1.;
    }
    if(rows == 1){ //С одним элементом
        return this -> data[0];
    }
    if(rows == 2){ // 2 на 2
        return (data[0]*data[3]) - (data[2]*data[1]);
    }
    //Остальные виды матриц через алгебраическое дополнение
    int determinant = 0;
    for (int i = 0; i < cols; i++){
        determinant = determinant + pow(-1,i+2) * data[i] * minor_det(0, i);
    }
    return determinant;
}