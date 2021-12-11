#include <iostream>
#include <cmath>
#include <algorithm>
#include "matrix_lib.h"
using namespace std;

Matrix::Matrix(unsigned int rows, unsigned int columns) {
    this -> rows = rows;
    this -> columns = columns;
    this -> data = allocate_mem(rows, columns);
    for (unsigned int cell = 0; cell < rows * columns; cell++) {
        data[0][cell] = 0;
    }
}

Matrix::Matrix(const Matrix &other) {
    this -> rows = other.rows;
    this -> columns = other.columns;
    this -> data = allocate_mem(rows, columns);
    memcpy(this -> data[0],other.data[0],rows * columns * sizeof(double));
}

Matrix::Matrix(Matrix && other) noexcept {
    rows = other.rows;
    columns = other.columns;
    data = allocate_mem(rows, columns);
    memcpy(data[0],other.data[0],rows * columns * sizeof(double));
}

Matrix::~Matrix() {
    clear_mem(data);
}

Matrix & Matrix::operator = (const Matrix &other) {
    clear_mem(this -> data);
    this -> rows = other.rows;
    this -> columns = other.columns;
    this -> data = allocate_mem(rows, columns);
    memcpy(this -> data[0],other.data[0],rows * columns * sizeof(double));
    return *this;
}

Matrix & Matrix::operator = (Matrix &&other) noexcept {
    if (this == &other){
        return *this;
    }
    clear_mem(data);
    rows = other.rows;
    columns = other.columns;

    data = other.data;
    other.data = nullptr;
    return *this;
}

Matrix Matrix::operator + (const Matrix &other) {
    Matrix var;
    if ((this -> rows != other.rows) || (this -> columns != other.columns)) {
        return var;
    }
    var.rows = other.rows;
    var.columns = other.columns;
    var.data = allocate_mem(var.rows, var.columns);
    for (unsigned int cell = 0; cell < other.rows * other.columns; cell++) {
        var.data[0][cell] = this -> data[0][cell] + other.data[0][cell];
    }
    return var;
}

Matrix Matrix::operator - (const Matrix &other) {
    Matrix var;
    if ((this -> rows != other.rows) || (this -> columns != other.columns)) {
        return var;
    }
    var.rows = other.rows;
    var.columns = other.columns;
    var.data = allocate_mem(var.rows, var.columns);
    for (unsigned int cell = 0; cell < other.rows * other.columns; cell++) {
        var.data[0][cell] = this -> data[0][cell] - other.data[0][cell];
    }
    return var;
}

Matrix Matrix::operator * (const Matrix &other) {
    Matrix var;
    if(this -> columns != other.rows) {
        return var;
    }
    var.rows = this -> rows;
    var.columns = other.columns;
    var.data = allocate_mem(var.rows, var.columns);

    for (unsigned int row = 0; row < this -> rows; row++){
        for (unsigned int col = 0; col < other.columns; col++){
            int cell = 0;
            for (unsigned int k = 0; k < this -> columns; k++) {
                cell = cell + ((this -> data[row][k]) * other.data[k][col]);
            }
            var.data[row][col] = cell;
        }
    }
    return var;
}

unsigned int Matrix::get_rows() {
    return rows;
}

unsigned int Matrix::get_columns() {
    return columns;
}

double Matrix::get_value(unsigned int row, unsigned int column) {
    if (row > rows || column > columns) {
        return nan("");
    }
    return data[row][column];
}

//returns determinant of Matrix
double Matrix::get_det() {
    if (rows != columns) {
        return nan("");
    }
    Matrix var (rows, columns);
    memcpy(var.data[0],data[0],rows * columns * sizeof(double));
    double det = 0;
    for (unsigned int col = 0; col < var.columns - 1; col++) {
        var.sort_rows(col);
        for (unsigned int row = col+1; row < var.rows; row++) {
            if (var.data[col][col] && var.data[row][col]) {
                double k = var.data[row][col]/var.data[col][col];
                for (unsigned int l = col; l < var.columns; l++) {
                    var.data[row][l] = var.data[row][l] - (k * var.data[col][l]);
                }
            }
        }
    }
    det = 1;
    for (unsigned int row = 0; row < rows; row++) {
        det = det * var.data[row][row];
    }
    return det;
}

//prints Matrix to command line
void Matrix::print_matrix() {
    cout << "Matrix " << ":" << endl;
    for (unsigned int row = 0; row < rows; row++) {
        for (unsigned int col = 0; col < columns; col++) {
            cout << "   " << data[row][col] << "    ";
        }
        cout << "\n";
    }
}

//returns transpose matrix
Matrix Matrix::get_transpose() {
    Matrix trans(columns, rows);
    for (unsigned int row = 0; row < rows; row++) {
        for (unsigned int col = 0; col < columns; col++) {
            trans.data[row][col] = data[col][row];
        }
    }
    return trans;
}

template <unsigned int lines, unsigned int cols>
void Matrix::set_matrix(double (&arr)[lines][cols]) {
    if (lines != rows || cols != columns) {
        clear_mem(data);
        rows = lines;
        columns = cols;
        data = allocate_mem(rows, columns);
    }
    memcpy(data[0], arr[0], sizeof(arr));
}

//matrix values assigns from command line
void Matrix::set_values_cmd() {
    for (unsigned int row = 0; row < rows; row++) {
        cout << "Enter values of the " << row + 1 << " row:" << endl;
        for (unsigned int col = 0; col < columns; col++) {
            cin >> data[row][col];
        }
    }
}

//set value of defined cell
void Matrix::set_value(unsigned int row, unsigned int column, double value) {
    if (row < rows && column < columns) {
        data[row][column] = value;
    }
}

//transfer rows with zero-values in defined column to the end of vector
void Matrix::sort_rows(unsigned int col) {
    bool next_step;
    unsigned int null_counter = 0;
    for (unsigned int row = 0; row < rows; row++) {
        if (null_counter < rows - row) {
            next_step = false;
            while(next_step == false) {
                if (data[row][col] == 0) {
                    null_counter = 0;
                    for (unsigned int i = row; i < rows; i++) {
                        if (data[i][col] == 0) {
                            null_counter++;
                        }
                    }
                    if (null_counter < rows - row) {
                        double buf[columns];
                        memcpy(buf, data[row], sizeof(double) * columns);
                        for (unsigned int rem_rows = row + 1; rem_rows < rows; rem_rows++) {
                            memcpy(data[rem_rows - 1], data[rem_rows], sizeof(double) * columns);
                        }
                        memcpy(data[rows - 1], buf, sizeof(double) * columns);
                    }
                    else {
                        next_step = true;
                    }
                }
                else {
                    next_step = true;
                }
            }
        }
    }
}

double** Matrix::allocate_mem(unsigned int rows, unsigned int columns) {
    if (rows == 0 || columns == 0){
        return nullptr;
    }
    double** array = new double*[rows];
    array[0] = new double[rows * columns];
    for (int row = 1; row < rows; row++) {
        array[row] = array[row - 1] + columns;
    }
    return array;
}

void Matrix::clear_mem(double** array) {
    if (data != nullptr){
        delete[] array[0];
        delete[] array;
    }
}
