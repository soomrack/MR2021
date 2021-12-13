#ifndef MATRIX_MATRIXLIB_H
#define MATRIX_MATRIXLIB_H



class Matrix {
private:
    int rows;
    int cols;
    double * data;
public:
    //Создание матрицы
    Matrix(int rows, int cols);
    //Создание разных типов матриц (единичная, нулевая)
    Matrix(int rows, int cols, int type);
    //Вывод матрицы
    void print();
    //Ввод элемента матрицы
    void set(int row, int col, double element);
    //Перезагрузка оператора присвоения
    Matrix & operator = (const Matrix &other);
    //Конструктор копирования
    Matrix(const Matrix &other);
    //Деструктор
    ~Matrix();
    //Конструктор перемещения
    Matrix(Matrix &&other) noexcept;
    //Перезагрузка оператора присваивания для перемещения
    Matrix & operator = (Matrix &&other) noexcept;
    //Перезагрузка оператора сложения
    Matrix operator + (const Matrix &other);
    //Перезагрузка оператора умножения
    Matrix operator * (const Matrix &other);
    //След матрицы (сумма элементов главной диагонали)
    int tr();
    //Определитель матрицы
    double det();
};


#endif //MATRIX_MATRIXLIB_H
