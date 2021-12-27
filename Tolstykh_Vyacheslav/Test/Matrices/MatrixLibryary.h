#include <string.h>
using namespace std;

class Matrix
{
private:
	int width;
	int height;
	int* data;
public:
	Matrix();
	Matrix(int width, int height);
	Matrix(int width, int height, int* other);
	Matrix(int width, int height, int type);
	Matrix(const Matrix& other);
	Matrix(Matrix&& other) noexcept;
	void print();
	Matrix operator +(const Matrix& other);
	Matrix operator *(const Matrix& other);
	Matrix& operator =(const Matrix& other);
	int trace();
	double minor_det(int n, int m);
	double det();
	~Matrix(); 
};