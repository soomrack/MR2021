#include <iostream>
#include <cmath>
#include "matrix.h"


Matrix::Matrix(unsigned int height,unsigned int width, double value){
    // try to allocate memory
    alloc_memory(height, width);

    // if allocating was successful then initialize height, width
    // and all elements of array with the "value"
    if (data_1d != nullptr){
        this->height = height;
        this->width = width;
        for (int i = 0; i < height * width; i++) {
            data_1d[i] = value;
        }
    }
}


Matrix::Matrix(unsigned int height, unsigned int width, MatrixType type){

    // try to allocate memory
    alloc_memory(height, width);

    // if allocating was successful then initialize height, width
    // and all elements of array according to matrix type
    if (data_1d != nullptr) {
        this->height = height;
        this->width = width;

        switch (type){
            case IDENTITY:
                set_identity();
                break;
            case ONES:
                set_ones();
                break;
            case RANDOM:
                set_random();
                break;
            case ZEROS:
            default:
                set_zeros();
                break;
        }
    }
}

Matrix::Matrix(double* arr, unsigned int lines, unsigned int cols){
    // try to allocate memory
    alloc_memory(lines, cols);

    // if allocating was successful then initialize height, width
    // and copying array in a new allocated place
    if (data_1d != nullptr){
        height = lines;
        width = cols;
        memcpy(data_1d, arr, height * width * sizeof(double));
    }
}

Matrix::~Matrix(){
    free_memory();
}

Matrix::Matrix(const Matrix &other){

    // try to allocate memory
    alloc_memory(other.height, other.width);

    // if allocating was successful then copy height, width
    // and copying array in a new allocated place
    if (data_1d != nullptr) {
        height = other.height;
        width = other.width;
        memcpy(data_1d, other.data_1d, height * width * sizeof(double));
    }
}

Matrix::Matrix(Matrix&& other) noexcept{
    height = other.height;
    width = other.width;

    // giving rights to access the moving memory
    data_1d = other.data_1d;
    data_2d = other.data_2d;

    // prohibit other matrix to access the memory
    other.data_1d = nullptr;
    other.data_2d = nullptr;
}

// overload of operator "=" for copying
Matrix& Matrix::operator= (const Matrix& other){

    // if is the same matrix then return its pointer
    if (this == &other){
        return *this;
    }

    // free old memory
    free_memory();

    // try to allocate memory
    alloc_memory(height, width);

    // if allocating was successful then copy height, width
    // and copying array in a new allocated place
    if (data_1d != nullptr) {
        height = other.height;
        width = other.width;
        memcpy(data_1d, other.data_1d, height * width * sizeof(double));
    }
    return *this;
}

// overload of operator "=" for moving
Matrix& Matrix::operator= (Matrix&& other) noexcept{
    if (this == &other){
        return *this;
    }
    free_memory();

    height = other.height;
    width = other.width;

    data_1d = other.data_1d;
    data_2d = other.data_2d;

    other.data_1d = nullptr;
    other.data_2d = nullptr;
    return *this;
}

// set the value of matrix in corresponding coordinates
int Matrix::set(unsigned int row, unsigned int col, double value){

    // if row or col is out of borders of the array then do nothing and return 1
    if ((row >= this->height) || (col >= this->width)) {
        return 1;
    }

    // else set value in a correct cell and return 0
    this->data_2d[row][col] = value;
    return 0;
}


// get the value from corresponding coordinates
double Matrix::get(unsigned int row, unsigned int col) {

    // if row or col is out of borders of the array then return NaN
    if ((row >= this->height) || (col >= this->width)) {
        return std::nan("1");
    }
    // else return the correct value of the cell
    return this->data_2d[row][col];
}

// overload of operator "+" for two matrices
Matrix Matrix::operator+ (const Matrix& other){

    // if these matrices are not compatible then return an empty matrix
    if ((this->height != other.height) || (this->width != other.width)){
        return Matrix();
    }

    // create result variable
    Matrix result(this->height, this->width);

    // apply addition for each element
    for (int row = 0; row < this->height; row++){
        for (int col = 0; col < this->width; col++){
            result.data_2d[row][col] = this->data_2d[row][col] + other.data_2d[row][col];
        }
    }
    return result;
}

unsigned int Matrix::get_height(){
    return height;
}
unsigned int Matrix::get_width(){
    return width;
}

// overload of operator "-" for two matrices
Matrix Matrix::operator- (const Matrix& other){

    // if these matrices are not compatible then return an empty matrix
    if ((this->height != other.height) || (this->width != other.width)){
        return Matrix();
    }

    // create result variable
    Matrix result(this->height, this->width);

    // apply substraction for each element
    for (int row = 0; row < this->height; row++){
        for (int col = 0; col < this->width; col++){
            result.data_2d[row][col] = this->data_2d[row][col] - other.data_2d[row][col];
        }
    }
    return result;
}

