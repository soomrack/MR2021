#include <stdio.h>

char FIELD[3][3];
char TURN;
char HUMAN;
struct cell{
    int x;
    int y;
};
struct cell xod;

void Print_Field(){
    printf(" %c | %c | %c \n",FIELD[0][0],FIELD[0][1],FIELD[0][2]);
    printf("-----------\n");
    printf(" %c | %c | %c \n",FIELD[1][0],FIELD[1][1],FIELD[1][2]);
    printf("-----------\n");
    printf(" %c | %c | %c \n",FIELD[2][0],FIELD[2][1],FIELD[2][2]);
}

void Init(){
    printf("please choose your side X or O\n");
    scanf("%c", &HUMAN);
    while (!((HUMAN == 'X')||(HUMAN == 'O'))){
        printf("please choose correct side X or O\n");
        scanf("%c", &HUMAN);
    }
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

void Make_Turn_Human(){
    printf("%c please make your turn\n", TURN);
    scanf("%d %d", &xod.y, &xod.x);
    while ((FIELD[xod.x-1][xod.y-1] != ' ')||(xod.x > 4)||(xod.y > 4)||
           (xod.x < 0)||(xod.y < 0)) {
        Print_Field();
        printf("%c please make correct turn\n", TURN);
        scanf("%d %d", &xod.y, &xod.x);
    }
    FIELD[xod.x-1][xod.y-1] = TURN;
};

void Make_Turn_Robot(){
    int max = 0;
    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){
            if (FIELD[i][j]==' '){
                int r_count_x = 0;
                int r_count_y = 0;
                int r_count_d1 = 0;
                int r_count_d2 = 0;
                int h_count_x = 0;
                int h_count_y = 0;
                int h_count_d1 = 0;
                int h_count_d2 = 0;
                for (int k=0; k<3; k++) {
                    if (FIELD[k][j] == TURN) {
                        r_count_x++;
                    }
                    if (FIELD[i][k] == TURN) {
                        r_count_y++;
                    }
                    if ((i == j)&&(FIELD[k][k] == TURN)){
                        r_count_d1++;
                    }
                    if ((i + j == 2)&&(FIELD[k][2-k] == TURN)){
                        r_count_d2++;
                    }
                    if (FIELD[k][j] == HUMAN) {
                        h_count_x++;
                    }
                    if (FIELD[i][k] == HUMAN) {
                        h_count_y++;
                    }
                    if ((i == j)&&(FIELD[k][k] == HUMAN)){
                        h_count_d1++;
                    }
                    if ((i + j == 2)&&(FIELD[k][2-k] == HUMAN)){
                        h_count_d2++;
                    }
                }
                if ((r_count_x == 2)||(r_count_y == 2)||(r_count_d1 == 2)||(r_count_d2 == 2)){
                    max = 1000;
                    xod.x = i;
                    xod.y = j;
                }
                else {
                    if ((h_count_x == 2) || (h_count_y == 2) || (h_count_d1 == 2) || (h_count_d2 == 2)) {
                        max = 500;
                        xod.x = i;
                        xod.y = j;
                    }
                    else {
                        int rating = 0;
                        if (r_count_x + h_count_x == 0) {
                            rating += 5;
                        }
                        if (r_count_y + h_count_y == 0) {
                            rating += 5;
                        }
                        if ((i == j) && (r_count_d1 + h_count_d1 == 0)) {
                            rating += 10;
                        }
                        if ((i + j == 2) && (r_count_d2 + h_count_d2 == 0)) {
                            rating += 10;
                        }
                        rating += 3 * (r_count_x + r_count_y + r_count_d1 + r_count_d2);
                        rating -= 5 * (h_count_x + h_count_y + h_count_d1 + h_count_d2);
                        if (rating > max) {
                            max = rating;
                            xod.x = i;
                            xod.y = j;
                        }
                    }
                }
            }
        }
    }
    FIELD[xod.x][xod.y] = TURN;
    printf("Robot turn: %d %d\n", xod.y+1, xod.x+1);
}

int main() {
    Init();
    for (int i=0; i<9; i++){
        if (TURN == HUMAN){
            Print_Field();
            Make_Turn_Human();
        }
        else{
            Make_Turn_Robot();
        }

        if (Check_Win()){
            Print_Field();
            if (TURN == HUMAN){
                printf("WOW --YOU WIN-- WOW");
                break;
            }
            else{
                printf("WOW --ROBOT WIN-- WOW");
                break;
            }
        }
        else{
            if (i == 8){
                Print_Field();
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