#ifndef MATRIX_LIBRARY_H
#define MATRIX_LIBRARY_H

class Matrix{
private:
    int height;
    int width;
    double * data;
public:
    Matrix();
    Matrix(int height, int width, double * data);
    Matrix(int height, int width);
    Matrix(const Matrix &m);
    Matrix(Matrix &&m);
    Matrix & operator= (const Matrix &m) {
        if (&m == this) { return *this; }
        height = m.height;
        width = m.width;
        free(data);
        data = (double *) malloc(height * width * sizeof(double));
        memcpy(data, m.data, height * width * (sizeof(double)));
        return *this;
    }

    Matrix & operator+ (const Matrix &m){
        if ((m.width != this->width) or (m.height != this->height)){
            std::cout<<"Summation error\n";
            return * new Matrix(0,0);
        }

        double arr[m.height * m.width];

        for (int i = 0; i < m.height * m.width; ++i) {
            arr[i] = this->data[i]+m.data[i];
        }

        return * new Matrix(m.height,m.width, arr);
    }

    Matrix & operator* (const Matrix &m){
        if (m.height != this->width){
            std::cout<<"Multiplication error\n";
            return * new Matrix(0,0);
        }

        double arr[this->height * m.width];

        for (int i = 0; i < this->height; ++i) {
            for (int j = 0; j < m.width; ++j) {
                double Temp = 0;
                for (int k = 0; k < m.height; ++k) {
                    Temp+= this->data[i*this->width+k]*m.data[m.width*k+j];
                }
                arr[i*width+j] = Temp;
            }
        }

        return * new Matrix(m.height,m.width, arr);
    }

    void Print();
    double Trace();
};

#endif //MATRIX_LIBRARY_H
