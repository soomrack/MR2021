// X_O_Improved.cpp: определяет точку входа для приложения.
//

#include "X_O_Improved.h"
#include "Bot_Strategy.h"

using namespace std;

char arr[9] = { '1','2','3','4','5','6','7','8','9'};
int x;
int var = 0;
int players_count;
int Turn_selector;
int Difficulty_mode;
extern int N;
extern char traveler; //This varible will transport bot's decision from library
extern char Sup_arr[9];

void set_field() {
    for (int i = 0; i <= 2; i++) {
        for (int j = 0; j <= 2; j++) {
            var = i * 3 + j; //gives num for points
            printf("%c  ", arr[var]);
        }
        printf("\n");
    }
}

void Check_Intruder(char ind1, char ind2)
{
    if (arr[x - 1] == ind1 || arr[x - 1] == ind2)
    {
        printf("You can't do this step\n"); // Check the intruder
    }
    else
    {
        arr[x - 1] = ind1;
    }
}

bool Win() {
    for (int i = 0; i <= 2; i++) {
        if ((arr[3 * i] == arr[3 * i + 1] && arr[3 * i + 1] == arr[3 * i + 2]) ||
            (arr[i] == arr[i + 3] && arr[i + 3] == arr[i + 3 * 2]) ||
            (arr[0] == arr[4] && arr[4] == arr[8]) || (arr[6] == arr[4] && arr[4] == arr[2])) // Check win combinations
        {
            printf("You Win!\n");
            return true;
        }
    }
}

bool Fields_end() {
    int counter = 0;
    for (int i = 0; i <= 8; i++) {
        if (arr[i] == 'X' || arr[i] == 'O') {
            counter++; //Shows number of filled cells
        }
    }
    if (counter == 9) {
        return true;
    }
    else {
        return false;
    }
}

void Human_player(char ind1, char ind2)
{
    printf("Input %c position\n", ind1);
    scanf("%d", &x);

    if ((x == 1) || (x == 2) || (x == 3) || (x == 4) || (x == 5) || (x == 6) || (x == 7) || (x == 8) || (x == 9))
    {
        Check_Intruder(ind1, ind2);
    }
    else
    {
        printf("There's no field for your position\n"); //Check position
    }

}

void (*Player1_move) (char ind1, char ind2);
void (*Player2_move) (char ind1, char ind2);

void Settings()
{
    printf("Welcome to my Tik Tak game\n" 
        "Do u want to play with your friend or with computer?\n"
        "1 - There is two of us\n"
        "2 - Wow, let's test your program\n");
    scanf("%d", &players_count);
    switch (players_count)
    {
        case 1:
            Player1_move = Human_player;
            Player2_move = Human_player;
            break;
        case 2:
            printf("Weeeel, would u like move firts or second?\n"
                "1 - I'm always first!!!\n"
                "2 - Lol, i'll beat your bot easily even from the second position\n");
            scanf("%d", &Turn_selector);
                switch (Turn_selector)
                {   
                    case 1:
                        Player1_move = Human_player;
                        printf("And what kind of difficulty would you pick?\n"
                            "1 - Easy, i have more important things to think of\n"
                            "2 - Not so easy... Finally a worthy opponent - our battle will be legendary\n");
                        scanf("%d", &Difficulty_mode);
                        switch (Difficulty_mode)
                        {
                            case 1:
                                Player2_move = bot_easy;
                                break;
                            case 2:
                                Player2_move = bot_hard;
                                break;
                            default: printf("You've broke my programm. Can u chose number next time...\n ");
                        }
                        break;
                    case 2:
                        Player2_move = Human_player;
                        printf("And what kind of difficulty would you pick?\n"
                            "1 - Easy, i have more important things to think of\n"
                            "2 - Not so easy... Finally a worthy opponent - our battle will be legendary\n");
                        scanf("%d", &Difficulty_mode);
                        switch (Difficulty_mode)
                        {
                        case 1:
                            Player1_move = bot_easy;
                            break;
                        case 2:
                            Player1_move = bot_hard;
                            break;
                        default: printf("You've broke my programm. Can u chose number next time... ");
                        }
                        break;
                default: printf("You've broke my programm. Can u chose number next time... ");
                }
                break;
    default: printf("You've broke my programm. Can u chose number next time... ");
    }
}

void Game()
{
    
    for (int k = 1; k < 18; k++)
    {
        if (k % 2 != 0)
        {
            Player1_move('X', 'O');
            if ((Player1_move == bot_easy) || (Player1_move == bot_hard))
            {
                x = N+1;
                Check_Intruder(traveler, 'O');
            }

            set_field();
        }
        else
        {
            Player2_move('O', 'X');
            if ((Player2_move == bot_easy) || (Player2_move == bot_hard))
            {
                x = N+1;
                Check_Intruder(traveler, 'X');
            }
            set_field();
        }
        if (Win() == true)
        {
            if (k % 2 != 0)
            {
                printf("Game over! X wins\n");
                break;
            }
            else
            {
                printf("Game over! O wins\n");
                break;
            }
        }
        if (Fields_end() == true)
        {
            printf("Game over! Noone wins, you have no free spots\n");

        }
    }
}

int main()
{
    Settings();
    set_field();
    Game();
}
