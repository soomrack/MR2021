#include <iostream>
#include <string.h>
#include"MatrixLibryary.h"

int main()
{
	int A[9] = { 1,2,3,4,5,6,7,8,9 };
	int B[12] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
	int C[9] = { 1,1,1,1,1,1,1,1,1 };

	Matrix M1(3, 3, A);
	Matrix M2(10, 10, 1);
	Matrix M3(3, 3, C);

	M1 = M3;
	M1.print();
	cout << M1.trace();

	cout<<M1.det();
	M2.print();

	Matrix M4 = M2;
	M4.print();

	Matrix M5 = M1 + M3;
	M5.print();
	Matrix M6 = M1 * M3;
	M6.print();
}
