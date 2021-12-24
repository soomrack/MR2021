#include <iostream>
#include <cmath>
#include "matrix_lib.h"

using namespace std;

void Matrix::allocate_mem(unsigned int rows, unsigned int columns) {
    if (rows == 0 || columns == 0) {
        return;
    }
    try {
        data_line = new double[rows * columns];
        data = new double *[rows];
    }
    catch (bad_alloc const &) {
        delete[] data;
        delete[] data_line;
        data_line = nullptr;
        data = nullptr;
        this->rows = 0;
        this->columns = 0;
        return;
    }
    for (int row = 0; row < rows; row++) {
        data[row] = &data_line[row * columns];
    }
}

void Matrix::clear_mem() {
    delete[] data;
    delete[] data_line;
    rows = 0;
    columns = 0;
}

Matrix::Matrix(unsigned int rows, unsigned int columns, char type) {
    this->rows = rows;
    this->columns = columns;
    allocate_mem(rows, columns);
    if (data_line != nullptr) {
        switch (type) {
            case '0':
                zeros();
                break;
            case '1':
                ones();
                break;
            case 'E':
                identity();
                break;
            case 'R':
                random();
                break;
        }
    }
}

Matrix::Matrix(const Matrix &other) {
    this->rows = other.rows;
    this->columns = other.columns;
    this->allocate_mem(rows, columns);
    if (data_line != nullptr) {
        memcpy(this->data_line, other.data_line, rows * columns * sizeof(double));
    }
}

Matrix::Matrix(Matrix &&other) noexcept {
    rows = other.rows;
    columns = other.columns;
    data_line = other.data_line;
    data = other.data;
    other.data_line = nullptr;
    other.data = nullptr;
    other.rows = 0;
    other.columns = 0;
}

Matrix::~Matrix() {
    clear_mem();
}

Matrix &Matrix::operator= (const Matrix &other) {
    if (this == &other) {
        return *this;
    }
    this->clear_mem();
    this->rows = other.rows;
    this->columns = other.columns;
    this->allocate_mem(rows, columns);
    if (data_line != nullptr) {
        memcpy(this->data_line, other.data_line, rows * columns * sizeof(double));
    }
    return *this;
}

Matrix &Matrix::operator= (Matrix &&other) noexcept {
    if (this == &other) {
        return *this;
    }
    clear_mem();
    rows = other.rows;
    columns = other.columns;
    data_line = other.data_line;
    data = other.data;
    other.data_line = nullptr;
    other.data = nullptr;
    other.rows = 0;
    other.columns = 0;
    return *this;
}

Matrix Matrix::operator+ (const Matrix &other) {
    Matrix var;
    if ((this->rows != other.rows) || (this->columns != other.columns)) {
        return var;
    }
    var.rows = other.rows;
    var.columns = other.columns;
    var.allocate_mem(var.rows, var.columns);
    for (unsigned int cell = 0; cell < other.rows * other.columns; cell++) {
        var.data_line[cell] = this->data_line[cell] + other.data_line[cell];
    }
    return var;
}

Matrix Matrix::operator- (const Matrix &other) {
    Matrix var;
    if ((this->rows != other.rows) || (this->columns != other.columns)) {
        return var;
    }
    var.rows = other.rows;
    var.columns = other.columns;
    var.allocate_mem(var.rows, var.columns);
    for (unsigned int cell = 0; cell < other.rows * other.columns; cell++) {
        var.data_line[cell] = this->data_line[cell] - other.data_line[cell];
    }
    return var;
}

Matrix Matrix::operator* (const Matrix &other) {
    Matrix var;
    if (this->columns != other.rows) {
        return var;
    }
    var.rows = this->rows;
    var.columns = other.columns;
    var.allocate_mem(var.rows, var.columns);

    for (unsigned int row = 0; row < this->rows; row++) {
        for (unsigned int col = 0; col < other.columns; col++) {
            double cell = 0;
            for (unsigned int k = 0; k < this->columns; k++) {
                cell = cell + ((this->data[row][k]) * other.data[k][col]);
            }
            var.data[row][col] = cell;
        }
    }
    return var;
}

unsigned int Matrix::get_rows() { return rows; }

unsigned int Matrix::get_columns() { return columns; }

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
    Matrix var(rows, columns);
    memcpy(var.data_line, data_line, rows * columns * sizeof(double));
    for (unsigned int col = 0; col < var.columns - 1; col++) {
        var.sort_rows(col);
        for (unsigned int row = col + 1; row < var.rows; row++) {
            if (var.data[col][col] && var.data[row][col]) {
                double k = var.data[row][col] / var.data[col][col];
                for (unsigned int m = col; m < var.columns; m++) {
                    var.data[row][m] = var.data[row][m] - (k * var.data[col][m]);
                }
            }
        }
    }
    double det = 1;
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

void Matrix::set_matrix_from_1d(double* arr) {
    if (data_line != nullptr) {
        memcpy(data_line, arr, rows * columns*sizeof(double));
    }
}

template<unsigned int height, unsigned int width>
void Matrix::set_matrix_from_2d(double (&arr)[height][width]) {
    if (height != rows || width != columns) {
        clear_mem();
        rows = height;
        columns = width;
        allocate_mem(rows, columns);
    }
    if (data_line != nullptr) {
        memcpy(data_line, arr, sizeof(arr));
    }
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

//transfer down rows with zero-values in defined column
void Matrix::sort_rows(unsigned int col) {
    bool next_step;
    unsigned int null_counter = 0;
    for (unsigned int row = 0; row < rows; row++) {
        if (null_counter < rows - row) {
            next_step = false;
            while (next_step == false) {
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
                    } else {
                        next_step = true;
                    }
                } else {
                    next_step = true;
                }
            }
        }
    }
}

void Matrix::zeros() {
    for (unsigned int cell = 0; cell < rows * columns; cell++) {
        data_line[cell] = 0;
    }
}

void Matrix::ones() {
    for (unsigned int cell = 0; cell < rows * columns; cell++) {
        data_line[cell] = 1;
    }
}

void Matrix::identity() {
    for (unsigned int row = 0; row < rows; row++) {
        for (unsigned int col = 0; col < columns; col++) {
            if (row == col) {
                data[row][col] = 1;
            } else {
                data[row][col] = 0;
            }
        }
    }
}

void Matrix::random() {
    srand(time(NULL));
    for (unsigned int cell = 0; cell < rows * columns; cell++) {
        data_line[cell] = rand() % 1000;
    }
}
