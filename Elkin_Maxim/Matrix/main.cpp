#include <iostream>
#include "matrix_lib.h"
using namespace std;

//example of using matrix library
int main() {
    matrix A(3,3);
    A.set_cells_cmd();
    A.get_matrix();

    matrix B(3,3);
    B.set_cells_cmd();
    B.get_matrix();
    cout << "determinant of B: " << B.get_det() << endl;

    matrix C = A + B;
    cout << "sum of A and B" << endl;
    C.get_matrix();

    C = A - B;
    cout << "result of A sub B" << endl;
    C.get_matrix();

    C = A * B;
    cout << "multiplication of A and B" << endl;
    C.get_matrix();

    matrix D = B;
    cout << "matrix D is the same as B" << endl;
    D.get_matrix();

    return 0;
}
