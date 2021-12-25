#ifndef MATRIX_LIBRARY_H
#define MATRIX_LIBRARY_H

class Matrix{
private:
    int height;
    int width;
    double * data;
public:
    ~Matrix();
    Matrix();                                                    //Создание м-цы размером 1*1 со значением 0
    Matrix(int height, int width);                               // Создание м-цы размером height*width, заполненной нулями

    Matrix(int height, int width, double (&data)[]);
    Matrix(const Matrix &m);
    Matrix(Matrix &&m) noexcept;
    Matrix & operator= (const Matrix &m);
    Matrix operator+ (const Matrix &m);
    Matrix operator* (const Matrix &m);

    void print();
    double trace();
};

#endif //MATRIX_LIBRARY_H
