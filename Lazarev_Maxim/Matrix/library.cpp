#include "library.h"
#include <iostream>

Matrix::Matrix(int lineCount, int columnCount):m(lineCount), n(columnCount) {
    contr = new double *[m];
    for (int i = 0; i < m; i++){
        contr[i] = new double [n];
        for (int j = 0; j < n; j++){
            contr[i][j]=0;
        }
    }
}

Matrix::Matrix(Matrix &mat) {
    this->m=mat.m;
    this->n=mat.n;
    this->contr = new double*[this->m];
    for (int i = 0; i < this->m; i++){
        this->contr[i] = new double [this->n];
        for (int j = 0; j < this->n; j++){
            this->contr[i][j]=mat.contr[i][j];
        }
    }
}

Matrix::~Matrix() {
    for (int i = 0; i<m; i++){
        delete [] contr[i];
    }
    delete [] contr;
}

void Matrix::setElement(int line, int column, double value) {
    contr[line][column] = value;
}

void Matrix::print() {
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            std::cout<< contr[i][j]<<'\t';
        }
        std::cout<<'\n';
    }
    std::cout<<'\n';
}

double  Matrix::determinant() {
    if (m!=n){
        std::cout<<"Матрица должна быть квадратной!"<<std::endl;
        return 0;
    }

    Matrix local(*this);
    double mn = 0, d = 1;
    for (int i=1; i<local.m; i++){
        for (int k=0; k<i; k++){
            mn = (-1)*(local.contr[i][k]/local.contr[k][k]);
            for (int j =0; j< local.n; j++){
                local.contr[i][j]+= local.contr[k][j]*mn;
            }
        }
    }
    for (int i = 0; i<local.m; i++){
        d*=local.contr[i][i];
    }
    return d;
}

double Matrix::trace() {
    double d = 0;
    for (int i = 0; i<this->m; i++){
        d+=this->contr[i][i];
    }
    return d;
}

Matrix &Matrix::operator=(const Matrix &mat) {
    if (this == &mat) return *this;
    if (this->m!=mat.m || this->n!=mat.n){
        std::cout<<"Размеры матриц не совпадают"<<std::endl;
        return *this;
    }
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            this->contr[i][j]=mat.contr[i][j];
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
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            C.contr[i][j] = this->contr[i][j]+mat.contr[i][j];
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
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            C.contr[i][j] = this->contr[i][j]-mat.contr[i][j];
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
    for (int i =0; i<this->m; i++){
        for (int j =0; j<mat.n; j++){
            for (int k = 0; k < this->n; k++){
                C.contr[i][j] += this->contr[i][k] * mat.contr[k][j];
            }
        }
    }
    return C;
}
