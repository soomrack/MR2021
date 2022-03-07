#include "Matrix.h"
#include <math.h>

int Matrix::MatrixCount = 0;

const char* Matrix::Exception::what () const noexcept {
    switch (exId) {
        default:
            return "Неизвестная ошибка\n";
        case 0:
            return "Ошибка выделения памяти\n";
        case 1:
            return "Некорректное количество строк\n";
        case 2:
            return "Некорректное количество столбцов\n";
        case 3:
            return "Некорректный размер матрицы\n";
        case 4:
            return "Некорректная индексация строки\n";
        case 5:
            return "Некорректная индексация столбца\n";
        case 6:
            return "Главная диагональ содержит нулевые элементы \n";
    }
}

Matrix::Matrix(const int lineCount, const int columnCount, double value):line(lineCount), col(columnCount) {
    if(line < 0){throw Exception(1);}
    if(col < 0){throw Exception(2);}

    size = line * col;
    MatrixCount++;
    id = MatrixCount;

    if(size == 0) {
        data = new double[1];
        data[0] = 0;
    }
    else {
        data = new double [size];
        for (int k = 0; k < size; ++k){
            data[k] = value;
        }
    }

    if (data == nullptr){throw Exception(0);}
}

Matrix::Matrix(const Matrix &other) {
    line = other.line;
    col = other.col;
    size = other.size;

    if(line < 0){throw Exception(1);}
    if(col < 0){throw Exception(2);}

    MatrixCount++;
    id = MatrixCount;

    if(size == 0) {
        data = new double [1];
        data[0] = 0;
    }
    else {
        data = new double [size];
        memcpy(data, other.data, sizeof(double)*size);
    }

    if (data == nullptr){throw Exception(0);}
}

Matrix::Matrix(Matrix&& other){
    line = other.line;
    col = other.col;
    size = other.size;

    if(line < 0){throw Exception(1);}
    if(col < 0){throw Exception(2);}

    MatrixCount++;
    id = MatrixCount;

    data = other.data;
    other.data = nullptr;

    if (data == nullptr){throw Exception(0);}
}

Matrix::~Matrix() {
    MatrixCount--;
    delete [] data;
    data = nullptr;
}

Matrix Matrix::getShortedMatrix() {
    if (line != col||size == 1||size == 0) {return *this;}

    Matrix shorted(line-1, col-1);
    int kBase=0, kShort=0;
    while (kBase + col + 1 < size){
        shorted.data[kShort] = data[kBase + col + 1];
        if (shorted.getCol(kShort)==shorted.col - 1) {
            kBase += 2;
            kShort++;
        }
        else {
            kBase += 1;
            kShort++;
        }
    }
    return shorted;
}

double& Matrix::getElement(const int line,const int col) {
    if(line < 0||line >= this->line) {throw Exception(4);}
    if(col < 0||col >= this->col) {throw Exception(5);}

    return data[this->col * line + col];
}

double Matrix::copyElement(const int line, const int col) const {
    if(line < 0||line >= this->line) {throw Exception(4);}
    if(col < 0||col >= this->col) {throw Exception(5);}

    return data[this->col * line + col];
}

int Matrix::getLine(const int index){
    return index/col;
}

int Matrix::getCol(const int index){
    return (index - (index/col) * col);
}

int Matrix::maxPosInCol(int pos) {
    int maxPos = pos;
    double max = std::abs(data[maxPos]);
    for (int j = pos + col; j < size; j += col){
        if (std::abs(data[j]) > max){
            maxPos = j;
            max = std::abs(data[j]);
        }
    }
    return maxPos;
}

void Matrix::setElement(const double value,const int line,const int col) {
    if(line < 0||line >= this->line) {throw Exception(4);}
    if(col < 0||col >= this->col) {throw Exception(5);}

    data[this->col * line + col] = value;
}

void Matrix::swapLines(const int line_1, const int line_2) {
    if(line_1 < 0||line_1 >= line) {throw Exception(4);}
    if(line_2 < 0||line_2 >= line) {throw Exception(4);}

    double buffer[col];
    memcpy(buffer, data + (col*line_1), sizeof(double)*col);
    memcpy(data + (col*line_1), data + (col*line_2), sizeof(double)*col);
    memcpy(data + (col*line_2), buffer, sizeof(double)*col);
}

