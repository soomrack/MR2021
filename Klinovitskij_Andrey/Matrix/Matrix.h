//
// Created by User on 22.11.2021.
//
#pragma once

#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

class Matrix {
private:
    int height;
    int width;
    int *data;
public:
    Matrix(int height, int width);
    Matrix(const Matrix&); //for copy
    ~Matrix();

    void random_input(int height, int width);
    void out();
    int size_height();
    int size_width ();
    //int sum (const Matrix A, const Matrix B);
    //int subtraction (const Matrix A, const Matrix B);
    //int multiplication (const Matrix A, const Matrix B);
    Matrix operator+ (const Matrix &other);
    Matrix operator- (const Matrix &other);
    Matrix operator* (const Matrix &other);
private:
    void free(int* data);
};


#endif //MATRIX_MATRIX_H
