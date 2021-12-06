//
// Created by User on 22.11.2021.
//

#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

class Matrix {
private:
    int height;
    int width;
    int *data;
public:
    Matrix(int height, int width);
    void MatrixRandom(int height, int width);
    void MatrixOut(int width, int height);
    int MatrixSizeHeight();
    int MatrixSizeWidth ();
    void MatrixSum (Matrix A, Matrix B);
    void MatrixSub (Matrix A, Matrix B);
    void MatrixMul (Matrix A, Matrix B);
private:
    void FreeMatrix(int** data);
};


#endif //MATRIX_MATRIX_H
