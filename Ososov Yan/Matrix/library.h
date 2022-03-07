
#ifndef UNTITLED24_LIBRARY_H
#define UNTITLED24_LIBRARY_H

typedef enum{
    ZEROS,
    IDENTITY,
    TEMPORARY,
    RANDOM,
    DIAGONAL,
    NUMBER,
} Matrix_Type;

class Matrix {
private:
    int rows;
    int cols;
    int *data;
public:
    Matrix();
    Matrix(int rows, int cols, int *arr, unsigned int length);
    //will copy the length elements from the arr to the matrix[row*cols].
    Matrix(int rows, int cols, Matrix_Type type, int value = 0);
    ~Matrix();
    Matrix(const Matrix &source);
    Matrix(Matrix &&source) noexcept;
    Matrix& operator= (const Matrix &source);
    Matrix& operator= (Matrix &&source) noexcept;
    Matrix operator+ (const Matrix &other);
    Matrix operator- (const Matrix &other);
    Matrix operator* (const Matrix &other);
    int tr();
    void print();
    int det();
    void set_zeros();
    void set_identity();
    void set_diagonal(int value);
    void set_number(int value);
    void set_random(int value);
};

#endif //UNTITLED24_LIBRARY_H
