#include "matrix_lib.h"

Matrix::Matrix(unsigned int height, unsigned int width) {
    memory_allocation(height, width);
    this->height = height;
    this->width = width;
    for (unsigned int cell = 0; cell < height * width; cell++) {
        data_1[cell] = 0.0;
    }
}

/* Конструктор копирования */
Matrix::Matrix(const Matrix &matrix) {
    memory_allocation(height, width);
    height = matrix.height;
    width = matrix.width;
    memcpy(data_1, matrix.data_1, height * width * sizeof(double));
}

/* Конструктор перемещения */
Matrix::Matrix(Matrix &&matrix) noexcept {
    height = matrix.height;
    width = matrix.width;

    data_1 = matrix.data_1;
    data_2 = matrix.data_2;

    matrix.data_1 = nullptr;
    matrix.data_2 = nullptr;
}

/* Деструктор */
Matrix::~Matrix() {
    memory_clearing();
}

/* Перегрузка оператора присвоения (копирование) */
Matrix &Matrix::operator=(const Matrix &matrix) {
    if (&matrix == this) return *this;
    memory_clearing();
    memory_allocation(height, width);
    height = matrix.height;
    width = matrix.width;
    memcpy(data_1, matrix.data_1, height * width * sizeof(double));
    return *this;
}

/* Перегрузка оператора присвоения (перемещение) */
Matrix &Matrix::operator=(Matrix &&matrix) noexcept {
    if (&matrix == this) return *this;
    memory_clearing();

    height = matrix.height;
    width = matrix.width;

    data_1 = matrix.data_1;
    data_2 = matrix.data_2;

    matrix.data_1 = nullptr;
    matrix.data_2 = nullptr;
    return *this;
}

/* Перегрузка оператора сложения */
Matrix Matrix::operator+(const Matrix &matrix) {
    if ((this->height != matrix.height) || (this->width != matrix.width)) {
        return Matrix(0, 0);
    }

    Matrix res(this->height, this->width);
    for (unsigned int cell = 0; cell < height * width; cell++) {
        res.data_1[cell] = data_1[cell] + matrix.data_1[cell];
    }
    return res;
}

/* Перегрузка оператора вычитания */
Matrix Matrix::operator-(const Matrix &matrix) {
    if ((this->height != matrix.height) || (this->width != matrix.width)) {
        return Matrix(0, 0);
    }

    Matrix res(this->height, this->width);
    for (unsigned int cell = 0; cell < height * width; cell++) {
        res.data_1[cell] = data_1[cell] - matrix.data_1[cell];
    }
    return res;
}

/* Перегрузка оператора умножения */
Matrix Matrix::operator*(const Matrix &matrix) {
    if (this->width != matrix.height) {
        return Matrix(0, 0);
    }
    Matrix res(this->height, matrix.width);
    for (int row = 0; row < this->height; row++) {
        for (int col = 0; col < matrix.width; col++) {
            res.data_2[row][col] = 0.0;
            for (int k = 0; k < matrix.height; k++) {
                res.data_2[row][col] += this->data_2[row][k] * matrix.data_2[k][col];
            }
        }
    }
    return res;
}

/* Вывод матрицы на экран */
void Matrix::print() {
    for (int row = 0; row < height; row++) {
        std::cout << std::endl;
        if (row == 0) std::cout << "[ ";
        else std::cout << "  ";
        for (int col = 0; col < width; col++) {
            std::cout << data_2[row][col] << " ";
        }
    }
    std::cout << "]" << std::endl;
}

/***********************************СОЗДАНИЕ МАТРИЦ***********************************/

/* Создание матрице по заданному массиву */
void Matrix::set(double *array) {
    memcpy(this->data_1, array, height * width * sizeof(double));
}

/* Создание случайной матрицы */
void Matrix::random() {
    for (unsigned int cell = 0; cell < height * width; cell++) {
        data_1[cell] = rand() % 100;
    }
}

/* Создание единичной матрицы */
void Matrix::identity() {
    width = height;
    zero();
    for (unsigned int cell = 0; cell < height; cell++) {
        data_2[cell][cell] = 1.0;
    }
}

/* Создание нулевой матрицы */
void Matrix::zero() {
    for (unsigned int cell = 0; cell < height * width; cell++) {
        data_1[cell] = 0.0;
    }
}


/***********************************ОПРЕДЕЛИТЕЛЬ***********************************/

/* Расчёт определителя матрицы методом Гаусса */
double Matrix::det() {
    double det = 0.0;
    if (height != width) {
        return 0.0;
    }
    if (height == 1) {
        return data_2[0][0];
    }
    else if (height == 2) {
        return data_2[0][0] * data_2[1][1] - data_2[0][1] * data_2[1][0];
    }

    Matrix tmp(height, width);
    memcpy(tmp.data_2[0], data_2[0], height * width * sizeof(double));

    for (unsigned int col = 0; col < tmp.height - 1; col++) {
        tmp.sort_rows(col);
        for (unsigned int row = col + 1; row < tmp.height; row++) {
            if (tmp.data_2[col][col] && tmp.data_2[row][col]) {
                double k = tmp.data_2[row][col] / tmp.data_2[col][col];
                for (unsigned int l = col; l < tmp.height; l++) {
                    tmp.data_2[row][l] = tmp.data_2[row][l] - (k * tmp.data_2[col][l]);
                }
            }
        }
    }
    det = 1;
    for (unsigned int row = 0; row < height; row++) {
        det = det * tmp.data_2[row][row];
    }
    return det;
}

/* Преобразование матрицы в треугольную */
void Matrix::sort_rows(unsigned int col) {
    bool toggle = false;
    double eps=0.00001;
    unsigned int null_counter = 0;
    for (unsigned int row = 0; row < height; row++) {
        if (null_counter < height - row) {
            toggle = false;
            while (!toggle) {
                if (data_2[row][col] < eps) {
                    null_counter = 0;
                    for (unsigned int i = row; i < height; i++) {
                        if (data_2[i][col] < eps) {
                            null_counter++;
                        }
                    }
                    if (null_counter < height - row) {
                        double buf[height];
                        memcpy(buf, data_2[row], sizeof(double) * height);
                        for (unsigned int rem_rows = row + 1; rem_rows < height; rem_rows++) {
                            memcpy(data_2[rem_rows - 1], data_2[rem_rows], sizeof(double) * height);
                        }
                        memcpy(data_2[height - 1], buf, sizeof(double) * height);
                    } else {
                        toggle = true;
                    }
                } else {
                    toggle = true;
                }
            }
        }
    }
}

/* След матрицы */
double Matrix::trace() {
    double tr = 0.0;
    for (int row = 0, col = 0; row < height && col < width; row++, col++) {
        tr += data_2[row][col];
    }
    return tr;
}

/* Выделение памяти */
void Matrix::memory_allocation(unsigned int height, unsigned int width) {
    if (height == 0 || width == 0) {
        return;
    }
    data_1 = new double[height * width];
    data_2 = new double *[height];
    for (int row = 0; row < height; row++) {
        data_2[row] = &data_1[row * width];
    }
}

/* Освобождение памяти */
void Matrix::memory_clearing() {
    if (data_1 != nullptr && data_2 != nullptr) {
        delete[] data_1;
        delete[] data_2;
    }
    height = 0;
    width = 0;
}

