#include "Matrix.h"
#include <math.h>

int Matrix::MatrixCount = 0;

std::string Matrix::exception::what() {
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
    size = line*col;
    MatrixCount++;
    id = MatrixCount;

    try{
        if(line<=0){throw 1;}
        if(col<=0){throw 2;}
        if(size<2){throw 3;}
    }
    catch (exception ex){
        std::cout<<ex.what()<<std::endl;
        return;
    }

    data = new double [size];
    for (int k=0; k<size; ++k){
        data[k]=value;
    }
    if (data == nullptr){throw exception(0);}
}

Matrix::Matrix(const Matrix &other) {
    MatrixCount++;
    id = MatrixCount;
    this->line = other.line;
    this->col = other.col;
    this->size = other.size;

    try{
        if(line<=0){throw 1;}
        if(col<=0){throw 2;}
        if(size<2){throw 3;}
    }
    catch (exception ex){
        std::cout<<ex.what()<<std::endl;
        return;
    }

    this->data = new double [size];
    for (int k=0; k<size; ++k){
        this->data[k]=other.data[k];
    }
    if (this->data == nullptr){throw exception(0);}
}

Matrix::Matrix(Matrix&& other){
    MatrixCount++;
    id = MatrixCount;
    this->line = other.line;
    this->col = other.col;
    this->size = other.size;

    try{
        if(line<=0){throw 1;}
        if(col<=0){throw 2;}
        if(size<2){throw 3;}
    }
    catch (exception ex){
        std::cout<<ex.what()<<std::endl;
        return;
    }

    this->data = other.data;
    other.data = nullptr;
    if (this->data == nullptr){throw exception(0);}
}

Matrix::~Matrix() {
    MatrixCount--;
    delete [] data;
    data = nullptr;
}

Matrix Matrix::getShortedMatrix() {
    try {
        if (line!=col||size==1) {throw exception(3);}
    }
    catch (exception ex){
        std::cout<<ex.what()<<std::endl;
        return *this;
    }

    Matrix shorted(this->line-1, this->col-1);
    int kBase=0, kShort=0;
    while (kBase+this->col+1 < this->size){
        shorted.data[kShort] = this->data[kBase+this->col+1];
        if (shorted.getCol(kShort)==shorted.col-1) {
            kBase+=2;
            kShort++;
        }
        else {
            kBase+=1;
            kShort++;
        }
    }
    return shorted;
}

double& Matrix::getElement(const int line,const int col) {
    try{
        if(line<0||line>=this->line) {throw exception(4);}
        if(col<0||col>=this->col) {throw exception(5);}
    }
    catch (exception ex){
        std::cout<<ex.what()<<std::endl;
        return data[0];
    }

    return data[this->col*line + col];
}

double Matrix::copyElement(const int line, const int col) const {
    try{
        if(line<0||line>=this->line) {throw exception(4);}
        if(col<0||col>=this->col) {throw exception(5);}
    }
    catch (exception ex){
        std::cout<<ex.what()<<std::endl;
        return 0.0;
    }

    return data[this->col*line + col];
}

int Matrix::getLine(const int index){
    return index/col;
}

int Matrix::getCol(const int index){
    return (index-(index/col)*col);
}

int Matrix::maxPosInCol(int pos) {
    int maxPos = pos;
    double max = std::abs(data[maxPos]);
    for (int j=pos+col; j<size; j+=col){
        if (std::abs(data[j])>max){
            maxPos = j;
            max = std::abs(data[j]);
        }
    }
    return maxPos;
}

void Matrix::setElement(const double value,const int line,const int col) {
    try{
        if(line<0||line>=this->line) {throw exception(4);}
        if(col<0||col>=this->col) {throw exception(5);}
    }
    catch (exception ex){
        std::cout<<ex.what()<<std::endl;
        return;
    }

    data[this->col*line + col] = value;
}

void Matrix::swapLines(const int line_1, const int line_2) {
    try{
        if(line_1<0||line_1>=this->line) {throw exception(4);}
        if(line_2<0||line_2>=this->line) {throw exception(4);}
    }
    catch (exception ex){
        std::cout<<ex.what()<<std::endl;
        return;
    }

    double buffer = 0.0;
    for (int n=0; n<col; ++n){
        buffer = copyElement(line_1,n);
        setElement(copyElement(line_2, n), line_1, n);
        setElement(buffer, line_2, n);
    }
}

