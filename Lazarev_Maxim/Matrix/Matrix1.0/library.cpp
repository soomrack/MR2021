#include "library.h"
#include <iostream>

Matrix::Matrix(int lineCount, int columnCount):m(lineCount), n(columnCount) {
    contr = new double *[m];
    for (int line = 0; line < m; line++){
        contr[line] = new double [n];
        for (int col = 0; col < n; col++){
            contr[line][col]=0.0;
        }
    }
    if (contr == nullptr||contr[0] == nullptr){
        std::cout<<"Не удалось корректно выделить память"<<std::endl;
    }
}

Matrix::Matrix(Matrix &mat) {
    this->m=mat.m;
    this->n=mat.n;
    this->contr = new double*[this->m];
    for (int line = 0; line < this->m; line++){
        this->contr[line] = new double [this->n];
        for (int col = 0; col < this->n; col++){
            this->contr[line][col]=mat.contr[line][col];
        }
    }
    if (contr == nullptr||contr[0] == nullptr){
        std::cout<<"Не удалось корректно выделить память"<<std::endl;
    }
}

Matrix::Matrix(Matrix &&mat) {
    this->m=mat.m;
    this->n=mat.n;
    this->contr = mat.contr;
    for (int line = 0; line < this->m; line++){
        this->contr[line] = mat.contr[line];
    }
    if (contr == nullptr||contr[0] == nullptr){
        std::cout<<"Не удалось корректно выделить память"<<std::endl;
    }
}

Matrix::~Matrix() {
    for (int line = 0; line<m; line++){
        delete [] contr[line];
    }
    delete [] contr;
}

void Matrix::setElement(int line, int column, double value) {
    contr[line][column] = value;
}

void Matrix::print() {
    for (int line = 0; line < m; line++){
        for (int col = 0; col < n; col++){
            std::cout<< contr[line][col]<<'\t';
        }
        std::cout<<'\n';
    }
    std::cout<<'\n';
}

void Matrix::setGaus() {
    if (m!=n){
        std::cout<<"Матрица должна быть квадратной!"<<std::endl;
        return;
    }
    double mn = 0.0;
}

double  Matrix::determinant() {
    if (m!=n){
        std::cout<<"Матрица должна быть квадратной!"<<std::endl;
        return 0;
    }

    Matrix local(*this);
    double mn = 0.0, d = 1;
    for (int line=1; line<local.m; line++){
        for (int k=0; k<line; k++){
            mn = (-1)*(local.contr[line][k]/local.contr[k][k]);
            for (int col =0; col < local.n; col++){
                local.contr[line][col]+= local.contr[k][col]*mn;
            }
        }
    }
    for (int line = 0; line<local.m; line++){
        d*=local.contr[line][line];
    }
    return d;
}

double Matrix::trace() {
    double d = 1.0;
    for (int line = 0; line<this->m; line++){
        d+=this->contr[line][line];
    }
    return d;
}

Matrix &Matrix::operator=(const Matrix &mat) {
    if (this == &mat) return *this;
    if (this->m!=mat.m || this->n!=mat.n){
        std::cout<<"Размеры матриц не совпадают"<<std::endl;
        return *this;
    }
    for (int line = 0; line < m; line++){
        for (int col = 0; col < n; col++){
            this->contr[line][col]=mat.contr[line][col];
        }
    }
    return *this;
}

Matrix Matrix::operator+(const Matrix &mat) {
    if (this->m!=mat.m || this->n!=mat.n){
        std::cout<<"Размеры матриц не совпадают"<<std::endl;
        return *this;
    }
    Matrix C(this->m, this->n);
    for (int line = 0; line < m; line++){
        for (int col = 0; col < n; col++){
            C.contr[line][col] = this->contr[line][col]+mat.contr[line][col];
        }
    }
    return C;
}

Matrix Matrix::operator-(const Matrix &mat) {
    if (this->m!=mat.m || this->n!=mat.n){
        std::cout<<"Размеры матриц не совпадают"<<std::endl;
        return *this;
    }
    Matrix C(this->m, this->n);
    for (int line = 0; line < m; line++){
        for (int col = 0; col < n; col++){
            C.contr[line][col] = this->contr[line][col]-mat.contr[line][col];
        }
    }
    return C;
}

Matrix Matrix::operator*(const Matrix &mat) {
    if (this->n!=mat.m){
        std::cout<<"Перемножение матриц невзможно"<<std::endl;
        return *this;
    }

    Matrix C(this->m,this->n);
    for (int line =0; line<this->m; line++){
        for (int col =0; col<mat.n; col++){
            for (int k = 0; k < this->n; k++){
                C.contr[line][col] += this->contr[line][k] * mat.contr[k][col];
            }
        }
    }
    return C;
}