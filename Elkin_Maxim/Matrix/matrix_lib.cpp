#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class matrix {
public:
    matrix(int rows, int columns);
    matrix(const matrix &);
    ~matrix();

    matrix operator + (const matrix &);
    matrix operator - (const matrix &);
    matrix operator * (const matrix &);
    void operator = (const matrix &);

    double get_det();
    int get_rows();
    int get_columns();
    void get_matrix();
    matrix get_transpose();
    void set_cells_cmd();
    void set_cell(int,int,double);
    void sort_rows(int);

private:
    int rows;
    int columns;
    vector<vector<double> > data;
};

matrix::matrix(int rows, int columns) {
    this -> rows = rows;
    this -> columns = columns;
    this -> data.resize(rows,vector<double>(columns));
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < columns; col++) {
            data[row][col] = 0;
        }
    }
}

matrix::matrix(const matrix &other) {
    this -> rows = other.rows;
    this -> columns = other.columns;
    this -> data = vector<vector<double> > (rows,vector<double> (columns));

    for (int row = 0; row < other.rows; row++) {
        for (int col = 0; col < other.columns; col++) {
            this -> data[row][col] = other.data[row][col];
        }
    }
}

matrix::~matrix() = default;

void matrix::operator = (const matrix &other) {
    this -> rows = other.rows;
    this -> columns = other.columns;
    this -> data = vector<vector<double> > (rows, vector<double> (columns));

    for (int row = 0; row < other.rows; row++) {
        for (int col = 0; col < other.columns; col++) {
            this -> data[row][col] = other.data[row][col];
        }
    }
}

matrix matrix::operator + (const matrix &other) {
    matrix var (0,0);
    if ((this -> rows == other.rows) && (this -> columns == other.columns)) {
        var.rows = other.rows;
        var.columns = other.columns;
        var.data.resize(var.rows,vector<double>(var.columns));
        for (int row = 0; row < other.rows; row++) {
            for (int col = 0; col < other.columns; col++) {
                var.data[row][col] = this -> data[row][col] + other.data[row][col];
            }
        }
    }
    else {
        cout << "Incorrect sizes of matrices" << endl;
    }
    return var;
}

matrix matrix::operator - (const matrix &other) {
    matrix var (0,0);
    if ((this -> rows == other.rows) && (this -> columns == other.columns)) {
        var.rows = other.rows;
        var.columns = other.columns;
        var.data.resize(var.rows,vector<double>(var.columns));
        for (int row = 0; row < other.rows; row++) {
            for (int col = 0; col < other.columns; col++) {
                var.data[row][col] = this -> data[row][col] - other.data[row][col];
            }
        }
    }
    else {
        cout << "Incorrect sizes of matrices" << endl;
    }
    return var;
}

matrix matrix::operator * (const matrix &other) {
    matrix var(0,0);
    if(this -> columns == other.rows) {
        var.rows = this -> rows;
        var.columns = other.columns;
        var.data.resize(var.rows,vector<double>(var.columns));

        for (int row = 0; row < this -> rows; row++){
            for (int col = 0; col < other.columns; col++){
                int cell = 0;
                for (int k = 0; k < this -> columns; k++) {
                    cell = cell + ((this -> data[row][k]) * other.data[k][col]);
                }
                var.data[row][col] = cell;
            }
        }
    }
    else {
        cout << "Incorrect sizes of matrices" << endl;
    }
    return var;
}

int matrix::get_rows() {
    return rows;
}

int matrix::get_columns() {
    return columns;
}

//returns determinant of matrix
double matrix::get_det() {
    matrix var (rows, columns);
    var.data.resize(var.rows,vector<double>(var.columns));
    for (int row = 0; row < var.rows; row++) {
        for (int col = 0; col < var.columns; col++) {
            var.data[row][col] = data[row][col];
        }
    }
    double det = 0;
    if (var.rows == var.columns) {
        for (int col = 0; col < var.columns - 1; col++) {
            var.sort_rows(col);
            for (int row = col+1; row < var.rows; row++) {
                if (var.data[col][col] && var.data[row][col]) {
                    double k = var.data[row][col]/var.data[col][col];
                    for (int l = col; l < var.columns; l++) {
                        var.data[row][l] = var.data[row][l] - (k * var.data[col][l]);
                    }
                }
            }
        }
        det = 1;
        for (int row = 0; row < rows; row++) {
            det = det * var.data[row][row];
        }
    }
    else {
        cout << "Matrix is not square" << endl;
    }
    return abs(det);
}

//prints matrix to command line
void matrix::get_matrix() {
    cout << "Matrix " << ":" << endl;
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < columns; col++) {
            cout << "   " << data[row][col] << "    ";
        }
        cout << "\n";
    }
}

//returns transpose matrix
matrix matrix::get_transpose() {
    matrix trans(columns, rows);
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < columns; col++) {
            trans.data[row][col] = data[col][row];
        }
    }
    trans.get_matrix();
    return trans;
}

//matrix values assigns from command line
void matrix::set_cells_cmd() {
    for (int row = 0; row < rows; row++) {
        cout << "Enter values of the " << row + 1 << " row:" << endl;
        for (int col = 0; col < columns; col++) {
            cin >> data[row][col];
        }
    }
}

//set value of defined cell
void matrix::set_cell(int row, int column, double value) {
    if (row >= rows || column >= columns) {
        cout << "Incorrect cell address!" << endl;
    }
    else {
        data[row][column] = value;
    }
}

//transfer rows with zero-values in defined column to the end of vector
void matrix::sort_rows(int col) {
    bool next_step;
    int null_counter = 0;
    for (int row = 0; row < rows; row++) {
        if (null_counter < rows - row) {
            next_step = false;
            while(next_step == false) {
                if (data[row][col] == 0) {
                    null_counter = 0;
                    for (int i = row; i < rows; i++) {
                        if (data[i][col] == 0) {
                            null_counter++;
                        }
                    }
                    if (null_counter < rows - row) {
                        rotate(data.begin() + row,data.begin() + (row+1),data.end());
                    }
                    else {
                        next_step = true;
                    }
                }
                else {
                    next_step = true;
                }
            }
        }
    }
}
