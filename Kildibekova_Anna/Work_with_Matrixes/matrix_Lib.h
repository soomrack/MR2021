//
// Библиотека для работы с матрицами.
//

#ifndef WORK_WITH_MATRIXES_MATRIX_LIB_H
#define WORK_WITH_MATRIXES_MATRIX_LIB_H
#include <iostream>

enum type_of_matrix {zero = 0, identity = 1};

class Matrix {
public:
    Matrix( int height = 0, int wight = 0, type_of_matrix type = zero);  //+
    Matrix(const Matrix &matrix);  //+
    Matrix(Matrix && matrix);
    ~Matrix();  //+
private:
    int height;
    int wight;
    double *data;
private:
    Matrix & operator = (const Matrix &matrix);  //
    Matrix & operator + (const Matrix &matrix);  //
    Matrix & operator * (const Matrix &matrix);  //
public:
    double trace() const;  //+
    double determinant() const;  //
    void print(const std::string &text = "Матрица:") const;  //+
private:
    void memory_allocation();  //+
    void free_memory();  //+
    bool check() const;  //+
private:
    bool cleanly;
};



#endif //WORK_WITH_MATRIXES_MATRIX_LIB_H