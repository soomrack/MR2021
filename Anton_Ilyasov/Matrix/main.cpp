#include <iostream>
#include <string.h>
#include"Matrix.Libryary.h"



int main()
{
	Matrix A(3, 3, "A");
	Matrix B(2, 2, "B");
	B.Inicialization(B);
	A = B;
	A.Print();
	Matrix C(2, 2, "C");
	C.Inicialization(C);
	A = B * C;
	A = B + C;


	cout << A.Trace()<< endl;
	cout << A.Det(A) << endl;

	return 0;
}