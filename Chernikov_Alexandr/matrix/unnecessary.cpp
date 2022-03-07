#include <cmath>
#include "matrix.h"

// find determinant of matrix using recursive algorithm
double Matrix::det(){
    if (this->width != this->height) {
        return std::nan("1");
    }
    if (height == 1){
        return this->data_2d[0][0];
    }
    Matrix minor_matrix(this->height - 1, this->width - 1);
    double determinant = 0;

    for (int orig_col = 0; orig_col < this->width; orig_col++){
        for (int row = 1; row < this->width; row++){
            for (int col = 0; col < this->width; col++){

                if (col < orig_col)
                    minor_matrix.data_2d[row - 1][col] = this->data_2d[row][col];
                if (col > orig_col)
                    minor_matrix.data_2d[row - 1][col - 1] = this->data_2d[row][col];
            }
        }

        if (orig_col % 2 == 0){
            determinant += this->data_2d[0][orig_col] * minor_matrix.det();
        }
        else{
            determinant -= this->data_2d[0][orig_col] * minor_matrix.det();
        }
    }
    return determinant;
}

void constructor_test(unsigned int height = 0, unsigned int width = 0, double value = 0.0){
    std::cout << "Initializing matrix with" << std::endl;
    std::cout << "height = " << height << std::endl;
    std::cout << "width = " << width << std::endl;
    std::cout << "value = " << value << std::endl;

    Matrix test_matrix(height, width, value);
    std::cout << test_matrix << std::endl;
/*
    if (height != test_matrix.get_height() && height * width > 0){
        std::cerr << "original height = " << height << '\n';
        std::cerr << "resulting height = " << test_matrix.get_height() << '\n';
        return;
    }

    if (width != test_matrix.get_width() && height * width > 0){
        std::cerr << "original width = " << width << '\n';
        std::cerr << "resulting width = " << test_matrix.get_width() << '\n';
        return;
    }

    for (int row = 0; row < height; row++){
        for (int col = 0; col < width; col++){
            if (test_matrix.get(row, col) != value){
                std::cerr << "original value = " << width << '\n';
                std::cerr << "resulting data_2d["<< row <<"]["<< col <<"] = " << test_matrix.get(row, col) << '\n';
                return;
            }
        }
    }*/
}
