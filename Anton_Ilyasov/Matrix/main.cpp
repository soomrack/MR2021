﻿#include <iostream>
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
	Matrix Cc(2, 2, 1);

	cout << Aa.trace() << endl;

	Matrix D = Aa * Bb;
	D.print();

	D = Aa + Bb;
	D.print();

	cout << Aa.trace() << endl;
	cout << Aa.det(Aa) << endl;

	Bb = Cc;
	Bb.print();
	
	Aa.minor(2, 2, Aa).print();
	cout << Aa.minor(2, 2, Aa).det(Aa) << endl;

	return 0;
}