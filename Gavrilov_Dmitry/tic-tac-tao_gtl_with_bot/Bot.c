

#include "Bot.h"
#include "stdbool.h"
#include "time.h"
#include "stdlib.h"
#include "stdio.h"
#include "gtk/gtk.h"

bool switch_move =  false;
bool cell_free[9];

void rand_move(char p1, char p2) {
    int RandomCell = 0;
    srand(time(NULL));
    for (int i = 0; i <= 8; i++) {
        if ((field[i] == p1) || (field[i] == p2)) {
            cell_free[i] = false;
        }
        else {
            cell_free[i] = true;
        }
    }
    do {
        RandomCell = rand() % 9;
        if (cell_free[RandomCell] == true) {
            field[RandomCell] = p1;
            pos = RandomCell;
            switch_move = true;
        }
    } while (switch_move == false);
}

void bot_easy(char p1, char p2) {
    switch_move=false;
    rand_move(p1,p2);
    snprintf(buffer_cell_value, sizeof(buffer_cell_value), "%c", p1);
}

