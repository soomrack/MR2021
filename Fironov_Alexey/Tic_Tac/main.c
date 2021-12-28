#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stdbool.h"
#include "string.h"

void first_print();
void game_zone_print (unsigned int cell [9]);

//------------------------Players_initialization------------------------------------
struct Player {
    char player_name[20];      // Players name
    unsigned int player_type;   // Player Human (1) or Bot (2)
    char difficulty;           // Bot difficulty 1-4
    unsigned int turn;          // Players turn: 1-st (1) or 2-nd (2)
};

/* made for the future */
void choose_difficulty(struct Player *p2) {     //Bot difficulty choose
    char key = 0;
    printf("Choose your enemy difficulty!\n");
    printf(" (1) Noob\n (2) Beginner\n (3) Normal\n (4) Live only once!\n");
    while (key < 49 || key > 52) {
        scanf(" %c", &key);
    }
    p2->difficulty = key - 49;
}

void init_P1(struct Player *p1) {
    printf("Enter your name\n");
    scanf("%s", p1->player_name);
};

void init_P2(struct Player *p2) {
    char key = 0;
    printf("Choose your fighter!\n (1) Player 2\n (2) Andrew the Bot\n");
    while (key < 49 || key > 50) {
        scanf(" %c", &key);
    }

    if (key == 50) {      //If u've chosen the Bot - u've to choose the difficulty
        p2->player_type = 1;
        strcpy(p2->player_name, "Andrew_the_Bot");
        choose_difficulty(p2);

    } else {
        p2->player_type = 0;
        printf("Enter p2 name:\n");
        scanf("%s", p2->player_name);
        printf("\n\n");
    }
}

//-----------------------------Turn_initialization-------------------------------------------
void heads_and_tails(struct Player *p1, struct Player *p2) { //finding of 1-st and 2-nd player
    printf("Heads or Tails \n (1) Heads \n (2) Tails\n");
    char key = 0;
    while (key < 49 || key > 50) {
        scanf(" %c", &key);
    }
    unsigned int random_num = random() % 2;
    if (key - 49 == random_num) {
        p1->turn = 1;
        p2->turn = 2;
        printf("First turn (X) belongs to %s \n\n", p1->player_name);
    } else {
        p1->turn = 2;
        p2->turn = 1;
        printf("First turn (X) belongs to %s \n\n", p2->player_name);
    }
}

//-------------------------------Computer_turn------------------------------------------------
unsigned int computer_step(unsigned int cell[9], unsigned int turn_sign) //It must take p2->difficulty
{
    unsigned int step = 42;
    while (cell[step] != 0) {
        step = random() % 9;
    }
    cell[step] = turn_sign;
    game_zone_print(cell);
}

//-----------------------------------Player_turn-----------------------------------------------
void player_step(unsigned int cell[9], unsigned int turn_sign)
{
    unsigned int istep = 42; // Just a random num
    printf("Enter your cell\n");
    while (cell[istep] != 0) {
        char step = 0;
        while (step < 48 || step > 56) {
            scanf(" %c", &step);
        }
        istep = step - 48;
    }
    cell[istep] = turn_sign;
    game_zone_print(cell);
}

//--------------------------Gaming_zone_initialization-----------------------------------------
int game_zone_initialization(unsigned int cell[9]) {
    for (int i = 0; i < 9; i++) {
        cell[i] = 0;
        // printf("%d r= %d c= %d\n", cell [row][column], row, column);
    }
    first_print();
}

//---------------------------------Visualization------------------------------------------------
void game_zone_print(unsigned int cell[9])
{
    printf(" --- --- ---\n");
    for (int row = 0; row < 3; row++){
        printf("|");
        for (int column = 0; column < 3; column++) {
            if (cell[row *3 + column] == 0){printf(" %d |", row * 3 + column);}
            if (cell[row *3 + column] == 1){printf(" X |");}
            if (cell[row *3 + column] == 2){printf(" O |");}
        }
        printf("\n --- --- ---\n");
    }
}

void first_print() {
    int row = 0;
    printf("\n Cells position is described below\n\n");
    printf(" --- --- ---\n");
    int temp = 0;
    while (row < 3) {
        printf("|");
        int column = 0;
        while (column < 3) {
            printf(" %d |", temp);
            temp++;
            column++;
        }
        printf("\n --- --- ---\n");
        row++;
    }
    printf("\n Now let's START!\n");
}

//------------------------------------Win_check------------------------------------------
unsigned int win_check(unsigned int cell[9]) {

    if ((cell[0] == cell[1]) && (cell [0] == cell[2]) && (cell[0] != 0)){ return 1; }
    if ((cell[3] == cell[4]) && (cell [3] == cell[5]) && (cell[3] != 0)){ return 1; }
    if ((cell[6] == cell[7]) && (cell [6] == cell[8]) && (cell[6] != 0)){ return 1; }
    if ((cell[0] == cell[3]) && (cell [0] == cell[6]) && (cell[0] != 0)){ return 1; }
    if ((cell[1] == cell[4]) && (cell [1] == cell[7]) && (cell[1] != 0)){ return 1; }
    if ((cell[2] == cell[5]) && (cell [2] == cell[8]) && (cell[2] != 0)){ return 1; }
    if ((cell[0] == cell[4]) && (cell [0] == cell[8]) && (cell[0] != 0)){ return 1; }
    if ((cell[2] == cell[4]) && (cell [2] == cell[6]) && (cell[2] != 0)){ return 1; }

    return 0;
}

int main() {

    struct Player player1;// Human
    init_P1(&player1);

    struct Player player2;// Human or Bot
    init_P2(&player2);

    heads_and_tails(&player1, &player2);

    unsigned int cell[9];
    unsigned int row = 0;
    unsigned int column = 0;

    game_zone_initialization(cell);

    unsigned int win = 0;
    unsigned int turn = 0;
    while (turn < 9 && win == 0)
    {
        unsigned int turn_sign = (turn % 2 + 1);

        if (player1.turn == turn_sign) {
            printf("turn of %s\n", player1.player_name);
            player_step(cell, turn_sign);
            win = win_check (cell);
            if (win) {printf ("Congratulations!\n %s won!", player1.player_name);}
        } else{
            printf("turn of %s\n", player2.player_name);

            if (player2.player_type == 1) {
                computer_step(cell, turn_sign);
            } else{
                player_step(cell, turn_sign);
            }

            win = win_check (cell);
            if (win) {printf ("Congratulations!\n %s won!", player2.player_name);}
        }
    turn++;
    }


}
