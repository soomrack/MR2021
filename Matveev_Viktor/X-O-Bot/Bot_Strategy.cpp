// Bot_Strategy.cpp: определяет точку входа для приложения.
//

#include "Bot_Strategy.h"


bool toggle = false;
char Sup_arr[9] = { '1','2','3','4','5','6','7','8','9' };
int Checking_arr[8];
int N;
char traveler;

void rand_move(char ind1, char ind2)
{
    for (int i = 0; i <= 8; i++)
    {
        srand(time(NULL));
        N = rand() % 9;
        Sup_arr[N - 1] = ind1;
        traveler = Sup_arr[N - 1];
    }


}

void something_smart(char ind_arr[9], char ind1, char ind2, char ind3)
{
    for (int i = 0; i <3; i++)
    {
        //Check for vertical
        if ((((ind_arr[i] == ind_arr[i + 3*1])&& (ind_arr[i + 3 * 1] == ind2)) && ((ind_arr[i+3*2]!=ind2) && (ind_arr[i + 3 * 2] != ind1)))&&(toggle=false))
        {
            N = i + 3 * 2;
            ind_arr[N] = ind3;
            traveler = ind_arr[N];
            toggle = true;
        }

        if ((((ind_arr[i] == ind_arr[i + 3 * 2])&& (ind_arr[i + 3 * 2] == ind2)) && ((ind_arr[i + 3 * 1] != ind2) && (ind_arr[i + 3 * 1] != ind1)))&&(toggle=false))
        {
            N = i + 3 * 1;
            ind_arr[N] = ind3;
            traveler = ind_arr[N];
            toggle = true;
        }

        if ((((ind_arr[i + 3 * 1] == ind_arr[i + 3 * 2])&& (ind_arr[i + 3 * 2] == ind2)) && ((ind_arr[i] != ind2) && (ind_arr[i] != ind1)))&&(toggle=false))
        {
            N = i;
            ind_arr[N] = ind3;
            traveler = ind_arr[N];
            toggle = true;
        }

        //Check for horisontal
        if ((((ind_arr[3 * i] == ind_arr[3 * i + 1])&& (ind_arr[3 * i + 1] == ind2)) && ((ind_arr[3 * i + 2] != ind2) && (ind_arr[3 * i + 2] != ind1)))&&(toggle=false))
        {
            N = 3 * i + 2;
            ind_arr[N] = ind3;
            traveler = ind_arr[N];
            toggle = true;
        }

        if ((((ind_arr[3 * i] == ind_arr[3 * i + 2])&& (ind_arr[3 * i + 2] == ind2)) && ((ind_arr[3 * i + 1] != ind2) && (ind_arr[3 * i + 1] != ind1)))&&(toggle=false))
        {
            N = 3 * i + 1;
            ind_arr[N] = ind3;
            traveler = ind_arr[N];
            toggle = true;
        }

        if ((((ind_arr[3 * i + 1] == ind_arr[3 * i + 2])&& (ind_arr[3 * i + 2] == ind2)) && ((ind_arr[3 * i] != ind2) && (ind_arr[3 * i] != ind1)))&&(toggle=false))
        {
            N = 3 * i;
            ind_arr[N] = ind3;
            traveler = ind_arr[N];
            toggle = true;
        }

    }
    
    // Check for main diagonal
    if ((((ind_arr[0] == ind_arr[4])&& (ind_arr[4] == ind2)) && ((ind_arr[8] != ind2) && (ind_arr[8] != ind1)))&&(toggle=false))
    {
        N = 8;
        ind_arr[N] = ind3;
        traveler = ind_arr[N];
        toggle = true;
    }

    else if ((((ind_arr[0] == ind_arr[8])&& (ind_arr[8] == ind2)) && ((ind_arr[4] != ind2) && (ind_arr[4] != ind1)))&&(toggle=false))
    {
        N = 4;
        ind_arr[N] = ind3;
        traveler = ind_arr[N];
        toggle = true;
    }

    if ((((ind_arr[4] == ind_arr[8])&& (ind_arr[8] == ind2)) && ((ind_arr[0] != ind2) && (ind_arr[0] != ind1)))&&(toggle=false))
    {
        N = 0;
        ind_arr[0] = ind3;
        traveler = ind_arr[N];
        toggle = true;
    }

    // Check for sub diagonal
    if ((((ind_arr[2] == ind_arr[4])&& (ind_arr[4] == ind2)) && ((ind_arr[6] != ind2) && (ind_arr[6] != ind1)))&&(toggle=false))
    {
        N = 6;
        ind_arr[6] = ind3;
        traveler = ind_arr[N];
        toggle = true;
    }

    if ((((ind_arr[2] == ind_arr[6])&& (ind_arr[6] == ind2)) && ((ind_arr[4] != ind2) && (ind_arr[4] != ind1)))&&(toggle=false))
    {
        N = 4;
        ind_arr[4] = ind3;
        traveler = ind_arr[N];
        toggle = true;
    }

    if ((((ind_arr[4] == ind_arr[6])&& (ind_arr[6] == ind2)) && ((ind_arr[2] != ind2) && (ind_arr[2] != ind1)))&&(toggle=false))
    {
        N = 2;
        ind_arr[2] = ind3;
        traveler = ind_arr[N];
        toggle = true;
    }
    if (toggle = false)
    {
        rand_move(ind1, ind2);
    }
}

void bot_easy(char ind1, char ind2)
{
    toggle = false;
    printf("Bot's move!\n");
    rand_move(ind1, ind2);
}

void bot_hard(char ind1, char ind2)
{
    toggle = false;
    printf("Bot's move!\n");
    rand_move(ind1, ind2);
}
