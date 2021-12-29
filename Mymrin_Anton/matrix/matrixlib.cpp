#include <iostream>
#include "matrix.h"

void Matrix::print() {
    for (int i=0;i<row;i++){
        for (int j=0;j<col;j++){
            cout <<data[i*col+j]<<" ";
        }
        cout<<endl;
    }
}

Matrix::Matrix(unsigned int row, unsigned int col, int value){
    this->row=row;
    this->col=col;
    data=new double [row*col];
    for (int i=0; i<row*col;i++){
        data[i]=value;
    }
}

Matrix::Matrix(unsigned int size){
    this->size=size;
    data=new double [size*size];
    for (int i=0; i<size*size;i++){
        data[i]=0;
    }
    for (int j=0;j<size;j++)
        data[j*size+j]=1;
}

Matrix::~Matrix(){
    delete[] data;
}
Matrix::Matrix() {
    row=0;
    col=0;
    data=nullptr;
}

Matrix::Matrix(const Matrix &m) {
    this->row=m.row;
    this->col=m.col;
    this->data=new double [row*col];
    memcpy(data,m.data,sizeof(double)*row*col);
}
Matrix::Matrix(Matrix&& m) noexcept{
    col=m.col;
    row=m.row;
    data=m.data;
    m.col=0;
    m.row=0;
    m.data=nullptr;
}

Matrix & Matrix::operator =(const Matrix &m) {
    if (&m== this){
        return *this;
    }
    row=m.row;
    col=m.col;
    delete[] data;
    data=new double [row*col];
    memcpy(data,m.data,sizeof(double)*row*col);
    return *this;
}

Matrix Matrix::operator =(Matrix &&m) {
    if (&m== this){
        return *this;
    }
    row=m.row;
    col=m.col;
    delete[] data;
    data=new double [row*col];
    data=m.data;
    m.data= nullptr;
    m.row = 0;
    m.col = 0;
    return *this;
}

Matrix Matrix::operator*(const Matrix &m) {
    if (col!=m.row){
        cout << "error! wrong size";
        return Matrix();
    }
    Matrix Res(row, m.col, 0);
    for (unsigned int i=0;i<this->row;++i) {
        for (unsigned int j=0; j<this->col;++j) {
            for (unsigned int k=0;k<Res.col;++k) {
                Res.data[i*Res.col+k]+=data[i*col+j]*m.data[m.col*j+k];
            }
        }
    }
    return Res;
}

Matrix Matrix::operator+(const Matrix &m) {
    if ((row!=m.row)&&(col!=m.col)) {
        cout << "error! wrong size";
        return Matrix();
    }
    Matrix Res(m.row,m.col,0);
    for (unsigned int i=0;i<m.row*m.col;i++)
            Res.data[i]= data[i]+m.data[i];
    return Res;
}

Matrix Matrix::operator-(const Matrix &m) {
    if ((row!=m.row)&&(col!=m.col)) {
        cout << "error! wrong size";
        return Matrix();
    }
    Matrix Res(m.row,m.col,0);
    for (unsigned int i=0;i<m.row*m.col;i++)
        Res.data[i]= data[i]-m.data[i];
    return Res;
}

double Matrix::trace() {
    if (col!=row){
        cout << "error! wrong size";
        return 0.0;
    }
    double trace=0.0;
    for (unsigned int i=0;i<row;i++)
        trace+=data[i*row+i];
    return trace;
}

double Matrix::det() {
    double det=0.0;
    if (col==2&&row==2){
        det=data[0]*data[3]-data[1]*data[2];
        return det;
    } else
        if(col==3&&row==3){
            det=data[0]*data[4]*data[8]+data[2]*data[3]*data[7]+data[1]*data[5]*data[6]-data[6]*data[4]*data[2]-
                    data[0]*data[5]*data[7]-data[1]*data[3]*data[8];
            return det;
        } else
        {
            cout << "error! wrong size";
            return 0;
        }
}