#include <stdio.h>

char name1[20], name2[20];
int a[3][3];
int result=0;
void Introduction(){
    printf("Tic-tac-toe\n");
    printf("Enter the name of the player who goes first\n");
    scanf("%s",name1);
    printf("Enter the name of the player who goes second\n");
    scanf("%s",name2);
    printf("The player %s goes first with using x\nThe player %s goes second with using 0\n", name1, name2);
    printf("Manual: Enter row and column number without spaces to select a field\n");
}

void Canvas(){
    printf("  1 2 3");
    for (int i = 1; i <= 3 ; ++i) {
        printf("\n%d", i);
        for (int j = 1; j <= 3 ; ++j) {
            if ( a[i][j] == 1){
                printf(" X");
            }else {
                if (a[i][j] == 2) {
                    printf(" 0");
                } else {
                    printf("  ");}
            }

        }

    }
    printf("\n");

}
void Who_is_the_winner(int g){
    if ( g == 1){
        printf("Winner is %s", name1);
        result = 1;
    }
    if ( g == 8){
        printf("Winner is %s", name2);
        result = 1;
    }

}

void determining_the_winner(){
    int sum;
    for (int i = 1 ; i <= 3 ; ++i) {
        sum = a[i][1] * a[i][2] * a[i][3];
        Who_is_the_winner(sum);

    }
    for (int j = 1 ; j <= 3 ; ++j) {
        sum = a[1][j] * a[2][j] * a[3][j];
        Who_is_the_winner(sum);
    }
    sum = a[1][1] * a[2][2] * a[3][3];
    Who_is_the_winner(sum);
    sum = a[1][3] * a[2][2] * a[3][1];
    Who_is_the_winner(sum);

}
void Purging(){
    for (int i = 1; i <= 3 ; ++i) {
        for (int j = 1; j <= 3 ; ++j) {
             a[i][j] = 0;
        }

    }
}
void Restart(){
    printf("\nGame was restarted\n");
    Introduction();
    Purging();
    Canvas();
}

int Safety(int c){
    if (c == 0 || c == 1 || c == 2 ||c == 3 ){
        return (0);
    } else {
        printf("An invalid value was entered. Try again!\n");
        return (1);
    }

}
int Avoidance_of_repetition(int m){
    if (m != 0){
        printf("This cell was previously involved. Try again! \n");
        return(1);
    } else{
        return (0);
    }

}

void Game_process(){
    int row = 0 , column = 0 ;
    for (int i = 1; i <= 9; ++i) {
        if ( i % 2 != 0){
            printf("Move %d. %s's turn\n",i,name1);
        }
        if ( i % 2 == 0){
            printf("Move %d. %s's turn\n",i,name2);
        }
        printf("Enter a number of column\n");
        scanf("%d", &row);
        printf("Enter a number of row\n");
        scanf("%d", &column);
        if ( Safety(row) == 1 || Safety(column) == 1 || Avoidance_of_repetition(a[column][row])== 1){
            row = 0 ;
            column = 0 ;
            --i;
        } else {
            if (i % 2 != 0) {
                a[column][row] = 1;
            }
            if (i % 2 == 0) {
                a[column][row] = 2;
            }
            Canvas();
            determining_the_winner();
            if (result == 1) {
                Restart();
                result =0;
                i = 0;
            }else if (i == 9 && result == 0 ){
                printf("Draw! Game will be restarted");
                Restart();
                i = 0;
            }
        }


    }
}

int main() {
    Introduction();
    Canvas();
    Game_process();
}
