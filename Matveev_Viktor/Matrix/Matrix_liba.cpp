#include <iostream>
#include "Matrix_liba.h"
using namespace std;

double** Matrix::alloc(unsigned int length, unsigned int height)
{
    if (length == 0 || height == 0)
    {
        return nullptr;
    }
    try
    {
        string = new double [length * height];
    }
    catch (bad_alloc const&)
    {
        string = nullptr;
        return nullptr;
    }
    try
    {
        Matr = new double* [length];
    }
    catch (bad_alloc const&)
    {
        string =  nullptr;
        Matr =  nullptr;
        delete[] string;
        return Matr;
    }
    for (unsigned int row = 0; row < length; row++)
    {
        Matr[row] = &string[row * height];
    }
    return Matr;
}
void Matrix::clear_memory()
{
    if (Matr != nullptr)
    {
        delete[] string;
        delete[] Matr;
    }
}

Matrix ::Matrix()
{
    length = 0;
    height = 0;
    Matr = alloc(length, height);
    for (unsigned int pos = 0; pos < length*height; pos++)
    {
        string[pos]=0;
    }
}
Matrix::Matrix(unsigned int length, unsigned int height)
{
    this -> length = length;
    this -> height = height;
    this -> Matr = alloc(length, height);
    for (unsigned int pos = 0; pos < length*height; pos++)
    {
        string[pos]=0;
    }
}
Matrix::Matrix(const Matrix & other)
{
    Matr= alloc(other.length,other.height);

    if (string != nullptr)
    {
        length = other.length;
        height = other.height;
        memcpy(string,other.string,length * height * sizeof(double));
    }
}
Matrix::Matrix(Matrix && other) noexcept
{
    length = other.length;
    height = other.height;
    Matr = other.Matr;
    string = other.string;
    other.Matr = nullptr;
    other.string = nullptr;
}
Matrix :: ~Matrix()
{
    clear_memory();
}

// Copy constructor
Matrix & Matrix :: operator = (const Matrix &other)
{
    if (this == &other)
    {
        return *this;
    }
    clear_memory();
    this->Matr= alloc(length, height);
    if (string != nullptr)
    {
        this -> length = other.length;
        this -> height = other.height;
        memcpy(this -> string,other.string,length * height * sizeof(double));
    }
    return *this;
}
//Transfer constructor
Matrix & Matrix::operator = (Matrix &&other) noexcept
{
    if (this == &other)
    {
        return *this;
    }
    clear_memory();
    length = other.length;
    height = other.height;
    Matr = other.Matr;
    string = other.string;
    other.Matr = nullptr;
    other.string = nullptr;
    return *this;
}
Matrix Matrix :: operator+(const Matrix &other)
{

    if ((this -> length != other.length) || (this -> height != other.height))
    {
        Matrix Answer (0, 0);
        cout << "Something wrong with sizes" << endl;
        return Answer;
    }

    Matrix Answer (length, height);
    for (unsigned int pos = 0; pos < length*height; pos++)
    {
        Answer.string[pos] = string[pos] + other.string[pos];
    }
    return Answer;
}
Matrix Matrix :: operator-(const Matrix &other)
{

    if ((this -> length != other.length) || (this -> height != other.height))
    {
        Matrix Answer (0, 0);
        cout << "Something wrong with sizes" << endl;
        return Answer;
    }

    Matrix Answer (length, height);
    for (unsigned int pos = 0; pos < length*height; pos++)
    {
        Answer.string[pos] = string[pos] - other.string[pos];
    }
    return Answer;
    return Answer;
}
Matrix Matrix :: operator*(const Matrix &other)
{
    if(this -> height != other.length)
    {
        Matrix Answer (0, 0);
        cout << "Something wrong with sizes" << endl;
        return Answer;
    }

    Matrix Answer (length, other.height);

    for (unsigned int row = 0; row < this -> length; row++)
    {
        for (unsigned int col = 0; col < other.height; col++)
        {
            int cell = 0;
            for (unsigned int k = 0; k < this -> height; k++) {
                cell += ((this -> Matr[row][k]) * other.Matr[k][col]);
            }
            Answer.Matr[row][col] = cell;
        }
    }
    return Answer;
}

