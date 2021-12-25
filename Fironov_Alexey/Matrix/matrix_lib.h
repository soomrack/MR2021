//
// Created by Fironov Alexey on 22.12.2021.
//

#pragma once
#include <iostream>
#ifndef MATRIX_MATRIX_LIB_H
#define MATRIX_MATRIX_LIB_H

class Matrix {
public:
    //Constructor and Destructor
    Matrix (unsigned int rows_num = 0, unsigned int columns_num = 0);
    Matrix (Matrix &);  //Makes matrix copy
    ~Matrix();
//==================================================================
    void visual ();

    void set_cell (unsigned int №_row, unsigned int №_calumn,   // Number from 1+
                   double value);
    double get_cell (unsigned int №_row, unsigned int №_calumn);// Number from 1+

    void diagonal_filling (double);
    double diagonal_trace();    //sum of cells[i][i]

    double det();

    void get_identity ();
    void get_reverse ();

    Matrix operator= (const Matrix &);
    Matrix operator+ (const Matrix &);
    Matrix operator- (const Matrix &);
    Matrix operator* (const Matrix &);

private:
    void get_zero_matrix ();    //turns matrix into matrix filled with 0

    unsigned int rows_num;
    unsigned int columns_num;
    double **data;
};

#endif //MATRIX_MATRIX_LIB_H