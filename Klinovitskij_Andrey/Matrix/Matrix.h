//
// Created by KAD1605 on 22.11.2021.
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
    Matrix();
    Matrix(int height, int width);
    Matrix(const Matrix&); //for copy
    Matrix (Matrix &&other) noexcept;
    ~Matrix();

    void set_random(int height, int width);
    void out();
    int size_height();
    int size_width ();
    int trace();
    //int sum (const Matrix A, const Matrix B);
    //int subtraction (const Matrix A, const Matrix B);
    //int multiplication (const Matrix A, const Matrix B);
    Matrix operator+ (const Matrix &other);
    Matrix operator- (const Matrix &other);
    Matrix operator* (const Matrix &other);
    Matrix & operator = (Matrix &&) noexcept;
    Matrix & operator = (const Matrix &);

private:
    void free(int* data);
};


#endif //MATRIX_MATRIX_H
