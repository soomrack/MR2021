#ifndef MARTIXXXLIB_LIBRARY_H
#define MARTIXXXLIB_LIBRARY_H

using namespace std;

class Matrix {
private:
    int column = 1;
    int row = 1;
public:
    double *data;

    //конструктор мцы с пользовательскими значениями
    Matrix(int column, int row) {
        this->column = column;
        this->row = row;
        data = new double[row * column];
        cout << "введите значения элементов матрицы\n" << endl;
        for (int i = 0; i < row; i++)
            for (int j = 0; j < column; j++) {
                cin >> data[i * column + j];
            }
    }

    //конструктор единичной мцы
    Matrix(int column) {
        this->column = column;
        row = column;
        this->row = row;
        data = new double[row * column];
        for (int i = 0; i < row; i++)
            for (int j = 0; j < column; j++) {
                if (i == j) {
                    data[i * column + j] = 1;
                } else data[i * column + j] = 0;
            }
    }

    //конструктор для нулевой, ну или для матрицы, чтобы заполнить одним числом все ячейки
    Matrix(int column, int row, int n) {
        this->column = column;
        this->row = row;
        data = new double[row * column];
        for (int i = 0; i < row; i++)
            for (int j = 0; j < column; j++) {
                data[i * column + j] = n;
            }
    }

    //ф-я для вывода ф-ии
    void print();

    //ф-я для следа матрицы
    double trace();

    //перегрузка операторов
    Matrix operator+(const Matrix &other);

    Matrix operator*(const Matrix &other);

    Matrix operator*(double scalar);

    Matrix operator-(const Matrix &other);
};
#endif //MARTIXXXLIB_LIBRARY_H
