#include <iostream>
#include "Matrix.h"

using namespace std;

Matrix::Matrix(int height, int width) {
    this->height = height;
    this->width = width;
    data = (int *) malloc(height * width * sizeof(int));
}

void Matrix::MatrixRandom(int height, int width) {
    for (int i = 0; i < height * width; i++)
        data[i] = rand()%10;
}

void Matrix::MatrixOut(int width, int height) {
    for (int i = 0; i < height*width; i++) {
        std::cout << data[i] << " ";
        if ((i+1) % width == 0)
            std::cout << std::endl;
    }
}

int Matrix::MatrixSizeHeight() {
    return height;
}

int Matrix::MatrixSizeWidth() {
    return width;
}

void Matrix::FreeMatrix(int** data){
    if (height != 0 && width != 0 && data != NULL)
        delete[] *data;
}

void Matrix::MatrixSum(Matrix A, Matrix B) {
    if ((A.MatrixSizeHeight() != B.MatrixSizeHeight()) && (A.MatrixSizeWidth() != B.MatrixSizeWidth())) {
        cout << "\n\nERROR\n\nMatrix A and B must be the same size";
        exit(0);
    } else {
        cout << "\nFinal matrix:\n";
        for (int i = 0; i < A.MatrixSizeHeight() * A.MatrixSizeWidth(); i++)
            A.data[i] = A.data[i] + B.data[i];
        A.MatrixOut(A.MatrixSizeWidth(), A.MatrixSizeHeight());
    }
}

void Matrix::MatrixSub(Matrix A, Matrix B) {
    if ((A.MatrixSizeHeight() == B.MatrixSizeHeight()) && (A.MatrixSizeWidth() == B.MatrixSizeWidth())) {
        cout << "\n\nERROR\n\nMatrix A and B must be the same size";
        exit(0);
    } else {
        cout << "\nFinal matrix:\n";
        for (int i = 0; i < A.MatrixSizeWidth() * A.MatrixSizeHeight(); i++)
            A.data[i] = A.data[i] - B.data[i];
        A.MatrixOut(A.MatrixSizeWidth(), A.MatrixSizeHeight());
    }
}

void Matrix::MatrixMul(Matrix A, Matrix B) {
    int sum = 0;
    if (A.MatrixSizeWidth() == B.MatrixSizeHeight()) {
        cout << "\n\nERROR\n\nMatrix A and B must be commutative (columns A = rows B)";
        exit(0);
    } else {
        cout << "\nFinal matrix:\n";
        Matrix C(A.MatrixSizeHeight(), B.MatrixSizeWidth());
        for (int i = 0, j = 0; i < A.MatrixSizeHeight() * B.MatrixSizeWidth(); i++) {
            for (int k = 0; k < A.MatrixSizeWidth(); k++)
                sum += A.data[k+j*A.MatrixSizeWidth()] * B.data[i - j * B.MatrixSizeWidth() + k * B.MatrixSizeWidth()];
            C.data[i] = sum;
            sum = 0;
            if ((i+1) % (A.MatrixSizeWidth()+1)==0) j++;
        }
        C.MatrixOut(C.MatrixSizeWidth(), C.MatrixSizeHeight());
    }
}