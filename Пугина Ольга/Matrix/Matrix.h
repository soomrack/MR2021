#ifndef INC_1_Matrix_H
#define INC_1_Matrix_H


class Matrix {
private:
    unsigned int rows;
    unsigned int cols;
    double * data;

public:
    Matrix(unsigned int row, unsigned int col, double* dat){
        rows=row;
        cols=col;
        data=dat;
    }
    ~Matrix() // деструктор
    {
        // Динамически удаляем массив, который выделили ранее
        delete[] m_array ;
    }
    double trace(const Matrix A);// След матрицы

    Matrix sum(const Matrix A, const Matrix B);// Сумма матриц

    Matrix mult(const Matrix A, const Matrix B);// Умножение матриц

    Matrix mult_const(const double scalar, const Matrix A); // Умножение матрицы на скаляр

    Matrix transp(const Matrix A); // Транспонирование матрицы

    Matrix minor(int row, int col, const Matrix A);// Миноры

    Matrix dop(const Matrix A);//Матрица дополнений

    double det(const Matrix A); // Определитель матрицы

    Matrix one(const unsigned int size);  // Единичная матрица

    Matrix power(const Matrix A, const unsigned int power); // Возведение матрицы в степень

    Matrix exp(const Matrix A);

    void print(const Matrix A);// Вывести матрицу на экран
};


#endif //INC_1_MatrixrixART_H
