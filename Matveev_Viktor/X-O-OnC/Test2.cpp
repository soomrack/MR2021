// Test2.cpp: определяет точку входа для приложения.
//

#include "Test2.h"

using namespace std;

char arr[9] = { '1','2','3','4','5','6','7','8','9'};
int x;
int var=0;

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

void set_X_position()
{
    printf("Input X position\n");
    scanf("%d", &x);

    if ((x == 1) || (x == 2) || (x == 3) || (x == 4) || (x == 5) || (x == 6) || (x == 7) || (x == 8) || (x == 9))
    {
        Check_Intruder('X','O');
    }
    else 
    { 
        printf("There's no field for your position\n"); //Check position
    }

}

void set_O_position() {
    printf("Input O position\n");
    scanf("%d", &x);

    if ((x == 1) || (x == 2) || (x == 3) || (x == 4) || (x == 5) || (x == 6) || (x == 7) || (x == 8) || (x == 9))
    {
        Check_Intruder('O', 'X');
    }
    else
    { 
        printf("There's no field for your position\n"); //Check position
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

void Game()
{
    for (int k = 1; k < 18; k++)
    {
        if (k % 2 != 0)
        {
            set_X_position();
            set_field();
        }
        else
        {
            set_O_position();
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
    set_field();
    Game(); 
  }
