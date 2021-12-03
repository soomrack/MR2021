#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class matrix {
public:
    matrix(int rows, int columns);
    matrix(const matrix &);
    ~matrix();

    matrix operator + (const matrix &);
    matrix operator - (const matrix &);
    matrix operator * (const matrix &);
    void operator = (const matrix &);

    double get_det();
    int get_rows();
    int get_columns();
    void get_matrix();
    matrix get_transpose();
    void set_cells_cmd();
    void set_cell(int,int,double);
    void sort_rows(int);

private:
    int rows;
    int columns;
    vector<vector<double> >data;
};