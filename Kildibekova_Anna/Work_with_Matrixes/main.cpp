#include "matrix_Lib.h"
#include <iostream>


int main() {

    double a[3][3] = {{8.0, 0.0, 0.0},
                      {4.0, 4.0, 5.0},
                      {3.0, 3.0, 2.0}};
    Matrix A(3, 3, a[0]);
    A.print("Матрица А:");
    std::cout << "След A:" << A.trace() << std::endl;
    std::cout << "Определитель A:" << A.determinant() << std::endl;

    Matrix d(5, 1, IDENTITY);
    d.print();
    Matrix e(3, 5, IDENTITY);
    e.print(std::string("Матрица e: "));
    Matrix f(5, 5, IDENTITY);
    f.print(std::string("Матрица f: "));

    d = A * e;
    d.print(std::string("Матрица d: "));
    std::cout << "След d:" << d.trace() << std::endl;

    return 0;
}