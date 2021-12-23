#include <iostream>
#include <ctime>
#include "library.h"
#include <string.h>

using namespace std;

Matrix::Matrix(int rows, int cols, Matrix_type type) {
    this->rows = rows;
    this->cols = cols;
    memory_allocation();
    switch (type) {
        case RANDOM: random_matrix(); break;
        case IDENTITY: identity_matrix(); break;
        case ONES: ones_matrix(); break;
        case ZERO:
        default: zero_matrix(); break;
    }
}

Matrix::Matrix(){
    this->rows = 0;
    this->cols = 0;
    for (int row = 0; row < rows; ++row) {
        matrix[row] = nullptr;
    }
    matrix = nullptr;
}

Matrix::~Matrix() {
    free_memory();
}

Matrix::Matrix(const Matrix &other) {
    this->rows = other.rows;
    this->cols = other.cols;
    memory_allocation();
    for (int row = 0; row < rows; ++row) {
        memcpy(this->matrix[row],other.matrix[row],other.cols * sizeof(double));
    }
    memcpy(this->matrix,other.matrix,other.rows * sizeof(double));
}

Matrix::Matrix(Matrix &&other) noexcept {
    this->rows = other.rows;
    this->cols = other.cols;
    this->matrix = other.matrix;
    other.matrix = nullptr;
    other.rows = 0;
    other.cols = 0;
}

Matrix Matrix::operator- (const Matrix &other){
    if ((this->rows != other.rows) || (this->cols != other.cols)) {
        return Matrix();
    }
    Matrix temp(this->rows, this->cols, ZERO);
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            temp.matrix[row][col] = this->matrix[row][col] - other.matrix[row][col];
        }
    }
    return temp;
}

Matrix Matrix::operator + (const Matrix &other){        //Перегрузка оператора сложения
    if ((this->rows != other.rows) || (this->cols != other.cols)) {
        return Matrix();
    }
    Matrix temp(this->rows, this->cols, ZERO);
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            temp.matrix[row][col] = this->matrix[row][col] + other.matrix[row][col];
        }
    }
    return temp;
}

Matrix Matrix::operator * (const Matrix &other){        //Перегрузка оператора умножения
    if (this->cols != other.rows){
        return Matrix();
    }
    Matrix temp(this->rows, this->cols, ZERO);
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < other.cols; ++col) {
            temp.matrix[row][col] = 0;
            for (int k = 0; k < other.rows; ++k) {
                temp.matrix[row][col] += this->matrix[row][k] * other.matrix[k][col];
            }
        }
    }
    return temp;
}

Matrix& Matrix::operator= (const Matrix &other){      //Перегрузка оператора присваивания
    if (&other == this) {
        return *this;
    }
    this->rows = other.rows;
    this->cols = other.cols;
    free_memory();
    memory_allocation();
    for (int row = 0; row < rows; ++row) {
        memcpy(this->matrix[row],other.matrix[row],other.cols * sizeof(double));
    }
    memcpy(this->matrix,other.matrix,other.rows * sizeof(double));
    return *this;
}

Matrix & Matrix::operator= (Matrix &&other) noexcept {
    this->rows = other.rows;
    this->cols = other.cols;
    free_memory();
    this->matrix = other.matrix;
    other.matrix = nullptr;
    other.rows = 0;
    other.cols = 0;
    return *this;
}

void Matrix::random_matrix() {
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            matrix[row][col] = rand() % 10;
        }
    }
}

void Matrix::zero_matrix(){
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            matrix[row][col] = 0;
        }
    }
}

void Matrix::ones_matrix(){
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            matrix[row][col] = 1;
        }
    }
}

void Matrix::identity_matrix(){
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            if (row == col) {
                matrix[row][col] = 1;
            }
            else {
                matrix[row][col] = 0;
            }
        }
    }
}

double Matrix::trace() {
    double matrix_trace = 0.0;
    if (this->rows != this->cols) {
        Matrix();
    }
    for (int row = 0; row < this->rows; ++row) {
        matrix_trace += this->matrix[row][row];
    }
    return matrix_trace;
}

double Matrix::det(){
    if (this->rows != this->cols) {
        return 0.0;
    }
    Matrix temp(*this);
    double det = 1.0;
    double add = 0.0;
    int swap_count = 0;
    for (int row = 0; row < rows-1; ++row) {
        int max_pos = row;
        double max = abs(temp.matrix[row][row]);
        for (int j = row+1; j < rows; ++j) {
            if (abs(temp.matrix[j][row]) > max) {
                max_pos = j;
                max = abs(temp.matrix[j][row]);
            }
        }
        if (max == 0.0){
            return 0.0;
        }
        if (row != max_pos){
            swap(temp.matrix[row],temp.matrix[max_pos]);
            swap_count++;
        }
        for (int j = row + 1; j < cols; ++j) {
            add = -(temp.matrix[j][row] / temp.matrix[row][row]);
            for (int k = row; k < rows; ++k) {
                temp.matrix[j][k] += temp.matrix[row][k] * add;
            }
        }
    }
    if (swap_count %2 == 1) {
        det = -1.0;
    }
    for (int row = 0; row < rows; ++row) {
        det *= temp.matrix[row][row];
    }
    return det;
}

void Matrix::print() {
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            std::cout << this->matrix[row][col] << "\t";
        }
        std::cout << std::endl;
    }
}

void Matrix::memory_allocation() {
    matrix = new double *[rows];
    if (matrix != nullptr) {
        for (int row = 0; row < rows; ++row) {
            matrix[row] = new double[cols];
            if ((matrix[row]) == nullptr) {
                this->cols = 0;
                this->rows = 0;
            }
        }
    }
}

void Matrix::free_memory() {
    for (int row = 0; row < rows; ++row) {
        delete [] matrix[row];
    }
    delete [] matrix;
}