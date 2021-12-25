#include "matrix_Lib.h"
#include <string.h>

Matrix::Matrix( int height, int wight, type_of_matrix type){
    cleanly = true;
    this->height = height;
    this->wight = wight;
    memory_allocation();
    if (cleanly) {
        return;
    }
    if (type != zero && type != identity){
        std::cout<<"=> Ошибка инициализации!\n"
        "=> Неверно введены параметры типизированной матрицы."<<std::endl;
        free_memory();
        return;
    }
    for (int cell = 0; cell < height*wight; cell++){
        data[cell]=(double)type;
    }
}

Matrix::Matrix(const Matrix &matrix){
    cleanly = true;
    height = matrix.height;
    wight = matrix.wight;
    memory_allocation();
    if (cleanly) {
        return;
    }
    memcpy(data, matrix.data, height*wight*sizeof(double));
}
Matrix::Matrix(Matrix && matrix){ }

Matrix::~Matrix() {
    free_memory();
}

Matrix & Matrix::operator = (const Matrix &matrix) { }
Matrix & Matrix::operator + (const Matrix &matrix) { }
Matrix & Matrix::operator * (const Matrix &matrix) { }

double Matrix::trace() const {
    if (!check()) {
        return 0.0;
    }
    double trace = 0.0;
    int min;
    if (height < wight) {
        min = height;
    }
    else {
        min = wight;
    }
    for (int i = 0; i < min; i++) {
        trace += data[i + wight];
    }
    return trace;
}
double Matrix::determinant() const { }

void Matrix::print(const std::string &text) const {
    std::cout<<text<<std::endl;
    if (!check()) {
        return;
    }
    for (int cell = 0; cell < height*wight; cell++) {
        std::cout<<data[cell]<<"\t";
        if ((cell+1) % wight == 0) {
            std::cout<<std::endl;
        }
    }
    std::cout<<std::endl;
}

void Matrix::memory_allocation() {
    if (height < 0 || wight < 0 || !cleanly){
        std::cout<<"=> Ошибка выделения памяти!"<<std::endl;
        return;
    }
    data = new double [height*wight];
    if (data == NULL){
        std::cout<<"=> Ошибка выделения памяти!(Возможно,затребованный"
                   "размер памяти слишком большой)"<<std::endl;
        return;
    }
    cleanly = false;
}

void Matrix::free_memory() {
    if(cleanly) {
        std::cout<<"=> Ошибка double-free!"<<std::endl;
        return;
    }
    free(data);
    height = 0;
    wight = 0;
    cleanly = true;
}

bool Matrix::check() const {
    if (cleanly) {
        std::cout<<"=> Матрицы не существует."<<std::endl;
        return false;
    }
    if (wight == 0 || height == 0) {
        std::cout<<"=> Матрица пуста."<<std::endl<<std::endl;
        return false;
    }
    return true;
}