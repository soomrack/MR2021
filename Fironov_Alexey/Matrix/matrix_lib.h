//
// Created by Fironov Alexey on 22.12.2021.
//
#pragma once
#include <iostream>
#ifndef MATRIX_MATRIX_LIB_H
#define MATRIX_MATRIX_LIB_H

class Matrix {
private:
    unsigned int rows_num;
    unsigned int columns_num;
    double *data;
public:
    Matrix (unsigned int rows_num = 0, unsigned int columns_num = 0, double value = 0.0);
    Matrix (Matrix &);  //Makes matrix copy
    Matrix (Matrix &&);
    ~Matrix();
public:
    void print ();
    void set_cell (unsigned int N_row, unsigned int N_column,
                   double value);
    double get_cell (unsigned int N_row, unsigned int N_column);
    void diagonal_filling (double value);
    double diagonal_trace();    //sum of cells[i][i]
    double det();
    void set_identity ();
    void set_reverse ();
    void set_zero_matrix ();    //turns matrix into matrix filled with 0

    Matrix operator= (const Matrix &);
    Matrix operator= (Matrix &&);
    Matrix operator+ (const Matrix &);
    Matrix operator- (const Matrix &);
    Matrix operator* (const Matrix &);
};

#endif //MATRIX_MATRIX_LIB_H