void Matrix :: create_matrix(double *arr)
{
    int count=0;
    for (int row = 0; row < length; row++)
    {
        for (int col = 0; col < height; col++)
        {
            Matr[row][col] = arr[count];
            count++;
        }
    }
}

void Matrix :: create_matrix_one()
{
    for (unsigned int pos = 0; pos < length; pos++)
    {
        Matr[pos][pos] = 1;
    }
}
void Matrix :: display()
{
    for (unsigned int row = 0; row < length; row++)
    {
        for (unsigned int col = 0; col < height; col++)
        {
            cout.width(4);
            cout << Matr[row][col];
        }
        cout << endl;
    }
    cout << endl;
}
int Matrix :: trace()
{
    double trace_res = 0.0;
    if(height != length)
    {
        cout << "The matrix is not square" << endl;
        return trace_res;
    }

    for (unsigned int pos = 0; pos < length; pos++)
    {
        trace_res += Matr[pos][pos];
    }
    return trace_res;
}
double Matrix :: determinant()
{
    double det = 0.0;

    if (length != height)
    {
        cout << "Something wrong with sizes" << endl;
        return det;
    }
    if (length == 1)
    {
        det = Matr[0][0];
        return det;
    }
    if (length == 2)
    {
        det = Matr[0][0]*Matr[1][1]-Matr[0][1]*Matr[1][0];
        return det;
    }

    Matrix Sup_Matrix (length, height);
    memcpy(Sup_Matrix.Matr[0],Matr[0],length * height * sizeof(double));

    for (unsigned int col = 0; col < Sup_Matrix.height - 1; col++)
    {
        Sup_Matrix.sort_rows(col);
        for (unsigned int row = col+1; row < Sup_Matrix.length; row++)
        {
            if (Sup_Matrix.Matr[col][col] && Sup_Matrix.Matr[row][col])
            {
                double k = 0.0;
                if (Sup_Matrix.Matr[col][col] != 0)
                {
                    k = Sup_Matrix.Matr[row][col]/Sup_Matrix.Matr[col][col];
                }
                else
                {
                    k = Sup_Matrix.Matr[row][col]/0.001;
                }
                for (unsigned int l = col; l < Sup_Matrix.height; l++)
                {
                    Sup_Matrix.Matr[row][l] = Sup_Matrix.Matr[row][l] - (k * Sup_Matrix.Matr[col][l]);
                }
            }
        }
    }
    det = 1;
    for (unsigned int row = 0; row < height; row++)
    {
        det = det * Sup_Matrix.Matr[row][row];
    }
    return det;
}

void Matrix::sort_rows(unsigned int col)
{
    bool toggle = false;
    unsigned int null_counter = 0;
    for (unsigned int row = 0; row < length; row++)
    {
        if (null_counter < length - row)
        {
            toggle = false;
            while(toggle == false)
            {
                if (Matr[row][col] == 0)
                {
                    null_counter = 0;
                    for (unsigned int i = row; i < length; i++)
                    {
                        if (Matr[i][col] == 0)
                        {
                            null_counter++;
                        }
                    }
                    if (null_counter < length - row)
                    {
                        double buf[height];
                        memcpy(buf, Matr[row], sizeof(double) * height);
                        for (unsigned int rem_rows = row + 1; rem_rows < length; rem_rows++)
                        {
                            memcpy(Matr[rem_rows - 1], Matr[rem_rows], sizeof(double) * height);
                        }
                        memcpy(Matr[length - 1], buf, sizeof(double) * height);
                    }
                    else
                    {
                        toggle = true;
                    }
                }
                else
                {
                    toggle = true;
                }
            }
        }
    }
}