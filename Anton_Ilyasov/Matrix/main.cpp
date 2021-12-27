#include <iostream>
#include <string.h>
#include"Matrix.Libryary.h"

int main() //пример работы с библиотекой матриц
{
	int A[4][3] = { 1,2,3,
                        4,5,6,
                        7,8,9,
                        10,11,12 };

	int B[3][3] = { -1,-2,-3,
                        -4,-5,-6,
                        -7,-8,-9 };

	Matrix Aa(4, 3, *A);
	Matrix Bb(3, 3, *B);
	Matrix Cc(3, 3, 1);
	Matrix Ab(3, 3, 124);

	Matrix D = Aa * Bb;
	D.print();
	cout << endl;

	Ab.print();
	Ab.set_identity();

	Ab.print();
	Aa.set_identity();
	Aa.print();
	cout << endl;
	Aa.set(0);
	Aa.print();
	cout << endl;
	Aa.set(1);
	Aa.print();
	cout << endl;

	cout << Aa.trace() << endl;
	cout << endl;

	Aa = Cc - Bb;
	Aa.print();
	cout << endl;

	Aa.print();
	Bb.print();
	D = Aa * Bb;
	D.print();
	cout << endl;

	cout << Aa.det(Aa) << endl;
	cout << endl;

	Aa.minor(2, 2, Aa).print();
	cout << endl;
	cout << Aa.minor(2, 2, Aa).det(Aa) << endl;
	cout << endl;

	return 0;
}