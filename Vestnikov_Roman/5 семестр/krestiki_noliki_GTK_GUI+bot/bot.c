#include "bot.h"
#include <stdlib.h>

int Bot_move(int step, int size, Cell pole[10][10], int size_for_win,
             int human_weapon, int bot_weapon, GtkWidget *grid) {



    int i, j, victory;
    int random_variable;
    int kr1 = 1, nol1 = 1;
    Trigger turn_is_completed = NO;
    random_variable = rand() % 2;
    int x = 0;
    int y = 0;

    //первая атака
    if (step == 1) {
        do {
            int random_variable1 = rand() % size;
            int random_variable2 = rand() % size;
            i = random_variable1;
            j = random_variable2;
        } while (pole[i][j] == human_weapon || pole[i][j] == bot_weapon);
        pole[i][j] = bot_weapon;
        victory = end(size, pole, size_for_win, grid, j, i, bot_weapon);
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
                    if (pole[i][j] == bot_weapon && pole[i][j + t] == bot_weapon) nol1++;
                if (nol1 >= size_for_win - 1) {
                    if (pole[i][j + size_for_win - 1] == EMPTY && j != size_for_win - 2) {
                        pole[i][j + size_for_win - 1] = bot_weapon;
                        x = i;
                        y = j + size_for_win - 1;
                        turn_is_completed = YES;
                    } else if (pole[i][j - 1] == EMPTY && j != 0) {
                        pole[i][j - 1] = bot_weapon;
                        turn_is_completed = YES;
                    }
                    if (turn_is_completed == YES) {
                        victory = end(size, pole, size_for_win, grid, y, x, bot_weapon);
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
                    if (pole[i + size_for_win - 1][j] == EMPTY && i != size_for_win - 2) {
                        pole[i + size_for_win - 1][j] = bot_weapon;
                        x = i + size_for_win - 1;
                        y = j;
                        turn_is_completed = YES;
                    } else if (pole[i - 1][j] == EMPTY && i != 0) {
                        pole[i - 1][j] = bot_weapon;
                        x = i - 1;
                        y = j;
                        turn_is_completed = YES;
                    }
                    if (turn_is_completed == YES) {
                        victory = end(size, pole, size_for_win, grid, y, x, bot_weapon);
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
                        x = i + size_for_win - 1;
                        y = j + size_for_win - 1;
                        turn_is_completed = YES;
                    } else if (pole[i - 1][j - 1] == EMPTY && i != 0 && j != 0) {
                        pole[i - 1][j - 1] = bot_weapon;
                        x = i - 1;
                        y = j - 1;
                        turn_is_completed = YES;
                    }
                    if (turn_is_completed == YES) {
                        victory = end(size, pole, size_for_win, grid, y, x, bot_weapon);
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
                 (j == size - size_for_win + 1 && i == EMPTY) || (j == 0 && i == size - size_for_win + 1))) {
                for (int t = 1; t < size_for_win - 1; t++)
                    if (pole[i][j] == 1 && pole[i + t][j - t] == bot_weapon)
                        nol1++;
                if (nol1 >= size_for_win - 1) {
                    if (pole[i + size_for_win - 1][j - (size_for_win - 1)] == EMPTY && i != size_for_win - 2 &&
                        j != -(size_for_win - 2)) {
                        pole[i + size_for_win - 1][j - (size_for_win - 1)] = bot_weapon;
                        x = i + size_for_win - 1;
                        y = j - (size_for_win - 1);
                        turn_is_completed = YES;
                    } else if (pole[i - 1][j + 1] == EMPTY && i != 0 ) {
                        pole[i - 1][j + 1] = bot_weapon;
                        x = i - 1;
                        y = j + 1;
                        turn_is_completed = YES;
                    }
                    if (turn_is_completed == YES) {
                        victory = end(size, pole, size_for_win, grid, y, x, bot_weapon);
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
                victory = end(size, pole, size_for_win, grid, i, 1, bot_weapon);
                return victory;
            }
        }
        for (j = 0; i < size; i++) {
            if (pole[1][j] == 0 && pole[0][j] == bot_weapon && pole[2][j] == bot_weapon) {
                pole[1][j] = bot_weapon;
                victory = end(size, pole, size_for_win, grid, 1, j, bot_weapon);
                return victory;
            }
        }
        if (pole[1][1] == 0 && pole[0][0] == bot_weapon && pole[2][2] == bot_weapon) {
            pole[1][1] = bot_weapon;
            victory = end(size, pole, size_for_win, grid, 1, 1, bot_weapon);
            return victory;
        }
        if (pole[1][1] == 0 && pole[2][0] == bot_weapon && pole[0][2] == bot_weapon) {
            pole[1][1] = bot_weapon;
            victory = end(size, pole, size_for_win, grid, 1, 1, bot_weapon);
            return victory;
        }
    }


    //Переход к обороне
    kr1 = 1;
    nol1 = 1;
    random_variable = rand() % 2;
    for (i = 0; i < size; i++) {        //Проверка по горизонтали
        for (j = 0; j < size - (size_for_win - 1); j++) {
            if (pole[i][j] == human_weapon &&
                ((pole[i][j + size_for_win - 1] == bot_weapon) || pole[i][j - 1] == bot_weapon || j == 0 ||
                 j == size - size_for_win + 1)) {
                for (int t = 1; t < size_for_win; t++)
                    if (pole[i][j] == human_weapon && pole[i][j + t] == human_weapon)kr1++;
                if (kr1 == size_for_win - 1) {
                    if (pole[i][j + size_for_win - 1] == EMPTY && j != size_for_win - 2) {
                        pole[i][j + size_for_win - 1] = bot_weapon;
                        x = i;
                        y = j + size_for_win - 1;
                        turn_is_completed = YES;
                    } else if (pole[i][j - 1] == EMPTY && j != 0)  {
                        pole[i][j - 1] = bot_weapon;
                        x = i;
                        y = j - 1;
                        turn_is_completed = YES;
                    }
                    if (turn_is_completed == YES) {
                        victory = end(size, pole, size_for_win, grid, y, x, bot_weapon);
                        return victory;
                    }
                }
            }
        }
        kr1 = 1;
    }
    for (j = 0; j < size; j++) {        //Проверка по вертикали
        for (i = 0; i < size - (size_for_win - 1); i++) {
            if (pole[i][j] == human_weapon &&
                ((pole[i + size_for_win - 1][j] == bot_weapon) || pole[i - 1][j] == bot_weapon || i == 0 ||
                 i == size - size_for_win + 1)) {
                for (int t = 1; t < size_for_win; t++)
                    if (pole[i][j] == human_weapon && pole[i + t][j] == human_weapon)kr1++;
                if (kr1 == size_for_win - 1) {
                    if (pole[i + size_for_win - 1][j] == EMPTY && i != size_for_win - 2) {
                        pole[i + size_for_win - 1][j] = bot_weapon;
                        x = i + size_for_win - 1;
                        y = j;
                        turn_is_completed = YES;
                    } else if (pole[i - 1][j] == EMPTY && i != 0) {
                        pole[i - 1][j] = bot_weapon;
                        x = i - 1;
                        y = j;
                        turn_is_completed = YES;
                    }
                    if (turn_is_completed == YES) {
                        victory = end(size, pole, size_for_win, grid, y, x, bot_weapon);
                        return victory;
                    }
                }
            }
        }
        kr1 = 1;
    }

    for (i = 0; i < size - (size_for_win - 1); i++) {        //Проверка по одной диагонали
        for (j = 0; j < size - (size_for_win - 1); j++) {
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
                        x = i + size_for_win - 1;
                        y = j + size_for_win - 1;
                        turn_is_completed = YES;
                    } else if (pole[i - 1][j - 1] == EMPTY && i != 0&& j != 0)  {
                        pole[i - 1][j - 1] = bot_weapon;
                        x = i - 1;
                        y = j - 1;
                        turn_is_completed = YES;
                    }
                    if (turn_is_completed == YES) {
                        victory = end(size, pole, size_for_win, grid, y, x, bot_weapon);
                        return victory;
                    }
                }
            }
        }
        kr1 = 1;
    }

    for (i = 1; i < size - (size_for_win - 1); i++) {        //Проверка по другой диагонали
        for (j = 1; j < size - (size_for_win - 1); j++) {
            if (pole[i][j] == human_weapon &&
                (pole[i - 1][j + 1] == EMPTY || pole[i + size_for_win - 1][j - (size_for_win - 1)] == EMPTY)) {
                for (int t = 1; t < size_for_win; t++)
                    if (pole[i][j] == human_weapon && pole[i + t][j - t] == human_weapon)kr1++;
                if (kr1 == size_for_win - 1) {
                    if (pole[i + size_for_win - 1][j - (size_for_win - 1)] == EMPTY && i != size_for_win - 2 &&
                        j != -(size_for_win - 2)) {
                        pole[i + size_for_win - 1][j - (size_for_win - 1)] = bot_weapon;
                        x = i + size_for_win - 1;
                        y = j - (size_for_win - 1);
                        turn_is_completed = YES;
                    } else if (pole[i - 1][j + 1] == EMPTY) {
                        pole[i - 1][j + 1] = bot_weapon;
                        x = i - 1;
                        y = j + 1;
                        turn_is_completed = 1;
                    }
                    if (turn_is_completed == YES) {
                        victory = end(size, pole, size_for_win, grid, y, x, bot_weapon);
                        return victory;
                    }
                }
            }
        }
        kr1 = 1;
    }
    //Переход к атаке и предварительной победе

    for (i = 0; i < size; i++) {        //Проверка по горизонтали
        for (j = 1; j < size - (size_for_win - 2); j++) {
            if (pole[i][j - 1] == 0 && pole[i][j] == bot_weapon && pole[i][j + size_for_win - 2] == EMPTY) {
                for (int t = 1; t < size_for_win - 1; t++)
                    if (pole[i][j] == bot_weapon && pole[i][j + t] == bot_weapon)nol1++;
                if (nol1 >= size_for_win - 2) {
                    if (random_variable == 0) {
                        pole[i][j + size_for_win - 2] = bot_weapon;
                        x = i;
                        y = j + size_for_win - 2;
                    } else {
                        pole[i][j - 1] = bot_weapon;
                        x = i;
                        y = j - 1;
                    }
                    victory = end(size, pole, size_for_win, grid, y, x, bot_weapon);
                    return victory;
                }
            }
        }
        nol1 = 1;
    }

    for (j = 0; j < size; j++) {        //Проверка по вертикали
        for (i = 1; i < size - (size_for_win - 2); i++) {
            if (pole[i - 1][j] == EMPTY && pole[i][j] == bot_weapon && pole[i + size_for_win - 2][j] == EMPTY) {
                for (int t = 1; t < size_for_win - 1; t++)
                    if (pole[i][j] == bot_weapon && pole[i + t][j] == bot_weapon)nol1++;
                if (nol1 >= size_for_win - 2) {
                    if (random_variable == 0) {
                        pole[i + size_for_win - 2][j] = bot_weapon;
                        x = i + size_for_win - 2;
                        y = j;
                    } else {
                        pole[i - 1][j] = bot_weapon;
                        x = i - 1;
                        y = j;
                    }
                    victory = end(size, pole, size_for_win, grid, y, x, bot_weapon);
                    return victory;
                }
            }
        }
        nol1 = 1;
    }

    for (i = 1; i < size - (size_for_win - 2); i++) {        //Проверка по одной диагонали
        for (j = 1; j < size - (size_for_win - 2); j++) {
            if (pole[i - 1][j - 1] == 0 && pole[i][j] == bot_weapon &&
                pole[i + size_for_win - 2][j + size_for_win - 2] == EMPTY) {
                for (int t = 1; t < size_for_win - 1; t++)
                    if (pole[i][j] == bot_weapon && pole[i + t][j + t] == bot_weapon)nol1++;
                if (nol1 >= size_for_win - 2) {
                    if (random_variable == 0) {
                        pole[i + size_for_win - 2][j + size_for_win - 2] = bot_weapon;
                        x = i + size_for_win - 2;
                        y = j + size_for_win - 2;
                    } else {
                        pole[i - 1][j - 1] = bot_weapon;
                        x = i - 1;
                        y = j - 1;
                    }
                    victory = end(size, pole, size_for_win, grid, y, x, bot_weapon);
                    return victory;
                }
            }
        }
        nol1 = 1;
    }

    for (i = 1; i < size - (size_for_win - 2); i++) {        //Проверка по другой диагонали
        for (j = 1; j < size - 1; j++) {
            if (pole[i - 1][j + 1] == EMPTY && pole[i][j] == bot_weapon &&
                pole[i + size_for_win - 2][j - (size_for_win - 2)] == EMPTY) {
                for (int t = 1; t < size_for_win - 1; t++)
                    if (pole[i][j] == bot_weapon && pole[i + t][j - t] == bot_weapon)nol1++;
                if (nol1 >= size_for_win - 2) {
                    if (random_variable == 0) {
                        pole[i + size_for_win - 2][j - (size_for_win - 2)] = bot_weapon;
                        x = i + size_for_win - 2;
                        y = j - (size_for_win - 2);
                    } else {
                        pole[i - 1][j + 1] = bot_weapon;
                        x = i - 1;
                        y = j + 1;
                    }
                    victory = end(size, pole, size_for_win, grid, y, x, bot_weapon);
                    return victory;
                }
            }
        }
        nol1 = 1;
    }

    //Переход к основной обороне
    for (i = 0; i < size; i++) {        //Проверка по горизонтали
        for (j = 1; j < size - (size_for_win - 2); j++) {
            if (pole[i][j - 1] == EMPTY && pole[i][j] == human_weapon && pole[i][j + size_for_win - 2] == EMPTY) {
                for (int t = 1; t < size_for_win - 1; t++)
                    if (pole[i][j] == human_weapon && pole[i][j + t] == human_weapon)kr1++;
                if (kr1 == size_for_win - 2) {
                    if (random_variable == 0) {
                        pole[i][j + size_for_win - 2] = bot_weapon;
                        x = i;
                        y = j + size_for_win - 2;
                    } else {
                        pole[i][j - 1] = bot_weapon;
                        x = i;
                        y = j - 1;
                    }
                    victory = end(size, pole, size_for_win, grid, y, x, bot_weapon);
                    return victory;
                }
            }
        }
        kr1 = 1;
    }

    for (j = 0; j < size; j++) {        //Проверка по вертикали
        for (i = 1; i < size - (size_for_win - 2); i++) {
            if (pole[i - 1][j] == EMPTY && pole[i][j] == human_weapon && pole[i + size_for_win - 2][j] == EMPTY) {
                for (int t = 1; t < size_for_win - 1; t++)
                    if (pole[i][j] == human_weapon && pole[i + t][j] == human_weapon)kr1++;
                if (kr1 == size_for_win - 2) {
                    if (random_variable == 0) {
                        pole[i + size_for_win - 2][j] = bot_weapon;
                        x = i + size_for_win - 2;
                        y = j;
                    } else {
                        pole[i - 1][j] = bot_weapon;
                        x = i - 1;
                        y = j;
                    }
                    victory = end(size, pole, size_for_win, grid, y, x, bot_weapon);
                    return victory;
                }
            }
        }
        kr1 = 1;
    }

    for (i = 1; i < size - (size_for_win - 2); i++) {        //Проверка по одной диагонали
        for (j = 1; j < size - (size_for_win - 2); j++) {
            if (pole[i - 1][j - 1] == EMPTY && pole[i][j] == human_weapon &&
                pole[i + size_for_win - 2][j + size_for_win - 2] == EMPTY) {
                for (int t = 1; t < size_for_win - 1; t++)
                    if (pole[i][j] == human_weapon && pole[i + t][j + t] == human_weapon)kr1++;
                if (kr1 == size_for_win - 2) {
                    if (random_variable == 0) {
                        pole[i + size_for_win - 2][j + size_for_win - 2] = bot_weapon;
                        x = i + size_for_win - 2;
                        y = j + size_for_win - 2;
                    } else {
                        pole[i - 1][j - 1] = bot_weapon;
                        x = i - 1;
                        y = j - 1;
                    }
                    victory = end(size, pole, size_for_win, grid, y, x, bot_weapon);
                    return victory;
                }
            }
        }
        kr1 = 1;
    }

    for (i = 1; i < size - (size_for_win - 2); i++) {        //Проверка по другой диагонали
        for (j = 1; j < size - 1; j++) {
            if (pole[i - 1][j + 1] == EMPTY && pole[i][j] == human_weapon &&
                pole[i + size_for_win - 2][j - (size_for_win - 2)] == EMPTY) {
                for (int t = 1; t < size_for_win - 1; t++)
                    if (pole[i][j] == human_weapon && pole[i + t][j - t] == human_weapon)kr1++;
                if (kr1 == size_for_win - 2) {
                    if (random_variable == 0) {
                        pole[i + size_for_win - 2][j - (size_for_win - 2)] = bot_weapon;
                        x = i + size_for_win - 2;
                        y = j - (size_for_win - 2);
                    } else {
                        pole[i - 1][j + 1] = bot_weapon;
                        x = i - 1;
                        y = j + 1;
                    }
                    victory = end(size, pole, size_for_win, grid, y, x, bot_weapon);
                    return victory;
                }
            }
        }
        kr1 = 1;
    }



    //Попытка атаки
    for (i = 0; i < size - 2; i++) {
        for (j = 0; j < size - 2; j++) {
            if (pole[i][j] == bot_weapon) {
                if (pole[i][j + 1] == EMPTY && pole[i][j + 2] == EMPTY) {
                    pole[i][j + 1] = bot_weapon;
                    x = i;
                    y = j + 1;
                    victory = end(size, pole, size_for_win, grid, y, x, bot_weapon);
                    return victory;
                }
                if (pole[i][j - 1] == EMPTY && pole[i][j - 2] == EMPTY && j != 0) {
                    pole[i][j - 1] = bot_weapon;
                    x = i;
                    y = j - 1;
                    victory = end(size, pole, size_for_win, grid, y, x, bot_weapon);
                    return victory;
                }
                if (pole[i + 1][j] == EMPTY && pole[i + 2][j] == EMPTY) {
                    pole[i + 1][j] = bot_weapon;
                    x = i + 1;
                    y = j;
                    victory = end(size, pole, size_for_win, grid, y, x, bot_weapon);
                    return victory;
                }
                if (pole[i - 1][j] == EMPTY && pole[i - 2][j] == EMPTY && i != 0) {
                    pole[i - 1][j] = bot_weapon;
                    x = i - 1;
                    y = j;
                    victory = end(size, pole, size_for_win, grid, y, x, bot_weapon);
                    return victory;
                }
                if (pole[i + 1][j + 1] == EMPTY && pole[i + 2][j + 2] == EMPTY) {
                    pole[i + 1][j + 1] = bot_weapon;
                    x = i + 1;
                    y = j + 1;
                    victory = end(size, pole, size_for_win, grid, y, x, bot_weapon);
                    return victory;
                }
                if (pole[i + 1][j - 1] == EMPTY && pole[i + 2][j - 2] == EMPTY && j != 0) {
                    pole[i + 1][j - 1] = bot_weapon;
                    x = i + 1;
                    y = j - 1;
                    victory = end(size, pole, size_for_win, grid, y, x, bot_weapon);
                    return victory;
                }
                if (pole[i - 1][j - 1] == EMPTY && pole[i - 2][j - 2] == EMPTY && i != 0 && j != 0)  {
                    pole[i - 1][j - 1] = bot_weapon;
                    x = i - 1;
                    y = j - 1;
                    victory = end(size, pole, size_for_win, grid, y, x, bot_weapon);
                    return victory;
                }
                if (pole[i - 1][j + 1] == EMPTY && pole[i - 2][j + 2] == EMPTY && i != 0) {
                    pole[i - 1][j + 1] = bot_weapon;
                    x = i - 1;
                    y = j + 1;
                    victory = end(size, pole, size_for_win, grid, y, x, bot_weapon);
                    return victory;
                }
            }
        }
    }

        do {
            int random_variable1 = rand() % size;
            int random_variable2 = rand() % size;
            i = random_variable1;
            j = random_variable2;
        } while (pole[i][j] == human_weapon || pole[i][j] == bot_weapon);
        pole[i][j] = bot_weapon;
        victory = end(size, pole, size_for_win, grid, j, i, bot_weapon);
        return victory;
}

int end(int size, Cell pole[10][10], int size_for_win, GtkWidget *grid, int x, int y, int bot_weapon) {
    Victory_result victory = NOTHING;
    GtkWidget *cross_image, *zero_image;
    cross_image = gtk_image_new_from_file ("Pictures\\cross.png");
    zero_image = gtk_image_new_from_file ("Pictures\\zero.png");
    if (bot_weapon==CROSS)
    {
        gtk_button_set_label((GtkButton *) gtk_grid_get_child_at(GTK_GRID(grid), x, y), NULL);
        gtk_button_set_image((GtkButton *) gtk_grid_get_child_at(GTK_GRID(grid), x, y), cross_image);
    }
    else if (bot_weapon==ZERO)
    {
        gtk_button_set_label((GtkButton *) gtk_grid_get_child_at(GTK_GRID(grid), x, y), NULL);
        gtk_button_set_image((GtkButton *) gtk_grid_get_child_at(GTK_GRID(grid), x, y), zero_image);
    }
    victory = check(size, pole, size_for_win);
    return victory;
}