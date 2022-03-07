#include "movement.h"
#include <stdlib.h>

#include <stdio.h>


void visual(int size, int pole[size][size]);

int end(int size, int pole[size][size], int size_for_win);


int Human_move(int step, int size, int pole[size][size], int size_for_win, int human_weapon, int bot_weapon) { //Крестик
    int victory, row, col;
    printf("Выберите клетку: ");
    syntax(&row, &col, size, pole);
    pole[row - 1][col - 1] = human_weapon;
    visual(size, pole);
    victory = check(size, pole, size_for_win);
    return victory;
}

int Bot_move(int step, int size, int pole[size][size], int size_for_win, int human_weapon, int bot_weapon) {


    int i, j, victory;
    int random_variable;
    int kr1 = 1, nol1 = 1, turn_is_completed = 0;
    random_variable = rand() % 2;

    //первая атака
    if (step == 1) {
        int random_variable1 = rand() % size;
        int random_variable2 = rand() % size;
        pole[random_variable1][random_variable2] = bot_weapon;
        victory = end(size, pole, size_for_win);
        return victory;
    }


    //Переход к атаке и обязательной победе

    kr1 = 1;
    nol1 = 1;

    for (i = 0; i < size; i++) {        //Проверка по горизонтали
        for (j = 0; j < size - 1; j++) {
            if (pole[i][j] == bot_weapon &&
                ((pole[i][j + size_for_win - 1] == human_weapon) || pole[i][j - 1] == human_weapon || j == 0 ||
                 j == size - size_for_win + 1)) {
                for (int t = 1; t < size_for_win - 1; t++)
                    if (pole[i][j] == bot_weapon && pole[i][j + t] == bot_weapon)nol1++;
                if (nol1 >= size_for_win - 1) {
                    if (pole[i][j + size_for_win - 1] == 0 && j != size_for_win - 2) {
                        pole[i][j + size_for_win - 1] = bot_weapon;
                        turn_is_completed = 1;
                    } else if (pole[i][j - 1] == 0) {
                        pole[i][j - 1] = bot_weapon;
                        turn_is_completed = 1;
                    }
                    if (turn_is_completed == 1) {
                        victory = end(size, pole, size_for_win);
                        return victory;
                    }
                }
            }
        }
        nol1 = 1;
    }
    for (j = 0; j < size; j++) {        //Проверка по вертикали
        for (i = 0; i < size - 1; i++) {
            if (pole[i][j] == bot_weapon &&
                ((pole[i + size_for_win - 1][j] == human_weapon) || pole[i - 1][j] == human_weapon || i == 0 ||
                 i == size - size_for_win + 1)) {
                for (int t = 1; t < size_for_win - 1; t++)
                    if (pole[i][j] == bot_weapon && pole[i + t][j] == bot_weapon)nol1++;
                if (nol1 >= size_for_win - 1) {
                    if (pole[i + size_for_win - 1][j] == 0 && i != size_for_win - 2) {
                        pole[i + size_for_win - 1][j] = bot_weapon;
                        turn_is_completed = 1;
                    } else if (pole[i - 1][j] == 0) {
                        pole[i - 1][j] = bot_weapon;
                        turn_is_completed = 1;
                    }
                    if (turn_is_completed == 1) {
                        victory = end(size, pole, size_for_win);
                        return victory;
                    }
                }
            }
        }
        nol1 = 1;
    }

    for (i = 0; i < size - 1; i++) {        //Проверка по одной диагонали
        for (j = 0; j < size - 1; j++) {
            if (pole[i][j] == bot_weapon && (pole[i - 1][j - 1] == human_weapon ||
                                             pole[i + size_for_win - 1][j + size_for_win - 1] == human_weapon ||
                                             (j == 0 && i == 0) ||
                                             (j == size - size_for_win + 1 && i == size - size_for_win + 1))) {
                for (int t = 1; t < size_for_win - 1; t++)
                    if (pole[i][j] == bot_weapon && pole[i + t][j + t] == bot_weapon)nol1++;
                if (nol1 >= size_for_win - 1) {
                    if (pole[i + size_for_win - 1][j + size_for_win - 1] == 0 && j != size_for_win - 2 &&
                        i != size_for_win - 2) {
                        pole[i + size_for_win - 1][j + size_for_win - 1] = bot_weapon;
                        turn_is_completed = 1;
                    } else if (pole[i - 1][j - 1] == 0) {
                        pole[i - 1][j - 1] = bot_weapon;
                        turn_is_completed = 1;
                    }
                    if (turn_is_completed == 1) {
                        victory = end(size, pole, size_for_win);
                        return victory;
                    }
                }

            }
        }
        nol1 = 1;
    }

    for (i = 0; i < size - 1; i++) {        //Проверка по другой диагонали
        for (j = 0; j < size - 1; j++) {
            if (pole[i][j] == bot_weapon &&
                (pole[i - 1][j + 1] == human_weapon ||
                 pole[i + size_for_win - 1][j - (size_for_win - 1)] == human_weapon ||
                 (j == size - size_for_win + 1 && i == 0) || (j == 0 && i == size - size_for_win + 1))) {
                for (int t = 1; t < size_for_win - 1; t++)
                    if (pole[i][j] == 1 && pole[i + t][j - t] == bot_weapon)
                        nol1++;
                if (nol1 >= size_for_win - 1) {
                    if (pole[i + size_for_win - 1][j - (size_for_win - 1)] == 0 && i != size_for_win - 2 &&
                        j != -(size_for_win - 2)) {
                        pole[i + size_for_win - 1][j - (size_for_win - 1)] = bot_weapon;
                        turn_is_completed = 1;
                    } else if (pole[i - 1][j + 1] == 0) {
                        pole[i - 1][j + 1] = bot_weapon;
                        turn_is_completed = 1;
                    }
                    if (turn_is_completed == 1) {
                        victory = end(size, pole, size_for_win);
                        return victory;
                    }
                }
            }
        }
        nol1 = 1;
    }

    if (size_for_win == 3) {
        for (i = 0; i < size; i++) {
            if (pole[i][1] == 0 && pole[i][0] == bot_weapon && pole[i][2] == bot_weapon) {
                pole[i][1] = bot_weapon;
                victory = end(size, pole, size_for_win);
                return victory;
            }
        }
        for (j = 0; i < size; i++) {
            if (pole[1][j] == 0 && pole[0][j] == bot_weapon && pole[2][j] == bot_weapon) {
                pole[1][j] = bot_weapon;
                victory = end(size, pole, size_for_win);
                return victory;
            }
        }
        if (pole[1][1] == 0 && pole[0][0] == bot_weapon && pole[2][2] == bot_weapon) {
            pole[1][1] = bot_weapon;
            victory = end(size, pole, size_for_win);
            return victory;
        }
        if (pole[1][1] == 0 && pole[2][0] == bot_weapon && pole[0][2] == bot_weapon) {
            pole[1][1] = bot_weapon;
            victory = end(size, pole, size_for_win);
            return victory;
        }
    }


    //Переход к обороне

    kr1 = 1;
    nol1 = 1;
    random_variable = rand() % 2;
    for (i = 0; i < size; i++) {        //Проверка по горизонтали
        for (j = 0; j < size - 1; j++) {
            if (pole[i][j] == human_weapon &&
                ((pole[i][j + size_for_win - 1] == bot_weapon) || pole[i][j - 1] == bot_weapon || j == 0 ||
                 j == size - size_for_win + 1)) {
                for (int t = 1; t < size_for_win; t++)
                    if (pole[i][j] == human_weapon && pole[i][j + t] == human_weapon)kr1++;
                if (kr1 == size_for_win - 1) {
                    if (pole[i][j + size_for_win - 1] == 0 && j != size_for_win - 2) {
                        pole[i][j + size_for_win - 1] = bot_weapon;
                        turn_is_completed = 1;
                    } else if (pole[i][j - 1] == 0) {
                        pole[i][j - 1] = bot_weapon;
                        turn_is_completed = 1;
                    }
                    if (turn_is_completed == 1) {
                        victory = end(size, pole, size_for_win);
                        return victory;
                    }
                }
            }
        }
        kr1 = 1;
    }
    for (j = 0; j < size; j++) {        //Проверка по вертикали
        for (i = 0; i < size - 1; i++) {
            if (pole[i][j] == human_weapon &&
                ((pole[i + size_for_win - 1][j] == bot_weapon) || pole[i - 1][j] == bot_weapon || i == 0 ||
                 i == size - size_for_win + 1)) {
                for (int t = 1; t < size_for_win; t++)
                    if (pole[i][j] == human_weapon && pole[i + t][j] == human_weapon)kr1++;
                if (kr1 == size_for_win - 1) {
                    if (pole[i + size_for_win - 1][j] == 0 && i != size_for_win - 2) {
                        pole[i + size_for_win - 1][j] = bot_weapon;
                        turn_is_completed = 1;
                    } else if (pole[i - 1][j] == 0) {
                        pole[i - 1][j] = bot_weapon;
                        turn_is_completed = 1;
                    }
                    if (turn_is_completed == 1) {
                        victory = end(size, pole, size_for_win);
                        return victory;
                    }
                }
            }
        }
        kr1 = 1;
    }

    for (i = 0; i < size - 1; i++) {        //Проверка по одной диагонали
        for (j = 0; j < size - 1; j++) {
            if (pole[i][j] == human_weapon &&
                (pole[i - 1][j - 1] == bot_weapon || pole[i + size_for_win - 1][j + size_for_win - 1] == bot_weapon ||
                 (i == 0 && j == 0) ||
                 (i == size - size_for_win + 1 && j == size - size_for_win + 1))) {
                for (int t = 1; t < size_for_win; t++)
                    if (pole[i][j] == human_weapon && pole[i + t][j + t] == human_weapon)kr1++;
                if (kr1 == size_for_win - 1) {
                    if (pole[i + size_for_win - 1][j + size_for_win - 1] == 0 && j != size_for_win - 2 &&
                        i != size_for_win - 2) {
                        pole[i + size_for_win - 1][j + size_for_win - 1] = bot_weapon;
                        turn_is_completed = 1;
                    } else if (pole[i - 1][j - 1] == 0) {
                        pole[i - 1][j - 1] = bot_weapon;
                        turn_is_completed = 1;
                    }
                    if (turn_is_completed == 1) {
                        victory = end(size, pole, size_for_win);
                        return victory;
                    }
                }
            }
        }
        kr1 = 1;
    }

    for (i = 1; i < size - 1; i++) {        //Проверка по другой диагонали
        for (j = 1; j < size - 1; j++) {
            if (pole[i][j] == human_weapon &&
                (pole[i - 1][j + 1] == 0 || pole[i + size_for_win - 1][j - (size_for_win - 1)] == 0)) {
                for (int t = 1; t < size_for_win; t++)
                    if (pole[i][j] == human_weapon && pole[i + t][j - t] == human_weapon)kr1++;
                if (kr1 == size_for_win - 1) {
                    if (pole[i + size_for_win - 1][j - (size_for_win - 1)] == 0 && i != size_for_win - 2 &&
                        j != -(size_for_win - 2)) {
                        pole[i + size_for_win - 1][j - (size_for_win - 1)] = bot_weapon;
                        turn_is_completed = 1;
                    } else if (pole[i - 1][j + 1] == 0) {
                        pole[i - 1][j + 1] = bot_weapon;
                        turn_is_completed = 1;
                    }
                    if (turn_is_completed == 1) {
                        victory = end(size, pole, size_for_win);
                        return victory;
                    }

                }
            }
        }
        kr1 = 1;
    }
    //Переход к атаке и предварительной победе

    for (i = 0; i < size; i++) {        //Проверка по горизонтали
        for (j = 1; j < size - 1; j++) {
            if (pole[i][j - 1] == 0 && pole[i][j] == bot_weapon && pole[i][j + size_for_win - 2] == 0) {
                for (int t = 1; t < size_for_win - 1; t++)
                    if (pole[i][j] == bot_weapon && pole[i][j + t] == bot_weapon)nol1++;
                if (nol1 >= size_for_win - 2) {
                    if (random_variable == 0) pole[i][j + size_for_win - 2] = bot_weapon;
                    else pole[i][j - 1] = bot_weapon;
                    victory = end(size, pole, size_for_win);
                    return victory;
                }
            }
        }
        nol1 = 1;
    }

    for (j = 0; j < size; j++) {        //Проверка по вертикали
        for (i = 1; i < size - 1; i++) {
            if (pole[i - 1][j] == 0 && pole[i][j] == bot_weapon && pole[i + size_for_win - 2][j] == 0) {
                for (int t = 1; t < size_for_win - 1; t++)
                    if (pole[i][j] == bot_weapon && pole[i + t][j] == bot_weapon)nol1++;
                if (nol1 >= size_for_win - 2) {
                    if (random_variable == 0) pole[i + size_for_win - 2][j] = bot_weapon;
                    else pole[i - 1][j] = bot_weapon;
                    victory = end(size, pole, size_for_win);
                    return victory;
                }
            }
        }
        nol1 = 1;
    }

    for (i = 1; i < size - 1; i++) {        //Проверка по одной диагонали
        for (j = 1; j < size - 1; j++) {
            if (pole[i - 1][j - 1] == 0 && pole[i][j] == bot_weapon &&
                pole[i + size_for_win - 2][j + size_for_win - 2] == 0) {
                for (int t = 1; t < size_for_win - 1; t++)
                    if (pole[i][j] == bot_weapon && pole[i + t][j + t] == bot_weapon)nol1++;
                if (nol1 >= size_for_win - 2) {
                    if (random_variable == 0) pole[i + size_for_win - 2][j + size_for_win - 2] = bot_weapon;
                    else pole[i - 1][j - 1] = bot_weapon;
                    victory = end(size, pole, size_for_win);
                    return victory;
                }
            }
        }
        nol1 = 1;
    }

    for (i = 1; i < size - 1; i++) {        //Проверка по другой диагонали
        for (j = 1; j < size - 1; j++) {
            if (pole[i - 1][j + 1] == 0 && pole[i][j] == bot_weapon &&
                pole[i + size_for_win - 2][j - (size_for_win - 2)] == 0) {
                for (int t = 1; t < size_for_win - 1; t++)
                    if (pole[i][j] == bot_weapon && pole[i + t][j - t] == bot_weapon)nol1++;
                if (nol1 >= size_for_win - 2) {
                    if (random_variable == 0) pole[i + size_for_win - 2][j - (size_for_win - 2)] = bot_weapon;
                    else pole[i - 1][j + 1] = bot_weapon;
                    victory = end(size, pole, size_for_win);
                    return victory;
                }
            }
        }
        nol1 = 1;
    }

    //Переход к основной обороне

    for (i = 0; i < size; i++) {        //Проверка по горизонтали
        for (j = 1; j < size - 1; j++) {
            if (pole[i][j - 1] == 0 && pole[i][j] == human_weapon && pole[i][j + size_for_win - 2] == 0) {
                for (int t = 1; t < size_for_win - 1; t++)
                    if (pole[i][j] == human_weapon && pole[i][j + t] == human_weapon)kr1++;
                if (kr1 == size_for_win - 2) {
                    if (random_variable == 0) pole[i][j + size_for_win - 2] = bot_weapon;
                    else pole[i][j - 1] = bot_weapon;
                    victory = end(size, pole, size_for_win);
                    return victory;
                }
            }
        }
        kr1 = 1;
    }

    for (j = 0; j < size; j++) {        //Проверка по вертикали
        for (i = 1; i < size - 1; i++) {
            if (pole[i - 1][j] == 0 && pole[i][j] == human_weapon && pole[i + size_for_win - 2][j] == 0) {
                for (int t = 1; t < size_for_win - 1; t++)
                    if (pole[i][j] == human_weapon && pole[i + t][j] == human_weapon)kr1++;
                if (kr1 == size_for_win - 2) {
                    if (random_variable == 0) pole[i + size_for_win - 2][j] = bot_weapon;
                    else pole[i - 1][j] = bot_weapon;
                    victory = end(size, pole, size_for_win);
                    return victory;
                }
            }
        }
        kr1 = 1;
    }

    for (i = 1; i < size - 1; i++) {        //Проверка по одной диагонали
        for (j = 1; j < size - 1; j++) {
            if (pole[i - 1][j - 1] == 0 && pole[i][j] == human_weapon &&
                pole[i + size_for_win - 2][j + size_for_win - 2] == 0) {
                for (int t = 1; t < size_for_win - 1; t++)
                    if (pole[i][j] == human_weapon && pole[i + t][j + t] == human_weapon)kr1++;
                if (kr1 == size_for_win - 2) {
                    if (random_variable == 0) pole[i + size_for_win - 2][j + size_for_win - 2] = bot_weapon;
                    else pole[i - 1][j - 1] = bot_weapon;
                    victory = end(size, pole, size_for_win);
                    return victory;
                }
            }
        }
        kr1 = 1;
    }

    for (i = 1; i < size - 1; i++) {        //Проверка по другой диагонали
        for (j = 1; j < size - 1; j++) {
            if (pole[i - 1][j + 1] == 0 && pole[i][j] == human_weapon &&
                pole[i + size_for_win - 2][j - (size_for_win - 2)] == 0) {
                for (int t = 1; t < size_for_win - 1; t++)
                    if (pole[i][j] == human_weapon && pole[i + t][j - t] == human_weapon)kr1++;
                if (kr1 == size_for_win - 2) {
                    if (random_variable == 0) pole[i + size_for_win - 2][j - (size_for_win - 2)] = bot_weapon;
                    else pole[i - 1][j + 1] = bot_weapon;
                    victory = end(size, pole, size_for_win);
                    return victory;
                }
            }
        }
        kr1 = 1;
    }



    //Попытка атаки
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - 1; j++) {
            if (pole[i][j] == bot_weapon) {
                if (pole[i][j + 1] == 0 && pole[i][j + 2] == 0) {
                    pole[i][j + 1] = bot_weapon;
                    victory = end(size, pole, size_for_win);
                    return victory;
                }
                if (pole[i][j - 1] == 0 && pole[i][j - 2] == 0) {
                    pole[i][j - 1] = bot_weapon;
                    victory = end(size, pole, size_for_win);
                    return victory;
                }
                if (pole[i + 1][j] == 0 && pole[i + 2][j] == 0) {
                    pole[i + 1][j] = bot_weapon;
                    victory = end(size, pole, size_for_win);
                    return victory;
                }
                if (pole[i - 1][j] == 0 && pole[i - 2][j] == 0) {
                    pole[i - 1][j] = bot_weapon;
                    victory = end(size, pole, size_for_win);
                    return victory;
                }
                if (pole[i + 1][j + 1] == 0 && pole[i + 2][j + 2] == 0) {
                    pole[i + 1][j + 1] = bot_weapon;
                    victory = end(size, pole, size_for_win);
                    return victory;
                }
                if (pole[i + 1][j - 1] == 0 && pole[i + 2][j - 2] == 0) {
                    pole[i + 1][j - 1] = bot_weapon;
                    victory = end(size, pole, size_for_win);
                    return victory;
                }
                if (pole[i - 1][j - 1] == 0 && pole[i - 2][j - 2] == 0) {
                    pole[i - 1][j - 1] = bot_weapon;
                    victory = end(size, pole, size_for_win);
                    return victory;
                }
                if (pole[i - 1][j + 1] == 0 && pole[i - 2][j + 2] == 0) {
                    pole[i - 1][j + 1] = bot_weapon;
                    victory = end(size, pole, size_for_win);
                    return victory;
                }
            }
        }
    }





    //Рандомная атака

    int random_variable1 = rand() % size;
    int random_variable2 = rand() % size;
    pole[random_variable1][random_variable2] = bot_weapon;
    victory = end(size, pole, size_for_win);
    return victory;


}

