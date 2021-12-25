#ifndef MATRIX_LIBRARY_H
#define MATRIX_LIBRARY_H

class Matrix
{
private:
    unsigned int rows;
    unsigned int columns;
    double * elements;
public:
    Matrix(int rows, int columns);
    Matrix::Matrix(int range, char type, int nothing);
    void user_input();
    void output();
    ~Matrix();
    Matrix(const Matrix &m);
    Matrix(Matrix &&m) noexcept;
    Matrix & operator = (const Matrix &m);
    Matrix operator + (const Matrix& m);
    Matrix operator * (const Matrix& m);
    Matrix & operator = (Matrix &&m) noexcept;
    int trace();
    double det();
    double minor(int number_row, int number_column);
};

#endif //MATRIX_LIBRARY_H
