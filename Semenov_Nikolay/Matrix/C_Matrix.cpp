#include "C_Matrix.h"
#include <iostream>
#include <cstring>

using namespace std;

/* Конструктор по умолчанию */
Matrix::Matrix(){
    this -> height = 0;
    this -> width = 0;
    data = nullptr;
}

/* Создание матрицы и выделение памяти */
Matrix::Matrix(unsigned int height, unsigned int width) {
    this->height = height;
    this->width = width;
    data = (int *) malloc(height * width * sizeof(int));
    if (!(data = (int *) malloc(height * width * sizeof(int)))) { //Проверка на выделение памяти
        this->data = 0;
        this->height = 0;
        this->width = 0;
    }
}

/* Конструктор копирования */
Matrix::Matrix(const Matrix &other) {
    this->height = other.height;
    this->width = other.width;
    this->data = (int *) malloc(height * width * sizeof(int));
    std::memcpy(this->data, other.data, width * height * sizeof(int));
    if (!(data = (int *) malloc(height * width * sizeof(int)))) { //Проверка на выделение памяти
        this->data = 0;
        this->height = 0;
        this->width = 0;
    }
}

/* Конструктор перемещения */
Matrix::Matrix(Matrix &&Matrix) noexcept {
    height = Matrix.height;
    width = Matrix.width;
    data = Matrix.data;
    Matrix.data = nullptr;
    height = 0;
    width = 0;
}

/* Деструктор */
Matrix::~Matrix(){
    delete[] data;
}

//-----

/* Перегрузка оператора сложения */
Matrix Matrix::operator + (const Matrix &other) {
    if ((this->width != other.width) || (this->height != other.height)) {
        Matrix Error(0, 0);
        return Error;
    }
    Matrix summarize(this->height, this->width);
    for (int i = 0; i < this->width * other.height; i++){
        summarize.data[i] = this->data[i] + other.data[i];
    }
    return summarize;
}

/* Перегрузка оператора вычитания */
Matrix Matrix::operator - (const Matrix &other) {
    if ((this->width != other.width) || (this->height != other.height)) {
        Matrix Error(0, 0);
        return Error;
    }
    Matrix subtraction(this->height, this->width);
    for (int i = 0; i < this->width * other.height; i++){
        subtraction.data[i] = this->data[i] - other.data[i];
    }
    return subtraction;
}

/* Перегрузка оператора умножения */
Matrix Matrix::operator * (const Matrix &other) {
    int sum = 0;
    if (this->width != other.height) {
        Matrix Error(0, 0);
        return Error;
    }
    Matrix multiplication(this->height, other.width);
    for(int row = 0; row < this->height; row++) {
        for(int col_B = 0; col_B < other.width; col_B++) {
            for(int col_A = 0; col_A < other.width; col_A++) {
                multiplication.data[width * row + col_B] += (this->data[width * row + col_A] * other.data[width * col_A + col_B]);
            }
        }
    }
    return multiplication;
}

/* След матрицы */
int Matrix::trace() {
    int tr = 0;
    for (int i = 0; i < height; i++) {
        tr += data[width * i + i];
        }
    return tr;
}

/* Расчёт определителя матрицы методом Гаусса */
double Matrix::determinant(){
    if (this->height != this->width) {
        return 0;
    }
    double det = 1.0;
    double add;
    auto **matrix_Det = new double *[height];
    for (int i = 0; i < height; ++i) {
        matrix_Det[i] = new double[width];
    }
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            matrix_Det[i][j] = (double)data[width * i + j];
        }
    }
    for (int i = 0; i < height - 1; ++i) {
        for (int j = i+1; j < width; ++j) {
            add = -(matrix_Det[j][i] / matrix_Det[i][i]);
            for (int k = 0; k < height; ++k) {
                matrix_Det[j][k] += matrix_Det[i][k] * add;
            }
        }
    }
    for (int i = 0; i < height; ++i) {
        det *= matrix_Det[i][i];
    }
    for (int i = 0; i < height; ++i) {
        delete [] matrix_Det[i];
    }
    delete [] matrix_Det;
    return det;
}

//-----

/* Создание случайной матрицы */
void Matrix::set_Random(int height, int width){
    for (int i = 0; i < height * width; i++) {
        data[i] = rand() % 10;
    }
}

/* Создание нулевой матрицы */
void Matrix::set_Zero() {
    for (int i = 0; i < height * width; i++) {
        data[i] = 0;
    }
}

/* Создание единичной матрицы */
void Matrix::set_Identity() {
    set_Zero();
    unsigned int length;
    if (width < height) {
        length = width;
    } else {
        length = height;
    }
    for(int i = 0; i < length; i++){
        data[width * i + i]= 1;
    }
}

//-----

/* Вывод матрицы на экран */
void Matrix::output() {
    for (int i = 0; i < this->width * this->height; i++) {
        std::cout << data[i] << " ";
        if ((i + 1) % this->width == 0)
            std::cout << std::endl;
    }
}