#include <iostream>
#include <ctime>
#include <cmath>
#include "matrix.h"

// Matrix constructor, which creates a matrix with shape (height, width)
// and fills it with the parameter value.
Matrix::Matrix(unsigned int height,unsigned int width, double value){
    this->height = height;
    this->width = width;
    data = alloc_memory(height, width);

    for (int row = 0; row < height; row++){
        for (int col = 0; col < width; col++){
            data[row][col] = value;
        }
    }
}


// Matrix constructor, which creates a matrix with shape (height, width)
// and fills it using special type.
Matrix::Matrix(unsigned int height, unsigned int width, SpecialType type){
    this->height = height;
    this->width = width;
    data = alloc_memory(height, width);

    switch (type){
        case IDENTITY:
            for (int row = 0; row < height; row++){
                for (int col = 0; col < width; col++){
                    if (row == col){
                        data[row][col] = 1.0;
                    }
                    else{
                        data[row][col] = 0.0;
                    }
                }
            }
            break;
        case ONES:
            for (int row = 0; row < height; row++){
                for (int col = 0; col < width; col++){
                    data[row][col] = 1.0;
                }
            }
            break;
        case RANDOM:
            srand(time(nullptr));
            for (int row = 0; row < height; row++){
                for (int col = 0; col < width; col++){
                    data[row][col] = rand();
                }
            }
            break;
        case ZEROS:
        default:
            for (int row = 0; row < height; row++){
                for (int col = 0; col < width; col++){
                    data[row][col] = 0.0;
                }
            }
            break;
    }
}

// Destructor
Matrix::~Matrix(){
    free_memory(data);
}

// Copy constructor
Matrix::Matrix(const Matrix &m){
    height = m.height;
    width = m.width;
    data = alloc_memory(height, width);

    for (int row = 0; row < height; row++){
        for (int col = 0; col < width; col++){
            data[row][col] = m.data[row][col];
        }
    }
}

// Move constructor
Matrix::Matrix(Matrix&& m) noexcept{
    height = m.height;
    width = m.width;
    data = m.data;
    m.data = nullptr;
}

// overload of operator "=" for copying
Matrix& Matrix::operator= (const Matrix& m){
    if (this == &m){
        return *this;
    }

    free_memory(data);
    this->height = m.height;
    this->width = m.width;
    data = alloc_memory(height, width);

    for (int row = 0; row < height; row++){
        for (int col = 0; col < width; col++){
            data[row][col] = m.data[row][col];
        }
    }
    return *this;
}

// overload of operator "=" for moving
Matrix& Matrix::operator= (Matrix&& m) noexcept{
    if (this == &m){
        return *this;
    }
    free_memory(data);
    height = m.height;
    width = m.width;

    data = m.data;
    m.data = nullptr;
    return *this;
}

// set the value in corresponding coordinates
// if this coordinates exists, return 0
// else return 1
int Matrix::set(unsigned int row, unsigned int col, double value){
    if ((row >= this->height) || (col >= this->width)) {
        return 1;
    }
    this->data[row][col] = value;
    return 0;
}

// get the value from corresponding coordinates
// if this coordinates exists, return value, placed in matrix
// else return NaN
double Matrix::get(unsigned int row, unsigned int col) {
    if ((row >= this->height) || (col >= this->width)) {
        return std::nan("1");
    }
    return this->data[row][col];
}

// overload of operator "+" for two matrices
// if the matrices are compatible, return result of addition
// else return matrix with shapes (0, 0)
Matrix Matrix::operator+ (const Matrix& m){
    if ((this->height != m.height) || (this->width != m.width)){
        return Matrix();
    }
    Matrix result(this->height, this->width);

    for (int row = 0; row < this->height; row++){
        for (int col = 0; col < this->width; col++){
            result.data[row][col] = this->data[row][col] + m.data[row][col];
        }
    }
    return result;
}

// overload of operator "-" for two matrices
// if the matrices are compatible, return result of subtraction
// else return matrix with shapes (0, 0)
Matrix Matrix::operator- (const Matrix& m){
    if ((this->height != m.height) || (this->width != m.width)){
        return Matrix();
    }
    Matrix result(this->height, this->width);

    for (int row = 0; row < this->height; row++){
        for (int col = 0; col < this->width; col++){
            result.data[row][col] = this->data[row][col] - m.data[row][col];
        }
    }
    return result;
}

// overload of operator "*" for two matrices
// if the matrices are compatible, return result of multiplication
// else return matrix with shapes (0, 0)
Matrix Matrix::operator* (const Matrix& m){
    if (this->width != m.height){
        return Matrix();
    }
    Matrix result(this->height, m.width);
    for (int row = 0; row < this->height; row++){
        for (int col = 0; col < m.width; col++){
            result.data[row][col] = 0;
            for (int i = 0; i < m.height; i++){
                result.data[row][col] += this->data[row][i] * m.data[i][col];
            }
        }
    }
    return result;
}

// find trace of matrix
double Matrix::tr(){
    if (this->height == 0 || this->width == 0){
        return 0.0;
    }

    double tr = 0.0;
    for (int i = 0; i < std::min(this->height, this->width); i++){
        tr += this->data[i][i];
    }
    return tr;
}

// find determinant of matrix using recursive algorithm
double Matrix::det(){
    if (this->width != this->height) {
        return std::nan("1");
    }
    if (height == 1){
        return this->data[0][0];
    }
    Matrix minor_matrix(this->height - 1, this->width - 1);
    double determinant = 0;

    for (int orig_col = 0; orig_col < this->width; orig_col++){
        for (int row = 1; row < this->width; row++){
            for (int col = 0; col < this->width; col++){

                if (col < orig_col)
                    minor_matrix.data[row - 1][col] = this->data[row][col];
                if (col > orig_col)
                    minor_matrix.data[row - 1][col - 1] = this->data[row][col];
            }
        }

        if (orig_col % 2 == 0){
            determinant += this->data[0][orig_col] * minor_matrix.det();
        }
        else{
            determinant -=  this->data[0][orig_col] * minor_matrix.det();
        }
    }
    return determinant;
}

// overload of operator "<<" for matrix output
std::ostream& operator<< (std::ostream &out, const Matrix& m){
    for (int i = 0; i < m.height; i++){
        for (int j = 0; j < m.width; j++){
            out << m.data[i][j] << " ";
        }
        out << '\n';
    }
    return out;
}

// print matrix in std::cout
void Matrix::print(){
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            std::cout << data[i][j] << " ";
        }
        std::cout << '\n';
    }
}

// allocate memory for matrix
double** Matrix:: alloc_memory(unsigned int new_height, unsigned int new_width){
    if (new_width == 0 || new_height == 0){
        return nullptr;
    }
    double* tmp_data_ptr = new double [new_height * new_width];
    double** new_data = new double* [new_height];
    for (int row = 0; row < new_height; row++){
        new_data[row] = &tmp_data_ptr[row * new_width];
    }
    return new_data;
}

// free memory for matrix
void Matrix::free_memory(double** freeing_data){
    if (height != 0 && width != 0 && data != nullptr)
        delete[] *freeing_data;
}
