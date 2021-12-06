#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

class matrix {
public:
    matrix(int rows, int columns);
    matrix(const matrix &);
    matrix(matrix &&) noexcept;
    ~matrix();

    matrix operator + (const matrix &);
    matrix operator - (const matrix &);
    matrix operator * (const matrix &);
    matrix operator = (matrix &&) noexcept;
    matrix operator = (const matrix &);

    double get_det();
    int get_rows();
    int get_columns();
    double get_value(int,int);
    void get_matrix();
    matrix get_transpose();
    void set_cells_cmd();
    void set_cell(int,int,double);
    void sort_rows(int);

private:
    int rows;
    int columns;
    std::vector<std::vector<double> > data;
};