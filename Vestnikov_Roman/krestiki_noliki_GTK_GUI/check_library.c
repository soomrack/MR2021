#include "check_library.h"



/* Функция проверки на победу/ничью */
int check(int victory,int size,int pole[10][10],int size_for_win)
{
    victory = 0;
    int i, j;
    int  kr = 0, nol = 0, c = 0;

    for (i = 0; i < size; i++) { //Проверка по горизонтали
        for (j = 0; j < size - 1; j++) {
            if (kr < size_for_win - 1 && nol < size_for_win - 1) {
                if (pole[i][j] == 1 && pole[i][j + 1] == 1) kr++;
                else kr = 0;
                if (pole[i][j] == 2 && pole[i][j + 1] == 2) nol++;
                else nol = 0;
            }
        }
        victory = check_2(victory, size_for_win, kr, nol);
        if (victory == 1 || victory == 2) break;
        kr = 0;
        nol = 0;
    }

    for (j = 0; j < size; j++) { //Проверка по вертикали
        for (i = 0; i < size - 1; i++) {
            if (kr < size_for_win - 1 && nol < size_for_win - 1) {
                if (pole[i][j] == 1 && pole[i + 1][j] == 1) kr++;
                else kr = 0;
                if (pole[i][j] == 2 && pole[i + 1][j] == 2) nol++;
                else nol = 0;
            }
        }
        victory = check_2(victory, size_for_win, kr, nol);
        if (victory == 1 || victory == 2) break;
        kr = 0;
        nol = 0;
    }

    for (i = 0; i < size - 1; i++) { //Проверка по одной диагонали
        for (j = 0; j < size - 1; j++) {
            if (kr < size_for_win - 1 && nol < size_for_win - 1) {
                if (pole[i][j] == 1 && pole[i + 1][j + 1] == 1) {
                    kr = 1;
                    for (int t = 1; t < size_for_win - 1; t++) {
                        if (pole[i + t][j + t] == 1 && pole[i + t + 1][j + t + 1] == 1) kr++;

                    }
                    if (kr == size_for_win - 1) break;
                } else kr = 0;
                if (pole[i][j] == 2 && pole[i + 1][j + 1] == 2) {
                    nol = 1;
                    for (int t = 1; t < size_for_win - 1; t++) {
                        if (pole[i + t][j + t] == 2 && pole[i + t + 1][j + t + 1] == 2) nol++;
                    }
                    if (nol == size_for_win - 1) break;
                } else nol = 0;
            }
        }
        victory = check_2(victory, size_for_win, kr, nol);
        if (victory == 1 || victory == 2) break;
        kr = 0;
        nol = 0;
    }

    for (i = 0; i < size - 1; i++) { //Проверка по другой диагонали
        for (j = 1; j < size; j++) {
            if (kr < size_for_win - 1 && nol < size_for_win - 1) {
                if (pole[i][j] == 1 && pole[i + 1][j - 1] == 1) {
                    kr = 1;
                    for (int t = 1; t < size_for_win - 1; t++) {
                        if (pole[i + t][j - t] == 1 && pole[i + t + 1][j - t - 1] == 1)
                            kr++;

                    }
                    if (kr == size_for_win - 1) break;
                } else kr = 0;

                if (pole[i][j] == 2 && pole[i + 1][j - 1] == 2) {
                    nol = 1;
                    for (int h = 1; h < size_for_win; h++) {
                        if (pole[i + h][j - h] == 2 && pole[i + h + 1][j - h - 1] == 2) nol++;

                    }
                    if (nol == size_for_win - 1) break;
                } else nol = 0;
            }
        }
        victory = check_2(victory, size_for_win, kr, nol);
        if (victory == 1 || victory == 2) break;
        kr = 0;
        nol = 0;
    }


    for (j = 0; j < size; j++) { //Проверка на ничью
        for (i = 0; i < size; i++) {
            if (pole[i][j] != 0 && victory == 0) c++;
        }
    }
    if (c == size * size) victory = 3;
    return victory;
}

/* Дополнительная функция проверки */
int check_2(int victory,int size_for_win,int kr, int nol) {
    victory = 0;
    if (size_for_win == 3) {
        if (kr == 2) {
            victory = 1;
        }
        if (nol == 2) {
            victory = 2;
        }
    } else if (size_for_win == 4) {
        if (kr == 3) {
            victory = 1;
        }
        if (nol == 3) {
            victory = 2;
        }
    } else {
        if (kr == 4) {
            victory = 1;
        }
        if (nol == 4) {
            victory = 2;
        }
    }
    return victory;
}
