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
    Matrix(int height, int width, double (&data)[]);
    Matrix(int height, int width);
    Matrix(const Matrix &m);
    Matrix(Matrix &&m);
    Matrix & operator= (const Matrix &m);
    Matrix & operator+ (const Matrix &m);
    Matrix & operator* (const Matrix &m);

    void print();
    double trace();
};

#endif //MATRIX_LIBRARY_H
