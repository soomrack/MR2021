#include <iostream>

typedef enum{
    IDENTITY_MATRIX,
    UPPER_TRIANG_MATRIX_OF_ONES,
    LOWER_TRIANG_MATRIX_OF_ONES,
} SpecialType;


class Matrix{
private:
    int height;
    int width;
    double** data;
public:
    Matrix(int height, int width);
    Matrix(int height, int width, SpecialType type);
    Matrix(int height, int width, double value);
    Matrix(const Matrix& m);
    Matrix(Matrix&& m) noexcept;
    Matrix& operator= (const Matrix& m);
    ~Matrix();
public:
    double get(int i, int j);
    void set(int i, int j, double value);
public:
    Matrix operator+ (const Matrix& m);
    Matrix operator- (const Matrix& m);
    Matrix operator* (const Matrix& m);
public:
    double tr();
    double det();
public:
    friend std::ostream& operator<< (std::ostream &out, const Matrix& m);
    void print();
};

Matrix::Matrix(int height, int width){
    this->height = height;
    this->width = width;
    data = new double* [height];
    for (int i = 0; i < height; i++){
        data[i] = new double[width];
    }

    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            data[i][j] = 0.0;
        }
    }
}

Matrix::Matrix(int height, int width, SpecialType type){
    this->height = height;
    this->width = width;
    data = new double* [height];
    for (int i = 0; i < height; i++){
        data[i] = new double[width];
    }

    switch (type){
        case IDENTITY_MATRIX:
            for (int i = 0; i < height; i++){
                for (int j = 0; j < width; j++){
                    if (i == j){
                        data[i][j] = 1.0;
                    }
                    else{
                        data[i][j] = 0.0;
                    }
                }
            }
            break;
        case UPPER_TRIANG_MATRIX_OF_ONES:
            for (int i = 0; i < height; i++){
                for (int j = 0; j < width; j++){
                    if (i <= j){
                        data[i][j] = 1.0;
                    }
                    else{
                        data[i][j] = 0.0;
                    }
                }
            }
            break;
        case LOWER_TRIANG_MATRIX_OF_ONES:
            for (int i = 0; i < height; i++){
                for (int j = 0; j < width; j++){
                    if (i >= j){
                        data[i][j] = 1.0;
                    }
                    else{
                        data[i][j] = 0.0;
                    }
                }
            }
            break;
        default:
            for (int i = 0; i < height; i++){
                for (int j = 0; j < width; j++){
                    data[i][j] = 0.0;
                }
            }
    }
}

Matrix::Matrix(int height, int width, double value){
    this->height = height;
    this->width = width;
    data = new double* [height];
    for (int i = 0; i < height; i++){
        data[i] = new double[width];
    }

    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            data[i][j] = value;
        }
    }
}

Matrix::~Matrix(){
    for (int i = 0; i < height; i++){
        delete[] data[i];
    }
    delete[] data;
}

Matrix::Matrix(const Matrix &m){
    height = m.height;
    width = m.width;
    data = new double* [height];
    for (int i = 0; i < height; i++){
        data[i] = new double[width];
    }
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            data[i][j] = m.data[i][j];
        }
    }
}

Matrix::Matrix(Matrix&& m) noexcept{
    height = m.height;
    width = m.width;
    data = m.data;
    m.data = nullptr;
}

Matrix& Matrix::operator= (const Matrix& m){
    if (this == &m){
        return *this;
    }

    for (int i = 0; i < height; i++){
        delete[] data[i];
    }
    delete[] data;

    this->height = m.height;
    this->width = m.width;
    data = new double* [height];
    for (int i = 0; i < height; i++){
        data[i] = new double[width];
    }

    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            data[i][j] = m.data[i][j];
        }
    }
    return *this;
}

void Matrix::set(int i, int j, double value){
    this->data[i][j] = value;
}

double Matrix::get(int i, int j) {
    return this->data[i][j];
}

Matrix Matrix::operator+ (const Matrix& m){
    Matrix result(this->height, this->width);
    for (int i = 0; i < this->height; i++){
        for (int j = 0; j < this->width; j++){
            result.data[i][j] = this->data[i][j] + m.data[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator- (const Matrix& m){
    Matrix result(this->height, this->width);
    for (int i = 0; i < this->height; i++){
        for (int j = 0; j < this->width; j++){
            result.data[i][j] = this->data[i][j] - m.data[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator* (const Matrix& m){
    Matrix result(this->height, m.width);
    for (int i = 0; i < this->height; i++){
        for (int j = 0; j < m.width; j++){
            result.data[i][j] = 0;
            for (int k = 0; k < m.height; k++){
                result.data[i][j] += this->data[i][k] * m.data[k][j];
            }
        }
    }
    return result;
}

double Matrix::tr(){
    double tr = 0.0;
    for (int i = 0; i < this->height; i++){
        tr += this->data[i][i];
    }
    return tr;
}

double Matrix::det(){
    if (height == 1){
        return this->data[0][0];
    }
    Matrix minor_matrix(this->height - 1, this->width - 1);
    double determinant = 0;
    for (int i = 0; i < this->width; i++){
        int j = 0;
        int j1 = 0;
        while (j < this->width){
            if (j != i){
                for (int k = 0; k < minor_matrix.width; k++)
                    minor_matrix.data[k][j1] = this->data[k][j1];
                j1++;
            }
            j++;
        }

        if (i % 2 == 0){
            determinant += this->data[0][i] * minor_matrix.det();
        }
        else{
            determinant -=  this->data[0][i] * minor_matrix.det();
        }
    }
    return determinant;
}

std::ostream& operator<< (std::ostream &out, const Matrix& m){
    for (int i = 0; i < m.height; i++){
        for (int j = 0; j < m.width; j++){
            out << m.data[i][j] << " ";
        }
        out << '\n';
    }
    return out;
}

void Matrix::print(){
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            std::cout << data[i][j] << " ";
        }
        std::cout << '\n';
    }
}
