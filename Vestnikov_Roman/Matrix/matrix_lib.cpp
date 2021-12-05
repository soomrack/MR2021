#include "matrix_lib.h"

/* Функция для обновления динамической памяти */
void Matrix::memory_update () {
    delete data ;
    data = new double *[m_height];
    for (int row = 0; row < m_height; row++) {
        data[row] = new double[m_width];
    }
}

/* Конструктор по умолчанию */
Matrix::Matrix(int height, int width) {
    m_height = height;
    m_width = width;
    //data = (double **) malloc(m_height * m_width * sizeof(double));
    data = new double *[m_height];
    for (int row = 0; row < m_height; row++) {
        data[row] = new double[m_width];
    }
    random();   //по умолчанию заполняем случайно
}

/* Конструктор для квадратных матриц */
Matrix::Matrix(int height) {
    m_height = height;
    m_width = height;
    data = new double *[m_height];
    for (int row = 0; row < m_height; row++) {
        data[row] = new double[m_width];
    }
    random();   //по умолчанию заполняем случайно
}

/***********************************СОЗДАНИЕ МАТРИЦ***********************************/

/* Создание матрицы вводом чисел с клавиатуры */
void Matrix::creator() {
    std::cout << "Enter numbers:" << std::endl;
    for (int row = 0; row < m_height; row++) {
        for (int col = 0; col < m_width; col++) {
            std::cin >> data[row][col];
        }
    }
}

/* Создание случайной матрицы */
void Matrix::random() {
    for (int row = 0; row < m_height; row++) {
        for (int col = 0; col < m_width; col++) {
            data[row][col]=rand()%100;
        }
    }
}

/* Создание единичной матрицы */
void Matrix::identity() {
    m_width=m_height;
    for (int row = 0; row < m_height; row++) {
        for (int col = 0; col < m_width; col++) {
            if (row==col) data[row][col]=1.0;
            else data[row][col]=0.0;
        }
    }
}

/* Создание нулевой матрицы */
void Matrix::zero() {
    for (int row = 0; row < m_height; row++) {
        for (int col = 0; col < m_width; col++) {
            data[row][col]=0.0;
        }
    }
}

/*********************************************************************************/

/* Вывод матрицы на экран */
void Matrix::print() {
    for (int row = 0; row < m_height; row++) {
        std::cout << std::endl;
        for (int col = 0; col < m_width; col++) {
            std::cout << data[row][col] << " ";
        }
    }
    std::cout << std::endl;
}

/* Конструктор перемещения */
Matrix::Matrix(Matrix &&matrix) noexcept {
    m_width=matrix.m_width;
    m_height=matrix.m_height;
    data=matrix.data;
    matrix.data= nullptr;
}

/* Перегрузка оператора присвоения */
Matrix &Matrix::operator=(const Matrix &matrix) {
    if (&matrix == this) return *this;
    this->m_height = matrix.m_height;
    this->m_width = matrix.m_width;
    memory_update ();
    for (int row = 0; row < this->m_height; row++) {
        for (int col = 0; col < this->m_width; col++) {
            this->data[row][col] = matrix.data[row][col];
        }
    }
    return *this;
}

/* Перегрузка оператора сложения */
Matrix Matrix::operator+(const Matrix &matrix) {
    if ((this->m_height != matrix.m_height) || (this->m_width != matrix.m_width)) {
        std::cerr << "ERROR! Matrix sizes are not suitable";
        exit(1);
    }
    this->m_height = matrix.m_height;
    this->m_width = matrix.m_width;
    Matrix res(this->m_height, this->m_width);
    for (int row = 0; row < m_height; row++) {
        for (int col = 0; col < m_width; col++) {
            res.data[row][col] = this->data[row][col] + matrix.data[row][col];
        }
    }
    return res;
}

