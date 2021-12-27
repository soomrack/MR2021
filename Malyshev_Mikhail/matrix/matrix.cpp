#include "matrix.h"
#include <iostream>
#include <cstring>

Matrix::Matrix() { // конструктор по умолчанию
    height = 0;
    width = 0;
    data = nullptr;
};

Matrix::Matrix(unsigned int height, unsigned int width) { // инициализация матрицы
    this->height = height;
    this->width = width;
    data = (int *) malloc(height * width * sizeof(int));
    std::cout << "zero matrix has been created" << std::endl;
}

void Matrix::set_values(unsigned int n_row, unsigned int n_col, int value) { //заполнение одного элемента матрицы
    this->data[(n_row)*width+(n_col)] = value;
}

void Matrix::set_zeros() { // нулевая матрица
    for (int i = 0; i < height * width; i++) {
        data[i] = 0;
    }
}

void Matrix::set_unit() { // единичная матрица
    this->height = height;
    this->width = width;
    if (height != width) {
        std::cout << "not square matrix" << std::endl;
        return;
    }
    set_zeros();
    for (int i = 0; i < height * width; i += width + 1) {
        data[i] = 1;
    }
}

Matrix::Matrix(const Matrix &m) { // копирование
    height = m.height;
    width = m.width;
    free(data);
    data = (int *) malloc(height * width * sizeof(int));
    std::memcpy(this->data, m.data, width * height * sizeof(int));
}

Matrix::Matrix(Matrix&& m) noexcept //Конструктор перемещения
{
    height = m.height;
    width = m.width;
    data = m.data;
    m.height = 0;
    m.width = 0;
    m.data = nullptr;
}

Matrix &Matrix :: operator =(const Matrix& m) { // перегрузка =
    height = m.height;
    width = m.width;
    free(data);
    data = (int *) malloc(height * width * sizeof(int));
    std::memcpy(this->data, m.data, height * width * sizeof(int));
    return *this;
}

Matrix Matrix :: operator +(const Matrix &m){ // перегрузка +
    if ((height != m.height) || (width != m.width))
    {
        Matrix Error(0,0);
        return Error;
    }
    Matrix result(height, width);
    for (int i = 0; i < height * width; i++) {
        result.data[i] = data[i] + m.data[i];
    }
    return result;
}

Matrix Matrix :: operator -(const Matrix &m){ // перегрузка -
    if ((height != m.height) || (width != m.width))
    {
        Matrix Error(0,0);
        return Error;
    }
    Matrix result(height, width);
    for (int i = 0; i < height * width; i++) {
        result.data[i] = data[i] - m.data[i];
    }
    return result;
}

Matrix Matrix :: operator *(const Matrix& m) { //перегрузка *
    if (width != m.height){
        Matrix Error(0,0);
        return Error;
    }
    else {
        Matrix result(height, m.width);

        int element = 0;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < m.width; j++) {
                for (int k = 0; k < height; k++) {
                    element = data[width * i + k] * m.data[m.width * k + j];
                }
                result.data[i * m.width + j] += element;
            }
        }
        return result;
    }
}

Matrix::~Matrix() { // деструктор
    free(data);
}

int Matrix::trace() { // след матрицы
    int tr = 0;
    if (height != width) {
        std::cout << "not square matrix" << std::endl;
        return 0;
    }
    for (int i = 0; i < height * width; i += width + 1) {
        tr += data[i];
    }
    return tr;
}

void Matrix::print() { // вывод матрицы на экран
    std::cout << "matrix \n";
    for (int i = 0; i < (height * width); i++) {
        std::cout << data[i] << " ";
        if ((i + 1) % width == 0) {
            std::cout << "" << std::endl;
        }
    }
}