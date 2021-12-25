#include "matrix_Lib.h"
#include <iostream>

int main() {

    Matrix d(5, 4, identity);
    d.print();
    Matrix e(5, 2);
    e.print(std::string("Матрица e: "));

    d=e;
    d.print(std::string("Матрица d: "));

    std::cout<<"След d:"<<d.trace()<<std::endl;
//    std::cout<<"Определитель d:"<<d.determinant()<<std::endl;

    return 0;
}