//
// Created by User on 22.11.2021.
//

#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

class Matrix {
private:
    int height;
    int width;
public:
    int *data;
public:
    Matrix(int height, int width) {
        this->height = height;
        this->width = width;
        data = (int *) malloc(height * width * sizeof(int));
    }

    void MatrixRandom(int height, int width) {
        for (int i = 0; i < height * width; i++)
            data[i] = rand()%10;
    }

    void MatrixOut(int width, int height) {
        for (int i = 0; i < height*width; i++) {
            std::cout << data[i] << " ";
            if ((i+1) % width == 0)
                std::cout << std::endl;
        }
    }

    int MatrixSizeHeight () {
        return height;
    }

    int MatrixSizeWidth () {
        return width;
    }
};


#endif //MATRIX_MATRIX_H