// overload of operator "*" for two matrices
Matrix Matrix::operator* (const Matrix& other){
    // if these matrices are not compatible then return an empty matrix
    if (this->width != other.height){
        return Matrix();
    }

    // create result variable
    Matrix result(this->height, other.width);

    // multiply
    for (int row = 0; row < this->height; row++){
        for (int col = 0; col < other.width; col++){
            result.data_2d[row][col] = 0;
            for (int i = 0; i < other.height; i++){
                result.data_2d[row][col] += this->data_2d[row][i] * other.data_2d[i][col];
            }
        }
    }
    return result;
}

// find trace of matrix
double Matrix::tr(){
    double tr = 0.0;
    for (int i = 0; i < std::min(this->height, this->width); i++){
        tr += this->data_2d[i][i];
    }
    return tr;
}

// find determinant of matrix using forward elimination of Gaussian elimination
double Matrix::det(){

    // if the matrix is not square, assume that determinant can not be found
    if (this->width != this->height) {
        return std::nan("1");
    }
    // if width is zero, computation is not needed, and it can be assumed that det is zero
    if (width == 0){
        return 0.0;
    }
    // create temporary matrix in order not to change values in original matrix
    Matrix tmp_matrix(*this);

    // apply forward elimination (make matrix upper triangular)
    tmp_matrix.apply_forward_elimination();

    // fing determinant as multiplying of elements of the main diagonal of the resulting matrix
    double determinant = 1.0;
    for (int diag_elem = 0; diag_elem < width; diag_elem++){
        determinant *= tmp_matrix.data_2d[diag_elem][diag_elem];
    }
    return determinant;
}

// overload of operator "<<" for matrix output
std::ostream& operator<< (std::ostream &out, const Matrix& m){
    for (int i = 0; i < m.height; i++){
        for (int j = 0; j < m.width; j++){
            out << m.data_2d[i][j] << " ";
        }
        out << '\n';
    }
    return out;
}

// print matrix in std::cout
void Matrix::print(){
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            std::cout << data_2d[i][j] << " ";
        }
        std::cout << '\n';
    }
}

void Matrix::set_identity(){
    for (int i = 0; i < height * width; i++){
        if ((i % height == i / height)){
            data_1d[i] = 1.0;
        }
        else{
            data_1d[i] = 0.0;
        }
    }
}

void Matrix::set_ones(){
    for (int i = 0; i < height * width; i++){
        data_1d[i] = 1.0;
    }
}

void Matrix::set_zeros(){
    for (int i = 0; i < height * width; i++){
        data_1d[i] = 0.0;
    }
}

void Matrix::set_random(){
    for (int i = 0; i < height * width; i++){
        data_1d[i] = rand();
    }
}

// apply the part of the Gaussian elimination called forward elimination
// in order to transform the square matrix into an upper triangular matrix
void Matrix::apply_forward_elimination(){

    // go through each element of the main diagonal
    for (int diag_elem = 0; diag_elem < width; diag_elem++){

        // if diagonal element is zero, computation can not continue
        // and because of that this situation dont have impact on determinant
        // (for this matrix determinant is zero) function just stops (may be it is needed to be improved)
        if (data_2d[diag_elem][diag_elem] == 0){
            return;
        }

        // go through each row placed bottom diagonal element
        for (int row = diag_elem + 1; row < height; row++){

            // create coefficient that will be multiplied with row,
            // that consists current diagonal element
            double coef = data_2d[row][diag_elem] / data_2d[diag_elem][diag_elem];

            // subtract from considered row another row, that consists current diagonal element
            // and which multiplied with coefficient
            for (int col = diag_elem; col < width; col++){
                data_2d[row][col] -= coef * data_2d[diag_elem][col];
            }
        }
    }
}

// allocate memory for matrix
void Matrix:: alloc_memory(unsigned int height, unsigned int width){

    // if any dimension is zero then not to allocate memory
    // and leave data_1d and data_2d with default value (nullptr)
    if (width == 0 || height == 0){
        return;
    }

    // try to allocate new memory
    try{
        data_1d = new double [height * width];
        data_2d = new double* [height];
    }
    // if something is wrong then make data_1d and data_2d nullptr and return
    catch (std::bad_alloc const&){
        data_1d =  nullptr;
        data_2d =  nullptr;
        return;
    }

    // if it was ok, make data_2d a correct 2d array
    for (int row = 0; row < height; row++) {
        data_2d[row] = &data_1d[row * width];
    }
}

// free memory for matrix
void Matrix::free_memory(){
    if (data_1d != nullptr)
        delete[] data_1d;
}
