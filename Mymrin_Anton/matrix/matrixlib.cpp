#include <iostream>
#include "matrix.h"

Matrix::Matrix(unsigned int row, unsigned int col) {
    this->row=row;
    this->col=col;
    data=new double [row*col];
    for (int i=0; i<row;i++){
        cout <<"matrix row № "<<i+1<<":"<<endl;
        for (int j=0;j<col;j++){
            cout <<"matrix element № "<<j+1<<":"<<endl;
            cin >> data[i*col+j];
        }
    }
}
void Matrix::print() {
    for (int i=0;i<row;i++){
        for (int j=0;j<col;j++){
            cout <<data[i*col+j]<<" ";
        }
        cout<<endl;
    }
}

Matrix::Matrix(unsigned int row, unsigned int col, int null){
    this->row=row;
    this->col=col;
    data=new double [row*col];
    for (int i=0; i<row;i++){
        for (int j=0;j<col;j++){
            data[i*col+j]=null;
        }
    }
}

Matrix::Matrix(unsigned int size){
    this->size=size;
    data=new double [row*col];
    for (int i=0; i<size;i++){
        for (int j=0;j<size;j++){
            if (i==j)
            data[i*size+j]=1;
            else data[i*size+j]=0;
        }
    }
}

Matrix::~Matrix(){
    delete[] data;
}

Matrix::Matrix(const Matrix &m) {
    this->row=m.row;
    this->col=m.col;
    this->data=new double [row*col];
    memcpy(data,m.data,sizeof(double)*row*col);
}

Matrix & Matrix::operator =(const Matrix &m) {
    for (int i = 0; i < this->row; ++i) {
        for (int j = 0; j < this->col; ++j) {
            this->data[i*col+j] = m.data[i*col+j];
        }
    }
    return *this;
}

Matrix Matrix::operator*(const Matrix &m) {
    Matrix Res(this->row, m.col, 0);
    if (this->col!=m.row){
        cout << "error! wrong size";
        return 0;
    }

    for (unsigned int i=0;i<this->row;++i) {
        for (unsigned int j=0; j<this->col;++j) {
            for (unsigned int k=0;k<Res.col;++k) {
                Res.data[i*Res.col+k]+=this->data[i*this->col+j]*m.data[m.col*j+k];
            }
        }
    }
    return Res;
}

Matrix Matrix::operator+(const Matrix &m) {
    if ((this->row!=m.row)&&(this->col!=m.col)) {
        cout << "error! wrong size";
        return 0;
    }
    Matrix Res(m.row,m.col,0);
    for (unsigned int i=0;i<m.row;i++)
        for (unsigned int j=0;j<m.col;j++)
            Res.data[i*Res.col+j]= this->data[i*this->col+j]+m.data[i*m.col+j];
    return Res;
}

Matrix Matrix::operator-(const Matrix &m) {
    if ((this->row!=m.row)&&(this->col!=m.col)) {
        cout << "error! wrong size";
        return 0;
    }
    Matrix Res(m.row,m.col,0);
    for (unsigned int i=0;i<m.row;i++)
        for (unsigned int j=0;j<m.col;j++)
            Res.data[i*Res.col+j]= this->data[i*this->col+j]-m.data[i*m.col+j];
    return Res;
}

double Matrix::trace() {
    double trace=0.0;
    if (col!=row){
        cout << "error! wrong size";
        return 0;
    }
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