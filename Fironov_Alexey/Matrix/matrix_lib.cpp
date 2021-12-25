#include <iomanip>
#include "matrix_lib.h"

void Error_output () {
    std::cout<<"Size error\n";
};

Matrix::Matrix(unsigned int rows_num, unsigned int columns_num) {
    Matrix::rows_num = rows_num;
    Matrix::columns_num = columns_num;
    Matrix::data = new double *[rows_num];
        for (int i = 0; i < rows_num; i++){
            this->data[i] = new double [columns_num];
            for (int j = 0; j < columns_num; j++){
                data[i][j] = 0.0;
            }
        }
}

Matrix::Matrix(Matrix &income_matrix) {
    this->rows_num = income_matrix.rows_num;
    this->columns_num = income_matrix.columns_num;
    this->data = new double *[income_matrix.rows_num];
    for (int i = 0; i < this->rows_num; i++){
        this->data[i] = new double [income_matrix.columns_num];
        for (int j = 0; j < this->columns_num; j++){
            this->data[i][j]=income_matrix.data[i][j];
        }
    }
}

Matrix::~Matrix() {
    delete[] data;
    data = nullptr;
}

//=======================================================================

void Matrix::visual () {
    for(int i = 0; i < Matrix::rows_num; i++){
        for(int j = 0; j < Matrix::columns_num; j++){
            std::cout<<std::fixed<<std::setprecision(3)<<"  "
            <<this->data[i][j];
        }
        std::cout<<"\n";
    }
    std::cout<<"\n";
}

void Matrix::get_zero_matrix() {
        for (unsigned i = 0; this->rows_num > i; i++){
            for (unsigned j = 0; this->columns_num > j; j++){
                this->data[i][j] = 0.0;
            }
    }
}

void Matrix::set_cell(unsigned int row, unsigned int column, double value) {
    this->data[row-1][column-1] = value;
}

double Matrix::get_cell(unsigned int row, unsigned int column) {
    return this->data[row-1][column-1];
}

double Matrix::diagonal_trace() {
    double temp_value = 0;
    unsigned int temp_border = 0;
    if (this->rows_num < this->columns_num) //It helps us to trace non-square matrices
    {
        temp_border = this->rows_num;
    } else {
        temp_border = this->columns_num;
    }
    for (unsigned int i = 0; i < temp_border; i++){
        temp_value+= this->data[i][i];
    }
    return temp_value;
}

void Matrix::diagonal_filling(double value) {
    unsigned int min = 0;
    if (this->rows_num > this->columns_num){
        min = this->columns_num;
    } else {
        min = this->rows_num;
    }
    for (long int i = 0; i < min; i++) {
        this->data[i][i] = value;
    }
}

double Matrix::det() {
    if (this->rows_num != this ->columns_num){
        Error_output;
        return 0;
    }

    double det = 1.0;
    double add = 0.0;
    Matrix temp_M (*this);

    for (int j = 0; j < this->rows_num - 1; ++j) {
        for (int i = j + 1; i < this->columns_num; ++i) {
            add = -(temp_M.data[i][j] / temp_M.data[j][j]);
            for (int k = 0; k < this->rows_num; ++k) {
                temp_M.data[i][k] += temp_M.data[j][k] * add;
            }
        }
    }
    for (int i = 0; i < this->rows_num; ++i) {
        det *= temp_M.data[i][i];
    }
    return det;
}

void Matrix::get_identity () { //Turns matrix into E
    this->get_zero_matrix();
    this->diagonal_filling(1.0);
}

void Matrix::get_reverse() { //Matrix * Reverse_Matrix = E_Matrix
    double temp;
    Matrix E_matrix(*this);
    E_matrix.get_identity();

    for (unsigned int k = 0; k < this->rows_num; k++) {
        temp = this->data[k][k];
        for (unsigned int j = 0; j < this->rows_num; j++) {
            this->data[k][j] /= temp;
            E_matrix.data[k][j] /= temp;
        }
        for (int i = k + 1; i < this->rows_num; i++) {
            temp = this->data[i][k];
            for (int j = 0; j < this->rows_num; j++) {
                this->data[i][j] -= this->data[k][j] * temp;
                E_matrix.data[i][j] -= E_matrix.data[k][j] * temp;
            }
        }
    }
    for (int k = this->rows_num - 1; k > 0; k--) {
        for (int i = k - 1; i >= 0; i--) {
            temp = this->data[i][k];

            for (int j = 0; j < this->rows_num; j++) {
                this->data[i][j] -= this->data[k][j] * temp;
                E_matrix.data[i][j] -= E_matrix.data[k][j] * temp;
            }
        }
    }

    for (int i = 0; i < this->rows_num; i++) {
        for (int j = 0; j < this->rows_num; j++) {
            this->data[i][j] = E_matrix.data[i][j];
        }
    }
}

Matrix Matrix::operator= (const Matrix &other){
    for (int i = 0; i < this->rows_num; ++i) {
        for (int j = 0; j < this->columns_num; ++j) {
            this->data[j][i] = other.data[j][i];
        }
    }
    return *this;
}

Matrix Matrix::operator+ (const Matrix &other) {
    Matrix temp_M(*this);
    if (this->rows_num != other.rows_num || this->columns_num != other.columns_num) {
        Error_output();
        temp_M.get_zero_matrix();
        return temp_M;
    }
    for (int i = 0; i < this->rows_num; ++i) {
        for (int j = 0; j < this->columns_num; ++j) {
            temp_M.data[i][j] = this->data[i][j] + other.data[i][j];
        }
    }
    return temp_M;
}

Matrix Matrix::operator- (const Matrix &other) {
    Matrix temp_M(*this);
    if (this->rows_num != other.rows_num || this->columns_num != other.columns_num) {
        Error_output();
        temp_M.get_zero_matrix();
        return temp_M;
    }
    for (int i = 0; i < this->rows_num; ++i) {
        for (int j = 0; j < this->columns_num; ++j) {
            temp_M.data[i][j] = this->data[i][j] - other.data[i][j];
        }
    }
    return temp_M;
}

Matrix Matrix::operator* (const Matrix &other) {
    Matrix temp_M(*this);
    if (this->rows_num != other.rows_num || this->columns_num != other.columns_num) {
        Error_output();
        temp_M.get_zero_matrix();
        return temp_M;
    }
    for (unsigned int i = 0; i < this->rows_num; ++i) {
        for (unsigned int j = 0; j < this->columns_num; ++j) {
            for (unsigned int k = 0; k < this->columns_num; ++k) {
                temp_M.data[j][i] += this->data[k][i] * other.data[j][k];
            }
        }
    }
    return temp_M;
}