#ifndef MATRIX_LIBRARY_H
#define MATRIX_LIBRARY_H
enum Type
{
    TYPE_NULL,
    TYPE_ONE,
};

class Matrix
{
private:
    unsigned int rows;
    unsigned int columns;
    double * elements;
public:
    Matrix();
    Matrix(unsigned int rows, unsigned int columns);
    Matrix(unsigned int range,Type type);
    void fill_zeros();
    void fill_ones();
    void user_input();
    void print();
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