int end(int size, int pole[size][size], int size_for_win) {
    int victory;
    visual(size, pole);
    victory = check(size, pole, size_for_win);
    // printf("Выполнен ход на %d %d \n", i + 1, j + 1);//
    return victory;
}


void syntax(int *a, int *b, int size, int pole[size][size]) //Контроль вводимых данных
{

    int word, roww, coll;
    word = scanf("%d %d", &roww, &coll);
    while ((word != 2) || roww > size || roww <= 0 || coll > size || coll <= 0 || pole[roww - 1][coll - 1] != 0) {
        if (word != 2) scanf("%*s");
        printf("Ошибка ввода!\n");
        printf("Повторите ввод: ");
        word = scanf("%d %d", &roww, &coll);
    }
    *a = roww;
    *b = coll;
}


int check(int size, int pole[size][size], int size_for_win) //Проверка на победу/ничью
{
    int i, j;
    int victory = 0, kr = 0, nol = 0, c = 0;
    for (i = 0; i < size; i++) { //Проверка по горизонтали
        for (j = 0; j < size - 1; j++) {
            if (kr < size_for_win - 1 && nol < size_for_win - 1) {
                if (pole[i][j] == 1 && pole[i][j + 1] == 1) kr++;
                else kr = 0;
                if (pole[i][j] == 2 && pole[i][j + 1] == 2) nol++;
                else nol = 0;
            }
        }
        victory = check_2(size_for_win, kr, nol);
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
        victory = check_2(size_for_win, kr, nol);
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
        victory = check_2(size_for_win, kr, nol);
        if (victory == 1 || victory == 2) break;
        kr = 0;
        nol = 0;
    }

    for (i = 0; i < size - 1; i++) { //Проверка по другой диагонали
        for (j = 0; j < size - 1; j++) {
            if (kr < size_for_win - 1 && nol < size_for_win - 1) {
                if (pole[i][j] == 1 && pole[i + 1][j - 1] == 1) {
                    kr = 1;
                    for (int t = 1; t < size_for_win - 1; t++) {
                        if (pole[i + t][j - t] == 1 && pole[i + t + 1][j - t - 1] == 1 && i < size - 2 &&
                            j < size - 2)
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
        victory = check_2(size_for_win, kr, nol); //check_2
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

int check_2(int size_for_win, int kr, int nol) {
    int victory = 0;
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
