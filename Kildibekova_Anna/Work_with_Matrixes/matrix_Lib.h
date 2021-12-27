//
// Библиотека для работы с матрицами.
//

#ifndef WORK_WITH_MATRIXES_MATRIX_LIB_H
#define WORK_WITH_MATRIXES_MATRIX_LIB_H
#include <iostream>

enum type_of_matrix {ZERO, IDENTITY, NOT_INIT};

class Matrix {
private:
    uint height;
    uint width;
    double *data;
public:
    Matrix(uint height = 0, uint width = 0, type_of_matrix type = ZERO);
    // *matrix - указатель на массив, размером height x width
    Matrix(uint height, uint width, double *matrix);
    Matrix(const Matrix &matrix);
    Matrix(Matrix && matrix);
    ~Matrix();
public:
    Matrix & operator = (const Matrix &matrix);
    Matrix operator + (const Matrix &matrix);
    Matrix operator * (const Matrix &matrix);
public:
    double trace() const;
    double determinant() const; // Только для матриц < 4 порядка
    void print(const std::string &text = "Матрица:") const;
private:
    void memory_allocation();
    void free_memory();
public:
    bool is_null() const;
    void zero_matrix();
    void identity_matrix();
};



#endif //WORK_WITH_MATRIXES_MATRIX_LIB_H