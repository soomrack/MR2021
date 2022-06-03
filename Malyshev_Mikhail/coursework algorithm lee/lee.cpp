#include <iostream>
#include <ctime>
#include "lee.h"

const int WALL   = -1;         // непроходимая клетка
const int BLANK  = -2;         // свободная непомеченная клетка



Grid::Grid() {
    H = 0;
    W = 0;
    grid = nullptr;
}

Grid::Grid(int W, int H) {
    this->H = H;
    this->W = W;

    for (int i = 0; i < W; i++) {
        for (int j = 0; j < H; j++) {
            grid[i][j] = BLANK;
        }
    }
}

void Grid::memory_alloc() {
    grid = new int* [H];
    for (int i = 0; i < H; i++) {
        grid[H] = new int[W];
    }
}

void Grid::free_memory() {
    for (int i = 0; i < H; i++) {
        free(grid[i]);
    }
    free(grid);
}

void Grid::Random() {   // случайная генерация поля
    for (int i = 0; i < W; i++) {
        for (int j = 0; j < H; j++) {
            if (rand() % 5 != 0) { // с вероятностью 1/5 каждая клетка может оказаться стеной
                grid[i][j] = BLANK;
            } else {
                grid[i][j] = WALL;
            }
        };
    };
}

bool Grid::lee(int ax, int ay, int bx, int by) {

        int px[W * H], py[W * H];      // координаты клеток, входящих  путь
        int len;                       // длина пути

        int dx[4] = {1, 0, -1, 0};   // смещения для определения соседей клетки  по x
        int dy[4] = {0, 1, 0, -1};   // и по у
        int wave, x, y, k;
        bool mark;

        if (grid[ay][ax] == WALL || grid[by][bx] == WALL) return false;  // ячейка (ax, ay) или (bx, by) - стена

        // распространение волны

        mark = false;  // не все возможные клетки помечены
        wave = 0;
        grid[ay][ax] = 0;            // стартовая ячейка помечена 0
        while ( !mark && grid[by][bx] == BLANK ) // пока не все возможные клетки помечены и финишная клетка не помечена
        {
            mark = true;               // предполагаем, что все свободные клетки уже помечены
            for ( y = 0; y < H; ++y )
                for ( x = 0; x < W; ++x )
                    if ( grid[y][x] == wave )                         // ячейка (x, y) помечена числом wave
                    {
                        for ( k = 0; k < 4; ++k )                    // проходим по всем непомеченным соседям
                        {
                            int iy=y + dy[k], ix = x + dx[k];
                            if ( iy >= 0 && iy < H && ix >= 0 && ix < W &&
                                 grid[iy][ix] == BLANK )
                            {
                                mark = false;              // найдены непомеченные клетки
                                grid[iy][ix] = wave + 1;      // распространяем волну
                            }
                        }
                    }
            wave++;
        }


        if (grid[by][bx] == BLANK) {
            return false;
        }

        // восстановление пути

        len = grid[by][bx];            // длина кратчайшего пути из (ax, ay) в (bx, by)
        x = bx;
        y = by;
        wave = len;
        while ( wave > 0 )            // пока не достигнем 0
        {
            px[wave] = x;
            py[wave] = y;                   // записываем ячейку (x, y) в путь
            wave--;
            for (k = 0; k < 4; ++k)
            {
                int iy=y + dy[k], ix = x + dx[k];
                if ( iy >= 0 && iy < H && ix >= 0 && ix < W &&
                     grid[iy][ix] == wave)
                {
                    x = x + dx[k];
                    y = y + dy[k];           // переходим в ячейку, которая на 1 ближе к старту
                    break;
                }
            }
        }
        px[0] = ax;
        py[0] = ay;                    // теперь px[0..len] и py[0..len] - координаты ячеек пути
        return true;
}

Grid::~Grid() {
    for (int i = 0; i < H; i++) {
        delete[] grid[i];
    }
    delete[] grid;
    grid = nullptr;
}

Grid::Grid(const Grid &other_grid) {
    H = other_grid.H;
    W = other_grid.W;
    grid = new int* [H];
    for (int i = 0; i < H; i++) {
        grid[H] = new int[W];
    }
    for (int i = 0; i < W; i++) {
        for (int j = 0; j < H; j++) {
            grid[i][j] = other_grid.grid[i][j];
        }
    }
}

Grid::Grid(Grid &&other_grid) noexcept {
    H = other_grid.H;
    W = other_grid.W;
    grid = other_grid.grid;
    other_grid.H = 0;
    other_grid.W = 0;
    grid = nullptr;
}

