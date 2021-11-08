#include "check_library.h"

/* Функция проверки на победу/ничью */
int check(int size, Cell pole[10][10], int size_for_win) {
    Victory_result victory = NOTHING;
    int i, j;
    int kr = 0, nol = 0, c = 0;

    for (i = 0; i < size; i++) { //Проверка по горизонтали
        for (j = 0; j < size - 1; j++) {
            if (kr < size_for_win - 1 && nol < size_for_win - 1) {
                if (pole[i][j] == CROSS && pole[i][j + 1] == CROSS) kr++;
                else kr = 0;
                if (pole[i][j] == ZERO && pole[i][j + 1] == ZERO) nol++;
                else nol = 0;
            }
        }
        victory = check_2(size_for_win, kr, nol);
        if (victory == CROSS_WIN || victory == ZERO_WIN) break;
        kr = 0;
        nol = 0;
    }

    for (j = 0; j < size; j++) { //Проверка по вертикали
        for (i = 0; i < size - 1; i++) {
            if (kr < size_for_win - 1 && nol < size_for_win - 1) {
                if (pole[i][j] == CROSS && pole[i + 1][j] == CROSS) kr++;
                else kr = 0;
                if (pole[i][j] == ZERO && pole[i + 1][j] == ZERO) nol++;
                else nol = 0;
            }
        }
        victory = check_2(size_for_win, kr, nol);
        if (victory == CROSS_WIN || victory == ZERO_WIN) break;
        kr = 0;
        nol = 0;
    }

    for (i = 0; i < size - 1; i++) { //Проверка по одной диагонали
        for (j = 0; j < size - 1; j++) {
            if (kr < size_for_win - 1 && nol < size_for_win - 1) {
                if (pole[i][j] == CROSS && pole[i + 1][j + 1] == CROSS) {
                    kr = 1;
                    for (int t = 1; t < size_for_win - 1; t++) {
                        if (pole[i + t][j + t] == CROSS && pole[i + t + 1][j + t + 1] == CROSS) kr++;

                    }
                    if (kr == size_for_win - 1) break;
                } else kr = 0;
                if (pole[i][j] == ZERO && pole[i + 1][j + 1] == ZERO) {
                    nol = 1;
                    for (int t = 1; t < size_for_win - 1; t++) {
                        if (pole[i + t][j + t] == ZERO && pole[i + t + 1][j + t + 1] == ZERO) nol++;
                    }
                    if (nol == size_for_win - 1) break;
                } else nol = 0;
            }
        }
        victory = check_2(size_for_win, kr, nol);
        if (victory == CROSS_WIN || victory == ZERO_WIN) break;
        kr = 0;
        nol = 0;
    }

    for (i = 0; i < size - 1; i++) { //Проверка по другой диагонали
        for (j = 1; j < size; j++) {
            if (kr < size_for_win - 1 && nol < size_for_win - 1) {
                if (pole[i][j] == CROSS && pole[i + 1][j - 1] == CROSS) {
                    kr = 1;
                    for (int t = 1; t < size_for_win - 1; t++) {
                        if (pole[i + t][j - t] == CROSS && pole[i + t + 1][j - t - 1] == CROSS)
                            kr++;

                    }
                    if (kr == size_for_win - 1) break;
                } else kr = 0;

                if (pole[i][j] == ZERO && pole[i + 1][j - 1] == ZERO) {
                    nol = 1;
                    for (int h = 1; h < size_for_win; h++) {
                        if (pole[i + h][j - h] == ZERO && pole[i + h + 1][j - h - 1] == ZERO) nol++;

                    }
                    if (nol == size_for_win - 1) break;
                } else nol = 0;
            }
        }
        victory = check_2(size_for_win, kr, nol);
        if (victory == CROSS_WIN || victory == ZERO_WIN) break;
        kr = 0;
        nol = 0;
    }


    for (j = 0; j < size; j++) { //Проверка на ничью
        for (i = 0; i < size; i++) {
            if (pole[i][j] != EMPTY && victory == NOTHING) c++;
        }
    }
    if (c == size * size) victory = DRAW;
    return victory;
}

/* Дополнительная функция проверки */
int check_2(int size_for_win, int kr, int nol) {
    int victory = 0;
    if (size_for_win == 3) {
        if (kr == 2) {
            victory = CROSS_WIN;
        }
        if (nol == 2) {
            victory = ZERO_WIN;
        }
    } else if (size_for_win == 4) {
        if (kr == 3) {
            victory = CROSS_WIN;
        }
        if (nol == 3) {
            victory = ZERO_WIN;
        }
    } else {
        if (kr == 4) {
            victory = CROSS_WIN;
        }
        if (nol == 4) {
            victory = ZERO_WIN;
        }
    }
    return victory;
}