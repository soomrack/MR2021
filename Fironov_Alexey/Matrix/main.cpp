#include <iostream>
#include "matrix_lib.h"

int main() {
    Matrix matrix (3,3);

    matrix.set_cell(1,1,2);
    matrix.set_cell(1,2,5);
    matrix.set_cell(1,3,7);
    matrix.set_cell(2,1,6);
    matrix.set_cell(2,2,3);
    matrix.set_cell(2,3,4);
    matrix.set_cell(3,1,5);
    matrix.set_cell(3,2,-2);
    matrix.set_cell(3,3,-3);

    Matrix reverse (matrix);
    reverse.get_reverse();
    double temp = matrix.get_cell(2,3);
    reverse.visual();
    std::cout<<"\n\n";
    std::cout<<temp;

    return 0;
}
