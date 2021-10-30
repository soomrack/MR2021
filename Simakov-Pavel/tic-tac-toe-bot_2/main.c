#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "library.h"

bool x_move = true; // determines whose turn it is now, t - X, f - O
char field [9] = {'0', '1', '2', '3', '4', '5', '6', '7', '8'};// initialize field of game
size_of_field = sizeof(field)/sizeof(field[0]);

//void fill_in_field()
//{
//    for (int i = 48; i < size_of_field + 48; i++)
  //  {
  //      field[i] = i+1;
 //   }
//}

void move() // input of crosses and noughts
{
    printf("enter the position\n");
    int position;
    int bot_position;
    if (x_move)
    {
        scanf("%d", &position);
        if (field[position] == 'X' || field[position] == 'O') {
            printf("Wrong number, please enter again\n");
            move();
        }
        field[position] = 'X';
    }
    else
    {
        bot_position = bot_move();
        while(field[bot_position] == 'X' || field[bot_position] == 'O')
        {
            bot_position = bot_move();
        }
        field[bot_position] = 'O';
    }
    x_move = !x_move;
}

char check_win() // checking for winner
{
    bool win = true;
    int sqrt_of_field = (int)sqrt(size_of_field);
    char being_compared;
    if (x_move)
    {
        being_compared = 'X';
    }
    else
    {
        being_compared = 'O';
    }

    for (int i = 0; i < size_of_field; i+=sqrt_of_field) // checking strings
    {
        for (int k = 0; k < sqrt_of_field; k++)
        {
            if (field[i+k] != being_compared)
            {
                win = false;
            }
        }
        if (win) {return being_compared;}
        else {win = true;}
    }

    for (int i = 0; i < sqrt_of_field; i++) // checking columnes
    {
        for (int k = 0; k < sqrt_of_field; k++)
        {
            if (field[i + sqrt_of_field*k] != being_compared)
            {
                win = false;
            }
        }
        if (win) {return being_compared;}
        else {win = true;}
    }

    for (int i = 0; i < 1; i++) //1 diagonal check from left-up to right-down
    {
        for (int k = 0; k < sqrt_of_field; k++)
        {
            if (field[i + sqrt_of_field*k + 1] != being_compared)
            {
                win = false;
            }
        }
        if (win) {return being_compared;}
        else {win = true;}
    }

    for (int i = sqrt_of_field - 1; i < sqrt_of_field; i++) //2 diagonal check from right-up to left-down
    {
        for (int k = 0; k < sqrt_of_field; k++)
        {
            if (field[i + sqrt_of_field*k - 1] != being_compared)
            {
                win = false;
            }
        }
        if (win) {return being_compared;}
        else {win = true;}
    }

    return 'F';
}

void output()
{
    for (int i = 0; i < 3; i++)
    {
        printf("  %c |",field[i*3]);
        printf("  %c |",field[i*3+1]);
        printf("  %c |\n",field[i*3+2]);
        printf("_______________\n");
    }
}

int main() {
    for (int i = 0; i < size_of_field; i++)
    {
        output();
        move();
        switch (check_win())
        {
            case 'X':
            {
                output();
                printf("x wins!");
                return 0;
            }
            case 'O':
            {
                output();
                printf("O wins");
                return 0;
            }
            case 'F':
            {}
        }
    }
    printf("draw");
    return 0;
}
