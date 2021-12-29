#include <iomanip>
#include "matrix_lib.h"

void Size_error () {
    std::cout<<"ERROR: Size is incorrect\n";
};

void OutOfRange_error () {
    std::cout<<"ERROR: Your destination cell is out of range\n";
}

Matrix::Matrix(unsigned int rows_num, unsigned int columns_num, double value) {
    this->rows_num = rows_num;
    this->columns_num = columns_num;
    this->data = new double [rows_num*columns_num];
    for (unsigned long int i = 0; i < rows_num*columns_num; i++){
            data[i] = value;
    }
}

Matrix::Matrix(Matrix &income_matrix) {
    rows_num = income_matrix.rows_num;
    columns_num = income_matrix.columns_num;
    data = new double [rows_num * columns_num];
    memcpy (data, income_matrix.data, rows_num * columns_num * sizeof(double));
}

Matrix::Matrix(Matrix &&income_matrix) {
    rows_num = income_matrix.rows_num;
    columns_num = income_matrix.columns_num;
    data = income_matrix.data;
    income_matrix.data = nullptr;
    income_matrix.rows_num = 0;
    income_matrix.columns_num = 0;
}

Matrix::~Matrix() {
    delete[] data;
}

//=======================================================================

void Matrix::print () {
    for(unsigned int i = 0; i < rows_num; i++){
        for(unsigned int j = 0; j < columns_num; j++){
            std::cout<<std::fixed<<std::setprecision(3)<<"  "
            <<data[i * rows_num +j];
        }
        std::cout<<"\n";
    }
    std::cout<<"\n";
}

void Matrix::set_zero_matrix() {
    for (unsigned long int i = 0; rows_num * columns_num> i; i++){
                data[i] = 0.0;
    }
}

void Matrix::set_cell(unsigned int row, unsigned int column, double value) {
    if (row > rows_num && column > columns_num) {
        OutOfRange_error();
    }
    data[row * rows_num + column] = value;
}

double Matrix::get_cell(unsigned int row, unsigned int column) {
    if (row > rows_num && column> columns_num){
        OutOfRange_error();
        return 0.0;
    }
    return data[row * rows_num + column];
}

double Matrix::diagonal_trace() {
    double temp_value = 0.0;
    unsigned int temp_border = rows_num > columns_num ? columns_num : rows_num;
    for (unsigned long int i = 0; i < temp_border; i++){
        temp_value+= data[i * rows_num + i];
    }
    return temp_value;
}

void Matrix::diagonal_filling(double value) {
    unsigned int min = rows_num > columns_num ? columns_num : rows_num;
    for (unsigned long int i = 0; i < min; i++) {
        data[i * rows_num + i] = value;
    }
}

double Matrix::det() {
    if (rows_num != columns_num){
        Size_error();
        return 0;
    }

    double det = 1.0;
    double add = 0.0;
    Matrix temp_M (*this);

    for (unsigned int j = 0; j < rows_num - 1; ++j) {
        for (unsigned int i = j + 1; i < columns_num; ++i) {
            add = -(temp_M.data[i * rows_num + j] / temp_M.data[j * rows_num + j]);
            for (unsigned int k = 0; k < rows_num; ++k) {
                temp_M.data[i * rows_num + k] += temp_M.data[i * rows_num + k] * add;
            }
        }
    }
    for (int i = 0; i < rows_num; ++i) {
        det *= temp_M.data[i * rows_num + i];
    }
    return det;
}

void Matrix::set_identity () { //Turns matrix into E
    set_zero_matrix();
    diagonal_filling(1.0);
}

void Matrix::set_reverse() { //Matrix * Reverse_Matrix = E_Matrix
    double temp;
    Matrix E_matrix(*this);
    E_matrix.set_identity();

    for (unsigned int k = 0; k < rows_num; k++) {
        temp = data[k * rows_num + k];
        for (unsigned int j = 0; j < rows_num; j++) {
            data[k * rows_num + j] /= temp;
            E_matrix.data[k * rows_num + j] /= temp;
        }
        for (unsigned int i = k + 1; i < rows_num; i++) {
            temp = this->data[i * rows_num + k];
            for (unsigned int j = 0; j < rows_num; j++) {
                data[i * rows_num + j] -= data[k * rows_num + j] * temp;
                E_matrix.data[i * rows_num + j] -= E_matrix.data[k * rows_num + j] * temp;
            }
        }
    }
    for (unsigned int k = rows_num - 1; k > 0; k--) {
        for (unsigned int i = k - 1; i >= 0; i--) {
            temp = data[i * rows_num + k];

            for (unsigned int j = 0; j < rows_num; j++) {
                data[i * rows_num + j] -= data[k * rows_num + j] * temp;
                E_matrix.data[i * rows_num + j] -= E_matrix.data[k * rows_num + j] * temp;
            }
        }
    }

    for (unsigned int i = 0; i < rows_num; i++) {
        for (unsigned int j = 0; j < rows_num; j++) {
            data[i * rows_num + j] = E_matrix.data[i * rows_num + j];
        }
    }
}

Matrix Matrix::operator= (const Matrix &other){
    if (&other == this) {
        return *this;
    }
    rows_num = other.rows_num;
    columns_num = other.columns_num;
    delete [] data;
    data = new double [rows_num * columns_num];
    memcpy(data, other.data, rows_num * columns_num * sizeof(double));
    return *this;
}

Matrix Matrix::operator= (Matrix &&other) {
    rows_num = other.rows_num;
    columns_num = other.columns_num;
    delete [] data;
    data = new double [rows_num * columns_num];
    data = other.data;
    delete [] other.data;
    other.rows_num = 0;
    other.columns_num = 0;
    return *this;
}

Matrix Matrix::operator+ (const Matrix &other) {
    if (rows_num != other.rows_num || columns_num != other.columns_num) {
        Size_error();
        Matrix Zero(0,0,0.0);
        return Zero;
    }
    Matrix temp_M(rows_num, other.columns_num, 0.0);
    for (int i = 0; i < temp_M.rows_num * temp_M.columns_num; ++i) {
            temp_M.data[i] = data[i* temp_M.rows_num] + other.data[i * temp_M.columns_num];
    }
    return temp_M;
}

Matrix Matrix::operator- (const Matrix &other) {
    if (rows_num != other.rows_num || columns_num != other.columns_num) {
        Size_error();
        Matrix Zero(0,0,0.0);
        return Zero;
    }
    Matrix temp_M(rows_num, other.columns_num, 0.0);
    for (unsigned long int i = 0; i < temp_M.rows_num * temp_M.columns_num; ++i) {
        temp_M.data[i] = data[i* temp_M.rows_num] - other.data[i * temp_M.columns_num];
    }
    return temp_M;
}

Matrix Matrix::operator* (const Matrix &other) {
    if (columns_num != other.rows_num) {
        Size_error();
        Matrix Zero(0,0,0.0);
        return Zero;
    }
    Matrix temp_M(rows_num, other.columns_num, 0.0);
    for (unsigned int i = 0; i < this->rows_num; ++i) {
        for (unsigned int j = 0; j < this->columns_num; ++j) {
            for (unsigned int k = 0; k < this->columns_num; ++k) {
                temp_M.data[i * rows_num + j] += data[k * rows_num + i] * other.data[j * rows_num + k];
            }
        }
    }
    return temp_M;
}