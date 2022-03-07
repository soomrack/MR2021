#include <iostream>
#include "Matrix_liba.h"
#include "Matrix_liba.cpp"
using namespace std;

int main()
{
    double test_arr1[9] = {1,2,3,10,5,7,4,4,1};

    Matrix F (3,3);

    F.create_matrix(test_arr1);

    F.display();

    double k = F.determinant();

    cout << k << endl;

    double test_arr2[6] = {6,5,4,3,2,1};

    Matrix S (3,2);

    S.create_matrix(test_arr2);

    S.display();

    Matrix Th=F*S;

    Th.display();

    return 0;
}