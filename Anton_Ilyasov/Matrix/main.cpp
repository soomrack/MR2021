#include <iostream>
#include <string.h>
#include"Matrix.Libryary.h"



int main()
{
	Matrix A(3, 3, 1);
	A.print();
	Matrix B(2, 2, 1);
	Matrix C(2, 2, 1);

	A = C;
	Matrix D= A + B;

	D.print();

	/*A.print();
	Matrix C(2, 2);

	A = B * C;
	A = B + C;


	cout << A.trace()<< endl;
	cout << A.det(A) << endl; */

	return 0;
}