#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

char field[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};

void show_field();
int player_movement();
int bot_movement();
bool win_set();

int main() {
    show_field();
    printf("crosses go first\n");
    for (int i = 0; i < 9;) {
        field[player_movement()-1] = 'X';
        show_field();
        i++;
        if (win_set() == 1) {
           printf("crosses wins");
           break;
        }
        if (i == 9){
            printf("dead heat");
            break;
        }
        printf("bot movement \n");
        field[bot_movement()] = 'O';
        show_field();
        i++;
        if (win_set() == 1) {
            printf("zeros wins");
            break;
        }
    }

    return 0;
}



void show_field() {
    printf("|%c|%c|%c|\n|%c|%c|%c|\n|%c|%c|%c|\n", field[0], field[1], field[2], field[3], field[4], field[5], field[6], field[7], field[8]);
}
int player_movement() {
    int move = 0;
    scanf("%d", &move);
    if ((move < 1)||(move > 9)) {
        printf("choose field from 1 to 9\n");
        player_movement();
    }
    if (field[move-1] != ' ') {
        printf("choose another cell\n");
        player_movement();
    }
    else {
        return move;
    }
}

int bot_movement() {
    srand(time(NULL));
    int move = rand()%8;
    if (field[move-1] != ' ') {
        bot_movement();
    }
    else {
        return move;
    }
}

bool win_set() {
    bool win = 0;
    if (((field[0] == field[3])&&(field[0] == field[6])&&(field[0] != ' ')) ||
            ((field[1] == field[4])&&(field[1] == field[7])&&(field[1] != ' ') ) ||
            ((field[2] == field[5])&&(field[2] == field[8])&&(field[2] != ' ') ) ||
            ((field[0] == field[2])&&(field[1] == field[2])&&(field[0] != ' ') ) ||
            ((field[3] == field[4])&&(field[3] == field[5])&&(field[3] != ' ') ) ||
            ((field[6] == field[7])&&(field[6] == field[8])&&(field[6] != ' ') ) ||
            ((field[0] == field[4])&&(field[0] == field[8])&&(field[0] != ' ') ) ||
            ((field[2] == field[4])&&(field[2] == field[6])&&(field[2] != ' ') )) {
        win = 1;
    }
    return win;
}
