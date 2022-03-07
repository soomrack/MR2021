#ifndef MATRIX_H
#define MATRIX_H

class Matrix {
public:
    Matrix (int lineCount, int columnCount);
    Matrix (Matrix &mat);
    ~Matrix();
    void setElement(int line, int  column, double value);
    void print();
    double determinant();
    double trace();
    Matrix &operator= (const Matrix &mat);
    Matrix operator+ (const Matrix &mat);
    Matrix operator- (const Matrix &mat);
    Matrix operator* (const Matrix &mat);
private:
    int m = 0; //m строк
    int n = 0; //n столбцов
    double** contr; //контейнер элементов

};

#endif //MATRIX_H
