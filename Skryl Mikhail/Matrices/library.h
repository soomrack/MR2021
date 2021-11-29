#ifndef UNTITLED94_LIBRARY_H
#define UNTITLED94_LIBRARY_H

class Matrix {
private:
    int rows = 0;
    int cols = 0;
    int **matrix;
public:
    Matrix(int rows, int cols);
    Matrix(int rows, int cols, int type);
    Matrix(int rows, int cols, bool isTemp);
    ~Matrix();
    Matrix(const Matrix &other);
    Matrix(Matrix &&other) noexcept;
    Matrix & operator = (const Matrix &other);
    Matrix operator + (const Matrix &other);
    Matrix operator - (const Matrix &other);
    Matrix & operator = (Matrix &&other) noexcept;
    Matrix operator * (const Matrix &other);
    int trace();
    double det();
    void print();
};

#endif //UNTITLED94_LIBRARY_H

