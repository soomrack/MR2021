#include "stdio.h"
#include <stdlib.h>

char square[10] = {'0','1','2','3','4','5','6','7','8','9'};

struct Player{
    char sign;
    int num;
};

struct Player Player_AI = {'X', 1};
struct Player Player2 = {'O',2};

int move = 1,player = 1,i;
char choice;


int checkwin();
void board();

int main()
{
    int  player;
    char mark;
    srand ( time(NULL) );
    int AI_num = 5;
    do
    {
        board();
        move = (move%2) ? 1 : 2;

        switch (move) {
            case 1:
                mark = Player_AI.sign;
                player = Player_AI.num;

                AI_num = rand() % 10;

                while(square[AI_num] == Player2.sign) {
                        AI_num++;
                    if (AI_num > 9)
                        AI_num = 0;
                }
                choice =  rand() % 10;
                break;
            case 2:
                mark = Player2.sign;
                player = Player2.num;

                printf("Player %c %s", mark, ", enter a number:  \n");

                scanf("%d ", &choice);
                break;
        }

        square[choice] = mark;

        move++;

        i=checkwin();

    } while(i==-1);


    if(i==1)

        printf("==>\aPlayer ", --player, " win ");
    else
        printf("==>\aGame draw");


    return 0;
}

int checkwin()
{
    if (square[1] == square[2] && square[2] == square[3])

        return 1;
    else if (square[4] == square[5] && square[5] == square[6])

        return 1;
    else if (square[7] == square[8] && square[8] == square[9])

        return 1;
    else if (square[1] == square[4] && square[4] == square[7])

        return 1;
    else if (square[2] == square[5] && square[5] == square[8])

        return 1;
    else if (square[3] == square[6] && square[6] == square[9])

        return 1;
    else if (square[1] == square[5] && square[5] == square[9])

        return 1;
    else if (square[3] == square[5] && square[5] == square[7])

        return 1;
    else if (square[1] != '1' && square[2] != '2' && square[3] != '3'
             && square[4] != '4' && square[5] != '5' && square[6] != '6'
             && square[7] != '7' && square[8] != '8' && square[9] != '9')

        return 0;
    else
        return -1;
}


void board()
{
    printf("\n\n\tTic Tac Toe\n\n");

    printf("Player 1 (X)  -  Player 2 (O)\n");


    printf("      |     |     \n");
    printf( "  %c %s %c %s %c %s" , square[1] , "  | " , square[2] , " |  " , square[3], "\n");

    printf(" _____|_____|_____\n" );
    printf("      |     |     \n" );

    printf("  %c %s %c %s %c %s" , square[4] , "  |  " , square[5] , "|  " , square[6], "\n");

    printf(" _____|_____|_____\n");
    printf( "      |     |    \n ");

    printf( "  %c %s %c %s %c %s" , square[7] , " |  " , square[8] , "|  " , square[9], "\n");

    printf("      |     |     \n" );
}