/* Перегрузка оператора вычитания */
Matrix Matrix::operator-(const Matrix &matrix) {
    if ((this->m_height != matrix.m_height) || (this->m_width != matrix.m_width)) {
        std::cerr << "ERROR! Matrix sizes are not suitable";
        exit(1);
    }
    this->m_height = matrix.m_height;
    this->m_width = matrix.m_width;
    Matrix res(this->m_height, this->m_width);
    for (int row = 0; row < m_height; row++) {
        for (int col = 0; col < m_width; col++) {
            res.data[row][col] = this->data[row][col] - matrix.data[row][col];
        }
    }
    return res;
}

/* Перегрузка оператора умножения */
Matrix Matrix::operator*(const Matrix &matrix) {
    if (this->m_width != matrix.m_height) {
        std::cerr << "ERROR! Matrix sizes are not suitable";
        exit(1);
    }
    Matrix res(this->m_height, matrix.m_width);
    for (int row = 0; row < this->m_height; row++) {
        for (int col = 0; col < matrix.m_width; col++) {
            res.data[row][col] = 0.0;
            for (int k = 0; k < matrix.m_width; k++) {
                res.data[row][col] += this->data[row][k] * matrix.data[k][col];
            }
        }
    }
    return res;
}

/***********************************ОПРЕДЕЛИТЕЛЬ***********************************/

/* Функция удаления строки и столбца из матрицы */
void getnewMatrix(double **data, int size, int row, int col, double **newMatrix) {
    int offsetRow = 0; //Смещение индекса строки в матрице
    int offsetCol = 0; //Смещение индекса столбца в матрице
    for (int i = 0; i < size - 1; i++) {
        //Пропустить row-ую строку
        if (i == row) {
            offsetRow = 1; //Как только встретили строку, которую надо пропустить, делаем смещение для исходной матрицы
        }

        offsetCol = 0; //Обнулить смещение столбца
        for (int j = 0; j < size - 1; j++) {
            //Пропустить col-ый столбец
            if (j == col) {
                offsetCol = 1; //Встретили нужный столбец, пропускаем его смещением
            }
            newMatrix[i][j] = data[i + offsetRow][j + offsetCol];
        }
    }
}

/* Функция нахождения определителя */
double MatrixDet(double **data, int size) {
    double det = 0.0;
    if (size == 1) {
        return data[0][0];
    }
        //Условие выхода из рекурсии
    else if (size == 2) {
        return data[0][0] * data[1][1] - data[0][1] * data[1][0];
    }

    int degree = 1; // (-1)^(1+j) из формулы определителя
    //Матрица без строки и столбца
    auto **newMatrix = new double *[size - 1];
    for (int i = 0; i < size - 1; i++) {
        newMatrix[i] = new double[size - 1];
    }

    //Раскладываем по 0-ой строке, цикл бежит по столбцам
    for (int j = 0; j < size; j++) {
        //Удалить из матрицы i-ю строку и j-ый столбец
        //Результат в newMatrix
        getnewMatrix(data, size, 0, j, newMatrix);

        //Рекурсивный вызов
        det = det + (degree * data[0][j] * MatrixDet(newMatrix, size - 1));
        degree = -degree;
    }

    //Чистим память на каждом шаге рекурсии(важно!)
    for (int i = 0; i < size - 1; i++) {
        delete[] newMatrix[i];
    }
    delete[] newMatrix;
    return det;
}

/* Вывод определителя */
void Matrix::determinant() {
    if (m_height != m_width) {
        std::cerr << "ERROR! The matrix is not square";
        exit(1);
    }
    double det = MatrixDet(data, m_height);
    std::cout << "det = " << det << std::endl;
}

/**********************************************************************************/

/* След матрицы */
void Matrix::trace() {
    if (m_height != m_width) {
        std::cerr << "ERROR! The matrix is not square";
        exit(1);
    }
    double tr = 0.0;
    for (int row = 0, col = 0; row < m_height; row++, col++) {
        tr += data[row][col];
    }
    std::cout << "trace = " << tr << std::endl;
}

