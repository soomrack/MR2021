#include <iostream>
#include "Matrix_liba.h"
using namespace std;

double** Matrix::allocation_memory(unsigned int length, unsigned int height)
{
    if (length == 0 || height == 0)
    {
        return nullptr;
    }
    try
    {
        data_line = new double [length * height];
    }
    catch (bad_alloc const&)
    {
        data_line = nullptr;
        return nullptr;
    }
    try
    {
        data = new double* [length];
    }
    catch (bad_alloc const&)
    {
        data_line =  nullptr;
        data =  nullptr;
        delete[] data_line;
        return data;
    }
    for (unsigned int row = 0; row < length; row++)
    {
        data[row] = &data_line[row * height];
    }
    return data;
}
void Matrix::clear_memory()
{
    delete[] data_line;
    delete[] data;
}

Matrix::Matrix(unsigned int length, unsigned int height)
{
    this->length = length;
    this->height = height;
    this->data = allocation_memory(length, height);
    if (data_line != nullptr)
    {
        for (unsigned int pos = 0; pos < length*height; pos++)
        {
            data_line[pos] = 0;
        }
    }
    else
    {
        this->length = 0;
        this->height = 0;
    }

}
// Transfer constructor
Matrix::Matrix(const Matrix & other)
{
    data = allocation_memory(other.length,other.height);
    if (data_line != nullptr)
    {
        length = other.length;
        height = other.height;
        memcpy(data_line,other.data_line,length * height * sizeof(double));
    }
}
// Copy constructor
Matrix::Matrix(Matrix && other) noexcept
{
    length = other.length;
    height = other.height;
    data = other.data;
    data_line = other.data_line;
    other.data = nullptr;
    other.data_line = nullptr;
    other.length = 0;
    other.height = 0;
}
Matrix :: ~Matrix()
{
    clear_memory();
}


Matrix & Matrix :: operator = (const Matrix &other)
{
    if (this == &other)
    {
        return *this;
    }
    clear_memory();
    this->data= allocation_memory(length, height);
    if (data_line != nullptr)
    {
        this->length = other.length;
        this->height = other.height;
        memcpy(this->data_line,other.data_line,length * height * sizeof(double));
    }
    return *this;
}
Matrix & Matrix :: operator = (Matrix &&other) noexcept
{
    if (this == &other)
    {
        return *this;
    }
    clear_memory();
    length = other.length;
    height = other.height;
    data = other.data;
    data_line = other.data_line;
    other.data = nullptr;
    other.data_line = nullptr;
    other.length = 0;
    other.height = 0;
    return *this;
}
Matrix Matrix :: operator+(const Matrix &other)
{
    if ((this->length != other.length) || (this->height != other.height))
    {
        Matrix answer (0, 0);
        return answer;
    }

    Matrix answer (length, height);

    for (unsigned int pos = 0; pos < length*height; pos++)
    {
        answer.data_line[pos] = data_line[pos] + other.data_line[pos];
    }
    return answer;
}
Matrix Matrix :: operator-(const Matrix &other)
{
    if ((this -> length != other.length) || (this -> height != other.height))
    {
        Matrix answer (0, 0);
        return answer;
    }

    Matrix answer (length, height);

    for (unsigned int pos = 0; pos < length*height; pos++)
    {
        answer.data_line[pos] = data_line[pos] - other.data_line[pos];
    }
    return answer;
}
Matrix Matrix :: operator*(const Matrix &other)
{
    if(this->height != other.length)
    {
        Matrix answer (0, 0);
        return answer;
    }

    Matrix answer (length, other.height);

    for (unsigned int row = 0; row < this->length; row++)
    {
        for (unsigned int col = 0; col < other.height; col++)
        {
            double cell = 0;
            for (unsigned int k = 0; k < this->height; k++)
            {
                cell += ((this->data[row][k]) * other.data[k][col]);
            }
            answer.data[row][col] = cell;
        }
    }
    return answer;
}

void Matrix :: set_matrix(double *arr)
{
    memcpy(data_line,arr,length * height * sizeof(double));
}

void Matrix :: set_matrix_one()
{
    for (unsigned int pos = 0; pos < length * height; pos++)
    {
        data_line[pos] = 0.0;
    }
    for (unsigned int pos = 0; pos < min(length, height); pos++)
    {
        data[pos][pos] = 1.0;
    }
}
void Matrix :: display()
{
    for (unsigned int row = 0; row < length; row++)
    {
        for (unsigned int col = 0; col < height; col++)
        {
            cout.width(4);
            cout << data[row][col];
        }
        cout << endl;
    }
    cout << endl;
}
int Matrix :: trace()
{
    double trace_res = 0.0;
    for (unsigned int pos = 0; pos < min(length, height); pos++)
    {
        trace_res += data[pos][pos];
    }
    return trace_res;
}
double Matrix :: determinant()
{
    double det = 0.0;
    double eps = 0.000001;

    if (length != height)
    {
        return det;
    }
    if (length == 1)
    {
        det = data[0][0];
        return det;
    }
    if (length == 2)
    {
        det = data[0][0]*data[1][1]-data[0][1]*data[1][0];
        return det;
    }

    Matrix sup_matrix (length, height);
    memcpy(sup_matrix.data[0],data[0],length * height * sizeof(double));

    for (unsigned int col = 0; col < sup_matrix.height - 1; col++)
    {
        sup_matrix.sort_rows(col);
        for (unsigned int row = col+1; row < sup_matrix.length; row++)
        {
            if (sup_matrix.data[col][col] && sup_matrix.data[row][col])
            {
                double k = 0.0;
                if (abs(sup_matrix.data[col][col]) < eps)
                {
                    return 0.0;
                }
                k = sup_matrix.data[row][col]/sup_matrix.data[col][col];
                for (unsigned int g = col; g < sup_matrix.height; g++)
                {
                    sup_matrix.data[row][g] -= k * sup_matrix.data[col][g];
                }
            }
        }
    }
    det = 1;
    for (unsigned int row = 0; row < height; row++)
    {
        det = det * sup_matrix.data[row][row];
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
                if (data[row][col] == 0)
                {
                    null_counter = 0;
                    for (unsigned int i = row; i < length; i++)
                    {
                        if (data[i][col] == 0)
                        {
                            null_counter++;
                        }
                    }
                    if (null_counter < length - row)
                    {
                        double buf[height];
                        memcpy(buf, data[row], sizeof(double) * height);
                        for (unsigned int rem_rows = row + 1; rem_rows < length; rem_rows++)
                        {
                            memcpy(data[rem_rows - 1], data[rem_rows], sizeof(double) * height);
                        }
                        memcpy(data[length - 1], buf, sizeof(double) * height);
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