

#include "Bot.h"
#include "stdbool.h"
#include "time.h"
#include "stdlib.h"
#include "stdio.h"
#include "gtk/gtk.h"

bool SwitchMove =  false;
bool IsCellVacant[9];

void rand_move(char p1, char p2) {
    int RandomCell = 0;
    for (int e = 0; e <= 8; e++) {
        if ((field[e] == p1) || (field[e] == p2)) {
            IsCellVacant[e] = false;
        }
        else {
            IsCellVacant[e] = true;
        }
    }
    do {
        srand(time(NULL));
        RandomCell = rand() % 9;
        if (IsCellVacant[RandomCell] == true) {
            field[RandomCell] = p1;
            pos = RandomCell;
            SwitchMove = true;
        }
    } while (SwitchMove == false);
}

void bot_easy(char p1, char p2) {
    SwitchMove=false;
    rand_move(p1,p2);
    snprintf(buffer_cell_value, sizeof(buffer_cell_value), "%c", p1);
}

