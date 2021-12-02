#ifndef C_MATRIX_C_MATRIX_H
#define C_MATRIX_C_MATRIX_H

#include <cstdlib>
#include <iostream>

class Matrix {
private:
    int height;
    int width;
public:
    int *data;
public:
    Matrix(int h, int w) {
        this->height = h;
        this->width = w;
        data = (int *) malloc(h * w * sizeof(int));
    }

    void M_Rand(int h, int w) const {
        for (int i = 0; i < h * w; i++)
            data[i] = rand()%10;
    }

    void M_Out(int w, int h) const {
        for (int i = 0; i < h * w; i++) {
            std::cout << data[i] << " ";
            if ((i+1) % w == 0)
                std::cout << std::endl;
        }
    }

    int M_Size_H () const {
        return height;
    }

    int M_Size_W () const {
        return width;
    }
};
#endif //C_MATRIX_C_MATRIX_H