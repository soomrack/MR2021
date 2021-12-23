#ifndef UNTITLED94_LIBRARY_H
#define UNTITLED94_LIBRARY_H

typedef enum {
    RANDOM,
    ZERO,
    IDENTITY,
    ONES
}Matrix_type;

class Matrix {
private:
    int rows = 0;
    int cols = 0;
    double **matrix;
public:
    Matrix(int rows, int cols, Matrix_type type);
    Matrix();
    Matrix(const Matrix &other);
    Matrix(Matrix &&other) noexcept;
    ~Matrix();
public:
    Matrix& operator= (const Matrix &other);
    Matrix& operator= (Matrix &&other) noexcept;
    Matrix operator+ (const Matrix &other);
    Matrix operator- (const Matrix &other);
    Matrix operator* (const Matrix &other);
public:
    void random_matrix();
    void zero_matrix();
    void ones_matrix();
    void identity_matrix();
public:
    double trace();
    double det();
public:
    void print();
private:
    void memory_allocation();
    void free_memory();
};

#endif //UNTITLED94_LIBRARY_H

