#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

char FIELD[3][3];
char TURN;
struct cell{
    int x;
    int y;
};
struct cell xod;

void Print_Field(){
    system("clear");
    printf(" %c | %c | %c \n",FIELD[0][0],FIELD[0][1],FIELD[0][2]);
    printf("-----------\n");
    printf(" %c | %c | %c \n",FIELD[1][0],FIELD[1][1],FIELD[1][2]);
    printf("-----------\n");
    printf(" %c | %c | %c \n",FIELD[2][0],FIELD[2][1],FIELD[2][2]);
}

void Init(){
    system("clear");
    TURN = 'X';
    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){
            FIELD[i][j]=' ';
        }
    }
}

int Check_Win(){
    int flag = 0;
    for (int i=0; i<3; i++){
        if ((FIELD[i][0] == FIELD[i][1])&&(FIELD[i][1] == FIELD[i][2])&&(FIELD[i][0]!=' ')){flag = 1;}
        if ((FIELD[0][i] == FIELD[1][i])&&(FIELD[1][i] == FIELD[2][i])&&(FIELD[0][i]!=' ')){flag = 1;}
    }
    if ((FIELD[0][0] == FIELD[1][1])&&(FIELD[1][1] == FIELD[2][2])&&(FIELD[1][1]!=' ')){flag = 1;}
    if ((FIELD[2][0] == FIELD[1][1])&&(FIELD[1][1] == FIELD[0][2])&&(FIELD[1][1]!=' ')){flag = 1;}
    return flag;
}

void Make_Turn(){
    Print_Field();
    printf("%c please make your turn\n", TURN);
    scanf("%d %d", &xod.y, &xod.x);
    while ((FIELD[xod.x-1][xod.y-1] != ' ')||(xod.x > 4)||(xod.y > 4)||
                                             (xod.x < 0)||(xod.y < 0)) {
        Print_Field();
        printf("%c please make correct turn\n", TURN);
        scanf("%d %d", &xod.y, &xod.x);
    }
    FIELD[xod.x-1][xod.y-1] = TURN;
}

int main() {
    Init();
    for (int i=0; i<9; i++){
        Make_Turn();
        if (Check_Win()){
            printf("WOW %c-Player win WOW", TURN);
            break;
        }
        else{
            if (i == 8){
                printf("DRAW --GAME OVER-- DRAW");
            }
        }
        if (TURN == 'X'){
            TURN = 'O';
        }
        else{
            TURN = 'X';
        }
    }
}
