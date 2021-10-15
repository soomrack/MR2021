#include <stdio.h>
#include <stdbool.h>
#include "BotXO.h"

char arr[8];
int x;
int a;
int game_mode;
int order;
int difficulty;

// задаем игровое поле с адресами
void start_field_values() {
    for (int m=0; m<=2; m++) {
        for (int n=0; n<=2; n++) {
            a=m*3+(n+1);
            arr[a-1]=a+'0';
        }
    }
}

// выводим содержимое поля на экран
void print_field() {
    for (int m=0; m<=2; m++) {
        for (int n=0; n<=2; n++) {
            a=m*3+n;
            printf("|%c|", arr[a]);
        }
        printf("\n");
    }
}

// проверка выйгрышной комбинации
bool win() {
    // вертикальные и горизонтальные строчки
    for (int w=0; w<=2; w++) {
        if (arr[3*w]==arr[3*w+1]&&arr[3*w+1]==arr[3*w+2]) {
            printf ("%c wins!\n", arr[3*w]);
            return true;
        }
        if (arr[w]==arr[w+3]&&arr[w+3]==arr[w+6]) {
            printf ("%c wins!\n", arr[w]);
            return true;
        }
    }
    // диагональные строчки
    if ((arr[0]==arr[4]&&arr[4]==arr[8])||
        (arr[2]==arr[4]&&arr[4]==arr[6])) {
        printf("Congratulations! %c wins!\n", arr[4]);
        return true;
    }
}

// проверка на заполненность поля
bool end_of_field() {
    int v=0;
    for (int e=0; e<=8; e++) {
        if (arr[e]=='X'||arr[e]=='O') {
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
    printf("Input %c position\n", p1);
    scanf("%d", &x);
    // проверка правильности адреса
    if ((x < 1) || (x > 9)) {
        printf("Incorrect value\n");
    } else {
        if (arr[x - 1] == p2) {
            // проверка на попытку презаписи
            printf("Cheater detected!\n Lose a turn!\n");
        } else {
            arr[x - 1] = p1;
        }
    }
}

//объявление функторов
void (*gamer01_move) (char p1, char p2);
void (*gamer02_move) (char p1, char p2);

//стартовый экран выбора режима игры
int start_screen() {
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
                            printf("something went wrong");
                    }
                    break;
            }
            break;
        case 2:
            gamer01_move=human_move;
            gamer02_move=human_move;
            break;
        default:
            printf("something went wrong");
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