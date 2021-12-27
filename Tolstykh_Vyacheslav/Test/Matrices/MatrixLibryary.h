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
	Matrix(unsigned int width, unsigned int height);
	Matrix(unsigned int width, unsigned int height, int* other);
	Matrix(unsigned int width, unsigned int height, int type);
	Matrix(const Matrix& other);
	Matrix(Matrix&& other) noexcept;
	void print();
	Matrix operator +(const Matrix& other);
	Matrix operator -(const Matrix& other);
	Matrix operator *(const Matrix& other);
	Matrix& operator =(const Matrix& other);
	void set_zero();
	void set_one();
	int trace();
	double minor_det(unsigned int n, unsigned int m);
	double det();
	~Matrix(); 
};