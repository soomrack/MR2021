
#ifndef UNTITLED24_LIBRARY_H
#define UNTITLED24_LIBRARY_H


class Matrix {
private:
    int rows = 0;
    int cols = 0;
    int *content;
public:
    Matrix(int rows, int cols);
    Matrix(int rows, int cols, int type);
    ~Matrix();
    Matrix(const Matrix &other);
    Matrix(Matrix &&other) noexcept;
    Matrix& operator = (const Matrix &other);
    Matrix operator + (const Matrix &other);
    Matrix operator - (const Matrix &other);
    Matrix& operator= (Matrix &&other) noexcept;
    Matrix operator * (const Matrix &other);
    int tr();
    void print();
    double det();

};

#endif //UNTITLED24_LIBRARY_H
