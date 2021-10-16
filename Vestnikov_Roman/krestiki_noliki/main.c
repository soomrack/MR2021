#include <stdio.h>
#include "movement.h"

int field_size();

void completion(int size, int pole[size][size]);

void rules(int size, int size_for_win);

void play(int size, int pole[size][size], int size_for_win);

void congratulation(int victory);

int for_win(int size);

void visual(int size, int pole[size][size]);

void bot_or_human(int *a, int *b);


int main() {
    int contin = 0;
    do {
        int size = field_size();
        int pole[size][size];
        int size_for_win = for_win(size);
        completion(size, pole);
        rules(size, size_for_win);
        visual(size, pole);
        play(size, pole, size_for_win);
        printf("\n\nЖелаете продолжить?\n(нажмите 2 - для выхода, любое другое число - для продолжения)\n");
        scanf("%d", &contin);
    } while (contin != 2);
    printf("До свидания!\n");
    return 0;
}

int field_size() {
    int word, size;
    printf("Какой размер поля вы хотите? (введите 3 для стандартной игры)\n");
    word = scanf("%d", &size);
    while ((word != 1) || size > 20 || size < 3) {
        if (word != 1) scanf("%*s");
        printf("Некорректный ввод!\n");
        printf("Повторите попытку: ");
        word = scanf("%d", &size);
    }

    return size;
}

int for_win(int size) {
    int size_for_win;
    if (size == 3) size_for_win = 3;
    else if (size < 8) size_for_win = 4;
    else size_for_win = 5;

    return size_for_win;
}

void visual(int size, int pole[size][size]) // Отображает поле
{

    for (int t = 0; t < size; t++) printf("==");
    printf("=\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (pole[i][j] == 0) printf("| ");
            if (pole[i][j] == 1) printf("|X");
            if (pole[i][j] == 2) printf("|0");
        }
        printf("| %d\n", i + 1);
        for (int t = 0; t < size; t++) printf("==");
        printf("=\n");
    }
    for (int t = 0; t < size; t++) printf(" %d", t + 1);
    printf("\n");
}

void completion(int size, int pole[size][size])   //Первоначальное заполнение поля пустными клетками
{
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++)
            pole[i][j] = 0;
    }
}

void rules(int size, int size_for_win)     //Правила
{
    printf("Добро пожаловать в игру!\n");
    printf("Правила игры: первым ходит крестик.\nПроизводится ввод с клавиатуры двух чисел через пробел.\nСперва вводится номер строки, затем номер столбца\n");
    printf("Затем ход передаётся второму игроку (нолику)\n");
    printf("Игра происходит на поле %dx%d\n", size, size);
    printf("Победа достигается при сборе %d клеток с крестиком/ноликом подряд по горизонтали/вертикали/диагонали.\n",
           size_for_win);
}

void bot_or_human(int *a, int *b) {
    int choice1, choice2, word;
    printf("Инициализация Игрока 1: нажмите 1, если вы человек / нажмите 2, если вы бот\n");
    word = scanf("%d", &choice1);
    while ((word != 1) || (choice1 != 1 && choice1 != 2)) {
        if (word != 1) scanf("%*s");
        printf("Некорректный ввод!\n");
        printf("Повторите попытку: ");
        word = scanf("%d", &choice1);
    }
    printf("Инициализация Игрока 2: нажмите 1, если вы человек / нажмите 2, если вы бот\n");
    word = scanf("%d", &choice2);
    while ((word != 1) || (choice2 != 1 && choice2 != 2)) {
        if (word != 1) scanf("%*s");
        printf("Некорректный ввод!\n");
        printf("Повторите попытку: ");
        word = scanf("%d", &choice2);
    }
    *a = choice1;
    *b = choice2;
}


void play(int size, int pole[size][size], int size_for_win)      //Ход игры
{
    int step, victory, choice1, choice2, human_weapon, bot_weapon;
    victory = 0;
    bot_or_human(&choice1, &choice2);
    int (*Gamer01_move)(int, int, int pole[size][size], int, int, int);
    int (*Gamer02_move)(int, int, int pole[size][size], int, int, int);

    switch (choice1) {
        case 1:
            Gamer01_move = Human_move;
            break;
        case 2:
            Gamer01_move = Bot_move;
            break;
    }
    switch (choice2) {
        case 1:
            Gamer02_move = Human_move;
            break;
        case 2:
            Gamer02_move = Bot_move;
            break;
    }

    for (step = 1; victory != 1 && victory != 2 && victory != 3; step++) {
        switch (choice1) {
            case 1:
                human_weapon = 1;
                break;
            case 2:
                bot_weapon = 1;
                break;
        }

        printf("%d ход - крестик\n", step);
        victory = Gamer01_move(step, size, pole, size_for_win, human_weapon, bot_weapon);     //Крестик
        if (victory == 1 || victory == 3) break;
        switch (choice2) {
            case 1:
                human_weapon = 2;
                break;
            case 2:
                bot_weapon = 2;
                break;
        }
        printf("%d ход - нолик\n", step);
        victory = Gamer02_move(step, size, pole, size_for_win, human_weapon, bot_weapon);     //Нолик
    }
    congratulation(victory);
}


void congratulation(int victory)        //Поздравление победителя / объявление ничьей
{
    if (victory == 1) printf("Поздравляем крестик с победой!\n");
    if (victory == 2) printf("Поздравляем нолик с победой!\n");
    if (victory == 3) printf("Ничья!\n");
}