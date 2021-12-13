#include "matrixlib.h"
#include <iostream>
#include <iomanip>


Matrix::Matrix(int rows, int cols) { //Простой конструктор
    this -> rows = rows;
    this -> cols = cols;
    data = new double [rows * cols];
}

Matrix::Matrix(int rows, int cols, int type) { //Конструктор единичной и нулевой матрицы (type = 0; type = 1)
    this -> rows = rows;
    this -> cols = cols;
    if(cols != rows) {
        type = 1;
        cols = 3;
        cols = 3;
    }
    data = new double [rows * cols];
    switch(type){
        case 0: //создание нулевой матрицы
            for(int i = 0; i < rows; i++){
                for(int j = 0; j < cols; j++){
                    data[cols * i + j] = 0;
                }
            }
            break;
        case 1: //создание единичной матрицы
            for(int i = 0; i < rows; i++){
                for(int j = 0; j < cols; j++){
                    if(i == j) {
                        data[cols * i + j]= 1;
                    } else {
                        data[cols * i + j]= 0;
                    }
                }
            }
            break;
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
    data[cols*row + col] = element;
}

Matrix & Matrix::operator = (const Matrix &other){ //Перегрузка оператора присваивания
    this -> rows = other.rows;
    this -> cols = other.cols;
    delete[] this -> data;
    this -> data = new double [rows * cols];

    for(int i = 0; i < (rows * cols); i++) {
        this -> data[i] = other.data[i];
    }
    return *this;
}

Matrix::Matrix(const Matrix &other) { //Конструктор копирования
    this -> rows = other.rows;
    this -> cols = other.cols;
    this -> data = new double [rows * cols];
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            this -> data[cols * i + j] = other.data[cols * i + j];
        }
    }
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
    if((this->rows != other.rows)&&(this->cols != other.cols)){
        exit(1);
    }
    Matrix temp(this->rows, this->cols, 0);
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            temp.data[cols * i + j] = this -> data[cols * i + j] + other.data[cols * i + j];
        }
    }
    return temp;
}

Matrix Matrix::operator * (const Matrix &other) { //Перезагрузка оператора умножения
    //Число столбцов первой матрицы должно совпадать с числом строк второй
    if (this -> cols != other.rows) {
        exit(1);
    }
    Matrix temp(this->rows, other.cols, 0); //Число строк первой и число столбцов второй
    for(int i = 0; i < this->rows; i++) {
        for(int j = 0; j < other.cols; j++) {
            for(int k = 0; k < other.cols; k++) {
                temp.data[cols * i + j] += (this->data[cols * i + k] * other.data[cols * k + j]);
            }
        }
    }
    return temp;
}

int Matrix::tr() { //След матрицы
    int trace = 0;
    if (this -> rows != this -> cols) {
        exit(1);
    }
    for (int i = 0; i < this -> rows; i++) {
        trace += this->data[cols * i + i];
    }
    return trace;
}

double Matrix::det() { //Определитель матрицы методом Гаусса
    double determinant = 1;
    double element = 0;
    Matrix temp = *this;
    //Цикл уменьшения размера матрицы по главной диагонали
    for(int k = 0; k < (temp.cols); k++){
        //Циклы деления элементов строк на первый элемент
        for(int i = k; i < temp.cols; i++){
            element = temp.data[cols * i + k];
            if (element) {
                for (int j = k; j < temp.cols; j++) {
                    temp.data[cols * i + j] /= element;
                }
                determinant *= element;
            }
        }
        //Циклы вычитания первой строки из последующих строк
        for(int i = k+1; i < temp.cols; i++){
            if(temp.data[cols * i + k]) {
                for (int j = k; j < temp.cols; j++) {
                    temp.data[cols * i + j] -= temp.data[cols * k + j];
                }
            }
        }
    }
    return determinant;
}