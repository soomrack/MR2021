#ifndef MATRIX_MATRIXLIB_H
#define MATRIX_MATRIXLIB_H


class Matrix {
private:
    int rows;
    int cols;
    double * data;
public:
    Matrix();
    Matrix(int rows, int cols);
    Matrix(int rows, int cols, int type);
    Matrix & operator = (const Matrix &other);
    Matrix(const Matrix &other);
    Matrix(Matrix &&other) noexcept;
    Matrix & operator = (Matrix &&other) noexcept;
    Matrix operator + (const Matrix &other);
    Matrix operator * (const Matrix &other);
    ~Matrix();

    void print();
    void set(int row, int col, double element);
    void set_nulls();
    void set_ones();
    double tr();
    double det();
    double minor_det(int n, int m);
};


#endif //MATRIX_MATRIXLIB_H