void Matrix::swapCols(const int col_1, const int col_2) {
    try{
        if(col_1<0||col_1>=this->col) {throw exception(5);}
        if(col_2<0||col_2>=this->col) {throw exception(5);}
    }
    catch (exception ex){
        std::cout<<ex.what()<<std::endl;
        return;
    }

    double buffer = 0.0;
    for (int m=0; m<line; ++m){
        buffer = copyElement(m,col_1);
        setElement(copyElement(m, col_2), m, col_1);
        setElement(buffer, m, col_2);
    }
}

void Matrix::print(){
    for (int k=0; k<size; ++k){
        std::cout<<data[k]<<" ";
        if((k+1)%col==0){std::cout<<std::endl;}
    }
    std::cout<<std::endl;
}

void Matrix::toGaus(int* swapCount) {
    try {
        if (line!=col||size==1) {throw exception(3);}

        double mn = 0.0;

        for (int i=0; i<line; ++i){
            int diagPos = i + col*i;
            int maxPos = maxPosInCol(diagPos);
            if (data[maxPos]==0) {throw exception(6);}
            if (data[diagPos]==0){
                swapLines(getLine(maxPos), getLine(diagPos));
                if(swapCount!= nullptr) {(*swapCount)++;}
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
    catch (exception ex){
        std::cout<<ex.what()<<std::endl;
        return;
    }

}

double Matrix::det() {
    Matrix local(*this);
    int swapCount=0;
    int* pswapCount = &swapCount;
    local.toGaus(pswapCount);
    double det=1.0;
    for (int m = 0; m<line; m++){
        det*=local.copyElement(m,m);
    }
    if (swapCount % 2 ==1) {det*=-1;}
    return det;
}

double Matrix::trace() {
    try {if (line!=col||size==1) {throw exception(3);} }
    catch (exception ex){
        std::cout<<ex.what()<<std::endl;
        return 0.0;
    }

    double tr = 0.0;
    for (int m = 0; m<this->line; m++){
        tr+=this->copyElement(m,m);
    }
    return tr;
}

Matrix& Matrix::operator=(const Matrix &mat) {
    if (this == &mat) {return *this;}

    try {
        if (this->line != mat.line || this->col != mat.col) {throw exception(3);}
    }
    catch (exception ex){
        std::cout<<ex.what()<<std::endl;
        return *this;
    }

    for (int k = 0; k < size; k++){
        this->data[k]=mat.data[k];
    }
    return *this;
}

Matrix& Matrix::operator=(Matrix &&mat) {
    if (this == &mat) {return *this;}

    try {
        if (this->line != mat.line || this->col != mat.col) {throw exception(3);}
    }
    catch (exception ex){
        std::cout<<ex.what()<<std::endl;
        return *this;
    }

    this->data=mat.data;
    mat.data = nullptr;
    return *this;
}

Matrix Matrix::operator+(const Matrix &mat) {
    try {
        if (this->line != mat.line || this->col != mat.col) {throw exception(3);}
    }
    catch (exception ex){
        std::cout<<ex.what()<<std::endl;
        return *this;
    }

    Matrix S(*this);
    for(int k=0; k<S.size; k++){
        S.data[k]+=mat.data[k];
    }
    return S;
}

Matrix Matrix::operator-(const Matrix &mat) {
    try {
        if (this->line != mat.line || this->col != mat.col) {throw exception(3);}
    }
    catch (exception ex){
        std::cout<<ex.what()<<std::endl;
        return *this;
    }

    Matrix S(*this);
    for(int k=0; k<S.size; k++){
        S.data[k]-=mat.data[k];
    }
    return S;
}

Matrix Matrix::operator*(const Matrix &mat) {
    try {
        if (this->col != mat.line) {throw exception(3);}
    }
    catch (exception ex){
        std::cout<<ex.what()<<std::endl;
        return *this;
    }

    Matrix C(this->line,this->col);
    for (int m =0; m<this->line; m++){
        for (int n =0; n<mat.col; n++){
            for (int k = 0; k < this->col; k++){
                C.getElement(m,n) += this->copyElement(m,k) * mat.copyElement(k,n);
            }
        }
    }
    return C;
}