#include "C_Matrix.h"
#include <iostream>
using namespace std;

/* Создание матрицы и выделение памяти */
Matrix::Matrix(int height, int width) {
    if (height <= 0 || width <= 0) {
        std::cout << "\n\nERROR\nHeight|Width must be >= 1." << std::endl;
        //exit(1);
    }
    this->height = height;
    this->width = width;
    data = (int *) malloc(height * width * sizeof(int));
}

/* Конструктор копирования */
Matrix::Matrix(const Matrix &other) {
    this->height = other.height;
    this->width = other.width;
    this->data = (int *) malloc(height * width * sizeof(int));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            this->data[width * i + j] = other.data[width * i + j];
        }
    }
}

/* Конструктор перемещения */
Matrix::Matrix(Matrix &&Matrix) noexcept {
    height = Matrix.height;
    width = Matrix.width;
    data = Matrix.data;
    Matrix.data = nullptr;
}

/* Деструктор */
Matrix::~Matrix() {
    erase(data);
}

/* Освобождение памяти */
void Matrix::erase(int *data) const {
    if (height != 0 && width != 0 && data != nullptr) {
        delete[] data;
    }
}

//-----

/* Перегрузка оператора сложения */
Matrix Matrix::operator + (const Matrix &other) {
    if ((this->width != other.width) || (this->height != other.height)) {
        std::cout << "\n\nERROR\nMatrix A and B must be the same size.";
        Matrix Error(0, 0);
        return Error;
    }
    Matrix Summarize(this->height, this->width);
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            Summarize.data[height * i + j] = this->data[height * i + j] + other.data[height * i + j];
        }
    }
    Summarize.Output();
    return Summarize;
}

/* Перегрузка оператора вычитания */
Matrix Matrix::operator - (const Matrix &other) {
    if ((this->width != other.width) || (this->height != other.height)) {
        std::cout << "\n\nERROR\nMatrix A and B must be the same size.";
        Matrix Error(0, 0);
        return Error;
    }
    Matrix Subtraction(this->height, this->width);
    for (int i = 0; i < this->width; i++) {
        for (int j = 0; j < other.height; j++) {
            Subtraction.data[other.height * i + j] = this->data[other.height * i + j] - other.data[other.height * i + j];
        }
    }
    Subtraction.Output();
    return Subtraction;
}

/* Перегрузка оператора умножения */
Matrix Matrix::operator * (const Matrix &other) {
    int sum = 0;
    if (this->width != other.height) {
        std::cout << "\n\nERROR\nMatrix A and B must be commutative (columns A = height B).\n\n\n";
        Matrix Error(0, 0);
        return Error;
    }
    Matrix Multiplication(this->height, other.width);
    for (int i = 0, j = 0; i < this->height * other.width; i++) {
        for (int k = 0; k < this->width; k++)
            sum += this->data[k + j * this->width] * other.data[i - j * other.width + k * other.width];
        Multiplication.data[i] = sum;
        sum = 0;
        if ((i + 1) % (this->width + 1) == 0) j++;
    }
    Multiplication.Output();
    return Multiplication;
}

/* След матрицы */
int Matrix::Trace() {
    int trace = 0;
    if (this->height != this->width) {
        std::cout << "\n\nERROR\nMatrix is not square." << std::endl;
        exit(2);
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i==j) {
                trace += data[width * i + j];
            }
        }
    }
    return trace;
}

/* Расчёт определителя матрицы методом Гаусса */
double Matrix::Determinant(){
    if (this->height != this->width) {
        std::cout << "\n\nERROR\nMatrix is not square." << std::endl;
        exit(2);
    }
    double det = 1.0;
    double add = 0.0;
    auto **Matrix_Det = new double *[height];
    for (int i = 0; i < height; ++i) {
        Matrix_Det[i] = new double[width];
    }
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            Matrix_Det[i][j] = (double)data[width * i + j];
        }
    }
    for (int i = 0; i < height-1; ++i) {
        for (int j = i+1; j < width; ++j) {
            add = -(Matrix_Det[j][i] / Matrix_Det[i][i]);
            for (int k = 0; k < height; ++k) {
                Matrix_Det[j][k] += Matrix_Det[i][k] * add;
            }
        }
    }
    for (int i = 0; i < height; ++i) {
        det *= Matrix_Det[i][i];
    }
    for (int i = 0; i < height; ++i) {
        delete [] Matrix_Det[i];
    }
    delete [] Matrix_Det;
    return det;
}

//-----

/* Создание случайной матрицы */
void Matrix::Rand(int height, int width){
    for (int i = 0; i < height * width; i++) {
        data[i] = rand() % 10;
    }
}

/* Создание нулевой матрицы */
void Matrix::Zero() {
    for (int i = 0; i < height * width; i++) {
        data[i] = 0;
    }
}

/* Создание единичной матрицы */
void Matrix::Identity() {
    if (this->height != this->width) {
        std::cout << "Matrix is not square." << std::endl;
        exit(1);
    }
    Zero();
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i == j) {
                data[i] = 1;
            }
        }
    }
}

//-----

/* Вывод матрицы на экран */
void Matrix::Output() {
    for (int i = 0; i < this->width * this->height; i++) {
        std::cout << data[i] << " ";
        if ((i + 1) % this->width == 0)
            std::cout << std::endl;
    }
}