#include <stdio.h>
#include <stdbool.h>
#include "BotXO.h"


char field[9];

// задаем игровое поле с адресами
void start_field_values() {
    int CellValue = 0;
    for (int m=0; m<=2; m++) {
        for (int n=0; n<=2; n++) {
            CellValue=m*3+(n+1);
            field[CellValue-1]=CellValue+'0';
        }
    }
}

// выводим содержимое поля на экран
void print_field() {
    int Cell = 0;
    for (int m=0; m<=2; m++) {
        for (int n=0; n<=2; n++) {
            Cell=m*3+n;
            printf("|%c|", field[Cell]);
        }
        printf("\n");
    }
}

// проверка выйгрышной комбинации
bool win() {
    // вертикальные и горизонтальные строчки
    for (int w=0; w<=2; w++) {
        if (field[3*w]==field[3*w+1]&&field[3*w+1]==field[3*w+2]) {
            printf ("%c wins!\n", field[3*w]);
            return true;
        }
        if (field[w]==field[w+3]&&field[w+3]==field[w+6]) {
            printf ("%c wins!\n", field[w]);
            return true;
        }
    }
    // диагональные строчки
    if ((field[0]==field[4]&&field[4]==field[8])||
        (field[2]==field[4]&&field[4]==field[6])) {
        printf("Congratulations! %c wins!\n", field[4]);
        return true;
    }
    else {
        return false;
    }
}

// проверка на заполненность поля
bool end_of_field() {
    int v=0;
    for (int e=0; e<=8; e++) {
        if (field[e]=='X'||field[e]=='O') {
            v++;
        }
    }
    if (v==9) {
        return true;
    }
    else {
        return false;
    }
}

// ход человека
void human_move(char p1, char p2) {
    int HumanPos = 0;
    printf("Input %c position\n", p1);
    scanf("%d", &HumanPos);
    // проверка правильности адреса
    if ((HumanPos < 1) || (HumanPos > 9)) {
        printf("Incorrect value\n");
    } else {
        if (field[HumanPos - 1] == p2) {
            // проверка на попытку презаписи
            printf("Cheater detected!\n Lose a turn!\n");
        } else {
            field[HumanPos - 1] = p1;
        }
    }
}

//объявление функторов
void (*gamer01_move) (char p1, char p2);
void (*gamer02_move) (char p1, char p2);

//стартовый экран выбора режима игры
void start_screen() {
    int game_mode;
    int order;
    int difficulty;
    printf("Welcome to Tic Tac Toe\n"
           "Select the type of a game\n"
           "1 - Single Player\n"
           "2 - Multiplayer\n");
    scanf("%d", &game_mode);
    switch (game_mode) {
        case 1:
            printf("Select the order of your move\n"
                   "1 - First\n"
                   "2 - Second\n");
            scanf("%d", &order);
            switch (order) {
                case 1:
                    gamer01_move=human_move;
                    printf("Select a difficulty level\n"
                           "1 - Easy\n"
                           "2 - Medium\n"
                           "3 - Hard\n");
                    scanf("%d", &difficulty);
                    switch (difficulty) {
                        case 1:
                            gamer02_move=bot_easy;
                            break;
                        case 2:
                            gamer02_move= bot_medium;
                            break;
                        case 3:
                            gamer02_move= bot_hard;
                            break;
                        default:
                            printf("something went wrong");
                    }
                    break;
                case 2:
                    gamer02_move= human_move;
                    printf("Select a difficulty level\n"
                           "1 - Easy\n"
                           "2 - Medium\n"
                           "3 - Hard\n");
                    scanf("%d", &difficulty);
                    switch (difficulty) {
                        case 1:
                            gamer01_move=bot_easy;
                            break;
                        case 2:
                            gamer01_move=bot_medium;
                            break;
                        case 3:
                            gamer01_move=bot_hard;
                            break;
                        default:
                            printf("something went wrong\n");
                    }
                    break;
                default:
                    printf("something went wrong\n");
            }
            break;
        case 2:
            gamer01_move=human_move;
            gamer02_move=human_move;
            break;
        default:
            printf("something went wrong\n");
    }
}

int main() {
    start_screen();
    start_field_values();
    print_field();
    int f=1; //счетчик для определения очередности хода
    while (f>0) {
        if (f%2!=0) {
            gamer01_move('X','O');
            print_field();
        }
        else {
            gamer02_move('O','X');
            print_field();
        }
        if (win()==true) {
            printf("Game Over!");
            return 0;
        }
        if (end_of_field()==true) {
            printf("End of the field!\nGame Over!");
            return 0;
        }
        f++;
    }
}