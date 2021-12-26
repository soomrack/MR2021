#include "matrix_Lib.h"
#include <string.h>


Matrix::Matrix(uint height, uint width, type_of_matrix type){
    this->height = height;
    this->width = width;
    memory_allocation();
    if (data == NULL){     // TODO: Нужна ли проверка?
        return;
    }
    switch (type) {
        case ZERO: zero_matrix();
            break;
        case IDENTITY: identity_matrix();
            break;
        case NOT_INIT:
            break;
        default:
            std::cout<<"=> Ошибка инициализации!\n"
            "=> Неверно введены параметры типизированной матрицы."<<std::endl;
            free_memory();
            return;
    }
}

Matrix::Matrix(uint height, uint width, double *matrix) {
    if (matrix == NULL){     // TODO: Нужна ли проверка?
        return;
    }
    this->height = height;
    this->width = width;
    memory_allocation();
    if (data == NULL){     // TODO: Нужна ли проверка?
        return;
    }
    memcpy(data, matrix, height * width * sizeof(double));
}

Matrix::Matrix(const Matrix &matrix) {
    height = matrix.height;
    width = matrix.width;
    memory_allocation();
    if (data == NULL){     // TODO: Нужна ли проверка?
        return;
    }
    memcpy(data, matrix.data, height * width * sizeof(double));
}
Matrix::Matrix(Matrix && matrix){
    free_memory();
    height = matrix.height;
    width = matrix.width;
    data = matrix.data;
    matrix.data = nullptr;
}

Matrix::~Matrix() {
    free_memory();
}

Matrix & Matrix::operator = (const Matrix &matrix) {
    if (matrix.data == NULL){     // TODO: Нужна ли проверка?
        return *this;
    }
    if (&matrix == this) {
        return *this;
    }
    free_memory();
    width = matrix.width;
    height = matrix.height;
    memory_allocation();
    memcpy(data, matrix.data, height * width * sizeof(double));
    return *this;
}

Matrix Matrix::operator + (const Matrix &matrix) {
    if (height != matrix.height || width != matrix.width) {
        std::cout<<"=> Несоответствие размеров матриц."<<std::endl;
        Matrix empty_matrix(0,0,ZERO);
        return empty_matrix;
    }
    Matrix result_matrix(height, width, NOT_INIT);
    for (uint cell = 0; cell < height * width; cell++) {
        result_matrix.data[cell] = data[cell] + matrix.data [cell];
    }
    return result_matrix;
}


Matrix Matrix::operator * (const Matrix &matrix) {
    if (width != matrix.height) {
        std::cout<<"=> Несоответствие размеров матриц."<<std::endl;
        Matrix empty_matrix(0,0,ZERO);
        return empty_matrix;
    }
    Matrix result_matrix(height, matrix.width, ZERO);
    for (uint row = 0; row < result_matrix.height; row++) {
        for (uint col = 0; col < result_matrix.width; col++) {
            for (uint i = 0; i < width; i++) {
                uint res_cell = row * result_matrix.width + col;
                uint left_cell = i + row * width;
                uint right_cell = col + i * matrix.width;
                result_matrix.data[res_cell] +=
                data[left_cell] * matrix.data [right_cell];
            }
        }
    }
    return result_matrix;
}

double Matrix::trace() const {
    if (is_null()) {
        return 0.0;
    }
    double trace = 0.0;
    uint min;
    min = height < width ? height : width;
    for (uint i = 0; i < min; i++) {
        trace += data[i * (1 + width)];
    }
    return trace;
}

// Считает через произведения по диагоналям
double Matrix::determinant() const {
    double det = 0.0;
    if (width != height) {
        std::cout<<"=> Матрица не квадратная."<<std::endl<<std::endl;
        return det;
    }
    if (is_null()) {
        return det;
    }
    for (uint col = 0; col < width; col++) {
        double pos = 1.0;
        double neg = 1.0;
        for (uint row = 0; row < height; row++) {
            uint cell_pos = row * (width + 1) + col
                          - (row + col) / width * width;
            uint re_col = width - 1 - col;
            uint cell_neg = row * (width - 1) + col
                          + ((row + re_col) / width * width);
            pos *= data[cell_pos];
            neg *= data[cell_neg];
        }
        det += pos - neg;
    }
    return det;
}

void Matrix::print(const std::string &text) const {
    std::cout<<text<<std::endl;
    if (is_null()) {
        return;
    }
    for (uint cell = 0; cell < height * width; cell++) {
        std::cout<<data[cell]<<"\t";
        if ((cell+1) % width == 0) {
            std::cout<<std::endl;
        }
    }
    std::cout<<std::endl;
}

void Matrix::memory_allocation() {
    data = new double [height * width];
    if (data == NULL){
        std::cout<<"=> Ошибка выделения памяти!(Возможно,затребованный"
                   "размер памяти слишком большой)"<<std::endl;
        return;
    }
}

void Matrix::free_memory() {
    free(data);
    this->height = 0;
    width = 0;
}

bool Matrix::is_null() const {
    if (width == 0 || height == 0) {
        std::cout<<"=> Матрица пуста."<<std::endl<<std::endl;
        return true;
    }
    return false;
}

// TODO: Может быть, лучше использовать memset(data, 0, height * width)?
void Matrix::zero_matrix() {
    for (uint cell = 0; cell < height * width; cell++){
        data[cell] = 0.0;
    }
}

void Matrix::identity_matrix() {
    zero_matrix();
    uint min;
    min = height < width ? height : width;
    for (uint i = 0; i < min; i++) {
        data[i * (1 + width)] = 1.0;
    }
}
