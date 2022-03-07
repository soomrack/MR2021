#include <stdio.h>
#include <stdlib.h>

//Создаем массив поля, один индекс это одна ячейка на поле
char field[9] = {'1','2','3','4','5','6','7','8','9'};


//Функция хода
//Игрок выбирает ячейку, куда будет помещен крестик

void x_move(void) {
    int position;
    printf("Krestiki move:\n");
    scanf("%d",&position);
    if ((field[position - 1] == 'X')||(field[position - 1] == 'O')) {
        printf("Cell is busy!\n");
        x_move();
    } else {
        field[position - 1] = 'X';
    }
}


//Идентичная функция хода, только для ноликов

void o_move(void) {
    int position;
    printf("Noliki move:\n");
    scanf("%d",&position);
    if ((field[position - 1] == 'X')||(field[position - 1] == 'O')) {
        printf("Cell is busy!\n");
        o_move();
    } else {
        field[position - 1] = 'O';
    }
}


//Функция вывода состояния поля на экран

void output(char point[9]) {
    printf("  %c  |  %c  |  %c  \n"
           "–––––|–––––|–––––\n"
           "  %c  |  %c  |  %c  \n"
           "–––––|–––––|–––––\n"
           "  %c  |  %c  |  %c  \n"
           "=================\n"
           "=================\n",
           point[0], point[1], point[2],
           point[3], point[4], point[5],
           point[6], point[7], point[8]);
}


//Если функция win_check обнаружит необходимые последовательности для победы
//то функция who_win узнает кто конкретно победил

char who_win(char player) {
    if (player == 'O') {
        output (field);
        printf("\n<<<NOLIKI WIN!>>>\n");
        exit(1);
    } else {
        output (field);
        printf("\n<<<KRESTIKI WIN!>>>\n");
        exit(1);
    }
}


//Функция win_check проверяет необходимые последовательности для победы после каждого хода

void win_check(void) {

    // Проверяем диагональ
    if ((field[0] == field[4]) && (field[4] == field[8])) {
        who_win(field[0]);
    }

    // Проверяем другую диагональ
    if ((field[6] == field [4]) && (field [4] == field [2])) {
        who_win(field[6]);
    }

    // Проверяем все горизонтали
    for (int i = 0; i <= 6; i = i + 3) {
        if ((field[i] == field[i + 1]) && (field[i + 1] == field[i + 2])) {
            who_win(field[i]);
        }
    }

    // Проверяем все вертикали
    for (int i = 0; i <= 2; i++) {
        if ((field[i] == field[i + 3]) && (field[i + 3] == field[i + 6])) {
            who_win(field[i]);
        }
    }
}


//Главный цикл игры

int main() {

    // Инструкция
    printf("=================\n"
           "How to play:\n"
           "Every cell has an index.\n"
           "When it is your move, just write cell index.\n"
           "Example:\n"
           "Krestiki move:\n"
           "5\n"
           "=================\n");

    for (int g = 0; g <= 4; g++) {
        output (field);
        x_move();
        win_check();

        // Если поле заполнится, то победила дружба
        if (g == 4) {
            printf("Friendship WIN!");
            exit(1);
        }

        output (field);
        o_move();
        win_check();
    }
    return 0;
}