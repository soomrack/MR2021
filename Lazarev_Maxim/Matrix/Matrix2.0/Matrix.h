#ifndef MATRIX2_0_MATRIX_H
#define MATRIX2_0_MATRIX_H
#include <iostream>

class Matrix{
public:
    class Exception: public std::exception{
    public:
        Exception(int id):exId(id){}
        Exception(Exception& other){this->exId=other.exId;}
        Exception(Exception&& other){this->exId=other.exId;}
        const char* what () const noexcept override;
    private:
        int exId = 0;
    };
    Matrix (const int lineCount = 0, const int columnCount = 0, double value = 0.0);
    Matrix (const Matrix& other);
    Matrix (Matrix&& other);
    ~Matrix();
    int getId(){return id;}
    int lineCount(){return line;}
    int colCount(){return col;}
    double& getElement(const int line,const int col);
    double copyElement(const int line,const int col) const;
    double det();
    double trace();
    void setElement(const double value,const int line,const int col);
    void swapLines(const int line_1, const int line_2);
    void swapCols(const int col_1, const int col_2);
    void print();
    void toGaus(int* swapCount = nullptr);
    Matrix getShortedMatrix();
    Matrix& operator=(const Matrix& mat);
    Matrix& operator=(Matrix&& mat);
    Matrix operator+ (const Matrix &mat);
    Matrix operator- (const Matrix &mat);
    Matrix operator* (const Matrix &mat);
private:
    static int MatrixCount;
    int id = 0;
    double* data = nullptr;
    int line = 0;
    int col = 0;
    int size = 0;
    int maxPosInCol(int row);
    int getLine(const int index);
    int getCol(const int index);
};

#endif //MATRIX2_0_MATRIX_H
