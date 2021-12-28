#ifndef MATRIX_LIBRARY_H
#define MATRIX_LIBRARY_H

class Matrix{
private:
    int height;
    int width;
    double * data;
public:
    ~Matrix();
    Matrix();
    Matrix(unsigned int height, unsigned int width, double value=0.0);
    Matrix(unsigned int height, unsigned int width, double *data);
    Matrix(const Matrix &m);
    Matrix(Matrix &&m) noexcept ;
    Matrix & operator= (const Matrix &m);
    Matrix operator+ (const Matrix &m);
    Matrix operator* (const Matrix &m);
    void print();
    void determinant();
    void trace();
    void identity_matrix ();// генерирует единичную матрицу
    void zero_matrix(); //генерирует нулевую матрицу
};


#endif //MATRIX_LIBRARY_H
