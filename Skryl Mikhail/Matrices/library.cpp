#include <iostream>
#include <ctime>
#include "library.h"

Matrix::Matrix(int rows, int cols) {            //Конструктор для случайных матриц
    srand(time(NULL));
    this->rows = rows;
    this->cols = cols;
    matrix = new int *[rows];
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new int[cols];
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = rand() % 20;
        }
    }
}

Matrix::Matrix(int rows, int cols, int type){   //Конструктор для стандартных матриц (нулевая и единичная)
    this->rows = rows;
    this->cols = cols;
    matrix = new int *[rows];
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new int[cols];
    }
    if (type == 0) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                matrix[i][j] = 0;
            }
        }
    }
    else {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (i == j) {
                    matrix[i][j] = 1;
                }
                else {
                    matrix[i][j] = 0;
                }
            }
        }
    }
}

Matrix::Matrix(int rows, int cols, bool isTemp){  //Конструктор для временно создаваемого объекта при арифметических операциях
    this->rows = rows;
    this->cols = cols;
}

Matrix::~Matrix() {
    for (int i = 0; i < rows; ++i) {
        delete [] matrix[i];
    }
    delete [] matrix;
}

Matrix::Matrix(const Matrix &other) {       //Конструктор копирования
    this->rows = other.rows;
    this->cols = other.cols;
    this->matrix = new int* [rows];
    for (int i = 0; i < rows; ++i) {
        this->matrix[i] = new int[cols];
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            this->matrix[i][j] = other.matrix[i][j];
        }
    }
}

Matrix::Matrix(Matrix &&other) noexcept {       //Конструктор перемещения
    this->rows = other.rows;
    this->cols = other.cols;
    this->matrix = other.matrix;
    other.matrix = nullptr;
    other.rows = 0;
    other.cols = 0;
}

Matrix Matrix::operator - (const Matrix &other){        //Перегрузка оператора вычитания
    if ((this->rows != other.rows) || (this->cols != other.cols)) {
        std::cout << "Matrices are not equal" << std::endl;
        exit(1);
    }
    Matrix temp(this->rows, this->cols, true);
    temp.matrix = new int* [rows];
    for (int i = 0; i < rows; ++i) {
        temp.matrix[i] = new int[cols];
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            temp.matrix[i][j] = this->matrix[i][j] - other.matrix[i][j];
        }
    }
    return temp;
}

Matrix Matrix::operator + (const Matrix &other){        //Перегрузка оператора сложения
    if ((this->rows != other.rows) || (this->cols != other.cols)) {
        std::cout << "Matrices are not equal" << std::endl;
        exit(1);
    }
    Matrix temp(this->rows, this->cols, true);
    temp.matrix = new int* [rows];
    for (int i = 0; i < rows; ++i) {
        temp.matrix[i] = new int[cols];
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            temp.matrix[i][j] = this->matrix[i][j] + other.matrix[i][j];
        }
    }
    return temp;
}

Matrix & Matrix::operator = (const Matrix &other){      //Перегрузка оператора присваивания
    if (&other == this) {
        return *this;
    }
    this->rows = other.rows;
    this->cols = other.cols;
    delete [] this->matrix;
    this->matrix = new int* [rows];
    for (int i = 0; i < rows; ++i) {
        this->matrix[i] = new int[cols];
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            this->matrix[i][j] = other.matrix[i][j];
        }
    }
    return *this;
}

Matrix & Matrix::operator = (Matrix &&other) noexcept {     //Перегрузка оператора присваивания для оператора перемещения
    this->rows = other.rows;
    this->cols = other.cols;
    delete [] this->matrix;
    this->matrix = other.matrix;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            this->matrix[i][j] = other.matrix[i][j];
        }
    }
    other.matrix = nullptr;
    other.rows = 0;
    other.cols = 0;
    return *this;
}

Matrix Matrix::operator * (const Matrix &other){        //Перегрузка оператора умножения
    if (this->cols != other.rows){
        std::cout << "Matrices are not equal" << std::endl;
        exit(1);
    }
    Matrix temp(this->rows, other.cols, false);
    temp.matrix = new int* [rows];
    for (int i = 0; i < rows; ++i) {
        temp.matrix[i] = new int[cols];
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < other.cols; ++j) {
            temp.matrix[i][j] = 0;
            for (int k = 0; k < other.rows; ++k) {
                temp.matrix[i][j] += this->matrix[i][k] * other.matrix[k][j];
            }
        }
    }
    return temp;
}

int Matrix::trace() {
    int matrix_trace = 0;
    if (this->rows != this->cols) {
        std::cout << "Matrix is not square" << std::endl;
        exit(1);
    }
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->cols; ++j) {
            if (i == j) {
                matrix_trace += matrix[i][j];
            }
        }
    }
    return matrix_trace;
}

double Matrix::det(){
    if (this->rows != this->cols) {
        std::cout << "Matrix is not square" << std::endl;
        exit(1);
    }
    double det = 1.0;
    double add = 0.0;
    auto **det_matrix = new double *[rows];
    for (int i = 0; i < rows; ++i) {
        det_matrix[i] = new double[cols];
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            det_matrix[i][j] = (double)matrix[i][j];
        }
    }
    for (int i = 0; i < rows-1; ++i) {
        for (int j = i+1; j < cols; ++j) {
            add = -(det_matrix[j][i] / det_matrix[i][i]);
            for (int k = 0; k < rows; ++k) {
                det_matrix[j][k] += det_matrix[i][k] * add;
            }
        }
    }
    for (int i = 0; i < rows; ++i) {
        det *= det_matrix[i][i];
    }
    for (int i = 0; i < rows; ++i) {
        delete [] det_matrix[i];
    }
    delete [] det_matrix;
    return det;
}
void Matrix::print() {
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->cols; ++j) {
            std::cout << this->matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}