void Matrix::swapCols(const int col_1, const int col_2) {
    if(col_1 < 0||col_1 >= col) {throw Exception(5);}
    if(col_2 < 0||col_2 >= col) {throw Exception(5);}

    double buffer = 0.0;
    for (int m=0; m<line; ++m){
        buffer = copyElement(m,col_1);
        setElement(copyElement(m, col_2), m, col_1);
        setElement(buffer, m, col_2);
    }
}

void Matrix::print(){
    if (size == 0){
        std::cout<<data[0]<<std::endl;
    }
    else {
        for (int k = 0; k < size; ++k){
            std::cout<<data[k]<<" ";
            if((k + 1) % col == 0){std::cout<<std::endl;}
        }
    }
    std::cout<<std::endl;
}

void Matrix::toGaus(int* swapCount) {
    if (line != col||size == 1||size == 0) {return;}

    double mn = 0.0;
    for (int i = 0; i < line; ++i){
        int diagPos = i + col*i;
        int maxPos = maxPosInCol(diagPos);
        if (data[maxPos] == 0) {throw Exception(6);}
        if (data[diagPos] == 0){
            swapLines(getLine(maxPos), getLine(diagPos));
            if(swapCount != nullptr) {(*swapCount)++;}
        }
        for (int j = i + 1; j < line; ++j) {
            int divPos = i + col * j;
            mn = -(data[divPos] / data[diagPos]);
            for (int k = i; k < col; ++k) {
                int elPos_1 = k + j * col, elPos_2 = k + i * col;
                data[elPos_1] += data[elPos_2] * mn;
            }
        }
    }
}

double Matrix::det() {
    if (line != col) {throw Exception(3);}
    if (size == 1||size == 0) {return data[0];}

    Matrix local(*this);
    int swapCount=0;
    int* pswapCount = &swapCount;
    local.toGaus(pswapCount);
    double det = 1.0;
    for (int m = 0; m < line; m++){
        det *= local.copyElement(m,m);
    }
    if (swapCount % 2 == 1) {det *= -1;}
    return det;
}

double Matrix::trace() {
    if (line != col) {throw Exception(3);}
    if (size == 1||size == 0) {return data[0];}

    double tr = 0.0;
    for (int m = 0; m < line; m++){
        tr += copyElement(m,m);
    }
    return tr;
}

Matrix& Matrix::operator=(const Matrix &mat) {
    if (this == &mat) {return *this;}

    delete [] data;
    line = mat.line;
    col = mat.col;
    size = mat.size;
    data = new double [size];
    memcpy(data, mat.data, sizeof(double)*size);
    return *this;
}

Matrix& Matrix::operator=(Matrix &&mat) {
    if (this == &mat) {return *this;}

    line = mat.line;
    col = mat.col;
    size = mat.size;
    data = mat.data;
    mat.data = nullptr;
    return *this;
}

Matrix Matrix::operator+(const Matrix &mat) {
    if (line != mat.line || col != mat.col) {throw Exception(3);}

    Matrix res(*this);
    for(int k = 0; k < res.size; k++){
        res.data[k]+=mat.data[k];
    }
    return res;
}

Matrix Matrix::operator-(const Matrix &mat) {
    if (line != mat.line || col != mat.col) {throw Exception(3);}

    Matrix res(*this);
    for(int k = 0; k < res.size; k++){
        res.data[k]-=mat.data[k];
    }
    return res;
}

Matrix Matrix::operator*(const Matrix &mat) {
    if (col != mat.line) {throw Exception(3);}

    if (size == 0||mat.size == 0) {
        Matrix res;
        return res;
    }
    else {
        Matrix res(line, mat.col);
        for (int m = 0; m < line; m++){
            for (int n = 0; n < mat.col; n++){
                for (int k = 0; k < col; k++){
                    res.getElement(m,n) += copyElement(m,k) * mat.copyElement(k,n);
                }
            }
        }
        return res;
    }
}