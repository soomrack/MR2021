#ifndef MATRIX_MATRIXLIB_H
#define MATRIX_MATRIXLIB_H



class Matrix {
private:
    int rows;
    int cols;
    double * data;
public:
    Matrix(int rows, int cols);
    Matrix(int rows, int cols, int type);
    void print();
    void set(int row, int col, double element);
    Matrix & operator = (const Matrix &other);
    Matrix(const Matrix &other);
    ~Matrix();
    Matrix(Matrix &&other) noexcept;
    Matrix & operator = (Matrix &&other) noexcept;
    Matrix operator + (const Matrix &other);
    Matrix operator * (const Matrix &other);
    int tr();
    double det();
    void setnulls();
    void setones();
};


#endif //MATRIX_MATRIXLIB_H
