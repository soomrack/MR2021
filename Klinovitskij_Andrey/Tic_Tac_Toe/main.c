#include<stdio.h>
//#include<conio.h>
#include<stdlib.h>
//#include <windows.h>
//#include <string.h>
//#include <wingdi.h>
//#include <GL/gl.h>
//#include <GL/glut.h>

//                            PLEASE, USE .EXE

/*
 *     After a couple of hours of trying to add graphics and control with the
 * mouse, I decided to leave it for later. For a first step I'll make the usual
 * Tic Tac Toe with symbolic graphics :(
 *     Attempts to include graphics.h failed because it has sstream header
 * (only for c++), attempts with OpenGL failed because of GL/glut.h (here I
 * was already lazy)
 *     There were also attempts to do with windows.h, but I didn't really like
 * the Brush work
 *     Somehow, so the most common program is made:
 *                                              --KAD1605 (Sorry for my English)
 *
 *    Useful links:
 *    Colored terminal (for color text): https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
 *    Portable character set (for \a \t): https://en.wikipedia.org/wiki/Portable_character_set
 *    ?: (for C): https://en.wikipedia.org/wiki/%3F:#C
 *    Elvis operator (addition to previous link): https://en.wikipedia.org/wiki/Elvis_operator
 */


char square[10] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'}; //Field array. X or 0

void Field_3x3() {  //Create a tic-tac-toe field  \x1B - color
    system("cls"); //Clearing screen
    printf("\n\n\n\n\n\n\n");
    printf("\x1B[22;1;92;40m\t\t\t\t\t Tic Tac Toe \x1B[0;37;40m\n\n");
    printf("\x1B[22;1;96;40m\t\t\t\t\t   X VS 0   \x1B[0;37;40m\n\n\n");
    printf("\t\t\t\t\t    |   |    \n");
    printf("\t\t\t\t\t \x1B[22;30;47m   |   |   \x1B[0;37;40m \n");
    printf("\t\t\t\t\t \x1B[22;30;47m %c | %c | %c \x1B[0;37;40m \n", square[6], square[7], square[8]);
    printf("\t\t\t\t\t_\x1B[22;30;47m___|___|___\x1B[0;37;40m_\n");
    printf("\t\t\t\t\t \x1B[22;30;47m   |   |   \x1B[0;37;40m \n");
    printf("\t\t\t\t\t \x1B[22;30;47m %c | %c | %c \x1B[0;37;40m \n", square[3], square[4], square[5]);
    printf("\t\t\t\t\t_\x1B[22;30;47m___|___|___\x1B[0;37;40m_\n");
    printf("\t\t\t\t\t \x1B[22;30;47m   |   |   \x1B[0;37;40m \n");
    printf("\t\t\t\t\t \x1B[22;30;47m %c | %c | %c \x1B[0;37;40m \n", square[0], square[1], square[2]);
    printf("\t\t\t\t\t \x1B[22;30;47m   |   |   \x1B[0;37;40m \n");
    printf("\t\t\t\t\t    |   |    \n");
}

int Check_Win() {   // All possible situations to win
    // return 1 = Win
    // return 2 = Draw
    // return 0 = Game in progress
    if (square[0] == square[1] && square[1] == square[2])
        return 1;
    else if (square[3] == square[4] && square[4] == square[5])
        return 1;
    else if (square[6] == square[7] && square[7] == square[8])
        return 1;
    else if (square[0] == square[3] && square[3] == square[6])
        return 1;
    else if (square[1] == square[4] && square[4] == square[7])
        return 1;
    else if (square[2] == square[5] && square[5] == square[8])
        return 1;
    else if (square[0] == square[4] && square[4] == square[8])
        return 1;
    else if (square[2] == square[4] && square[4] == square[6])
        return 1;
    else if (square[0] != '1' && square[1] != '2' && square[2] != '3' && square[3] != '4' && square[4] != '5' &&
             square[5] != '6' && square[6] != '7' && square[7] != '8' && square[8] != '9')
        return 0;
    else
        return 2;
}

void Foolproof(int Position, char Mark, int *player, int code) { //Foolproof for mistakes
    if (Position == 1 && square[0] == '1')
        square[0] = Mark;
    else if (Position == 2 && square[1] == '2')
        square[1] = Mark;
    else if (Position == 3 && square[2] == '3')
        square[2] = Mark;
    else if (Position == 4 && square[3] == '4')
        square[3] = Mark;
    else if (Position == 5 && square[4] == '5')
        square[4] = Mark;
    else if (Position == 6 && square[5] == '6')
        square[5] = Mark;
    else if (Position == 7 && square[6] == '7')
        square[6] = Mark;
    else if (Position == 8 && square[7] == '8')
        square[7] = Mark;
    else if (Position == 9 && square[8] == '9')
        square[8] = Mark;
    else {
        //Motivational message!
        if ((*player) % 2 == 1)
            printf("\n\n\t\tI believe in you! You will be able to click on the \x1B[1;31;46mCORRECT\x1B[0;37;40m button.\n\t\t\t\t Try again. Good luck!\n\n\t\t\t");
        (*player)--; //Back on our turn
    }
}

int User(int code) //User interface
{
    int player = 1, Win, Position; //Player num, Win/Draw/GiP, Position X or 0
    char Mark; //X or 0
    system("cls");      //Clearing screen
    do {
        Field_3x3();             //Create a tic-tac-toe field
        player = (player % 2) ? 1 : 2;   //Check useful links (?:) or Elvis operator
        printf("\n\n\t\t\t\tPlayer %d \n\t\t\t\tEnter position on field: ", player);
        if (code == 2 && player == 2) {
            Position = rand() % 10;
        } else
            scanf("%d", &Position);   //Input position
        if (player % 2 == 1) {
            Mark = 'X';
        } else {
            Mark = '0';
        }
        Foolproof(Position, Mark, &player, code);//Foolproof
        player++;       //Next turn
        Win = Check_Win();//Checking win
    } while (Win == 2);    //While game in progress
    Field_3x3();        //Create a tic-tac-toe field
    if (Win == 1) {         //If someone won
        printf("\n\n\t\t\t\t\t\a\x1B[1;92;40mPlayer %d win\x1B[0;37;40m\n\t\t\t",
               --player); // --player for right winner \a for sound
        return 0;
    } else {               //If nobody won
        printf("\n\n\t\t\t\t\t\aDraw!\n\t\t\t");
        return 0;
    }
}

void Menu() { //Game menu
    int key; //press key
    for (int i = 0; i <= 8; i++) {
        square[i] = 49 + i; //Clearing field. P.S. ASCII '0' = 48 (!)
    }
    system("cls");//Clearing screen
    printf("1 - Play\n");
    printf("2 - Game with bot\n");
    printf("3 - Exit\n");
    printf("\nChoose gamemode: ");
    scanf("%d", &key); //Input choose
    if (key == 1) {         //If 1 then start game
        User(1);
    } else if (key == 2) {    //If 2 then close game
        User(2);
    } else if (key == 3) {    //If 2 then close game
        exit(0);
    } else {       //If missclick
        //Motivational message!
        printf("\n\n\t\tI believe in you! You will be able to click on the \x1B[1;31;46mCORRECT\x1B[0;37;40m button.\n\t\t\t\t Try again. Good luck!\n\n\t\t\t"); // \x1B - color. Check https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
        system("pause");
        Menu(); //Return to menu
    }
}

int main() {
    while (1) {                     //Infinity loop
        Menu();                     //Start menu
        system("pause");  //Wait for key
    }
}