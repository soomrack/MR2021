#include <iostream>
#include "Matrix_liba.h"
#include "Matrix_liba.cpp"
using namespace std;

int main()
{
    double test_arr1[9] = {1,2,3,10,5,7,4,4,1};

    Matrix F (3,3);

    F.Create_Matrix(test_arr1);

    F.Display();

    double k = F.Determinant();

    cout << k << endl;

    double test_arr2[6] = {6,5,4,3,2,1};

    Matrix S (3,2);

    S.Create_Matrix(test_arr2);

    S.Display();

    Matrix Th=F*S;

    Th.Display();

    return 0;
}