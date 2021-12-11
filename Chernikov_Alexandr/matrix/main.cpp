#include "matrix.h"
#include <iostream>

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

void constructor_test(unsigned int height, unsigned int width, MatrixType type){
    std::cout << "Initializing matrix with" << std::endl;
    std::cout << "height = " << height << std::endl;
    std::cout << "width = " << width << std::endl;
    std::cout << "type = " << type << std::endl;

    std::cout << Matrix(height, width, type) << std::endl;
}

template <unsigned int lines, unsigned int cols>
void constructor_test(double (&arr)[lines][cols]){
    std::cout << "Initializing matrix with" << std::endl;
    std::cout << "height = " << lines << std::endl;
    std::cout << "width = " << cols << std::endl;

    std::cout << Matrix(lines, cols, &arr[0][0]) << std::endl;
}

double test_array1[2][2] = {{1, 2},
                            {4, 3}};
double test_array2[2][2] = {{2, 2},
                            {2, 2}};
double test_array3[3][3] = {{1, 0, 0},
                            {0, 1, 0},
                            {0, 0, 1}};
double test_array4[2][3] = {{1, 2, 3},
                            {0, 1, 0}};


int main() {
    constructor_test(0, 0, 0);
    constructor_test(-2, -3, 5);
    constructor_test(2, 2, 2);
    constructor_test(2, 2, IDENTITY);
    constructor_test(test_array2);

    return 0;
}
