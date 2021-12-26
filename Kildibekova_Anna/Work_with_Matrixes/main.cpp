#include "matrix_Lib.h"
#include <iostream>

int main() {

    Matrix d(5, 1, IDENTITY);
    d.print();
    Matrix e(5, 5, IDENTITY);
    e.print(std::string("Матрица e: "));
    Matrix f(5, 5, IDENTITY);
    f.print(std::string("Матрица f: "));

    d = e*f;
    d.print(std::string("Матрица d: "));

    std::cout<<"След d:"<<d.trace()<<std::endl;
    std::cout<<"Определитель d:"<<d.determinant()<<std::endl;

    return 0;
}