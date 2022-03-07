#include "BotXO.h"
#include "stdbool.h"
#include "time.h"
#include "stdlib.h"
#include "stdio.h"
#include "gtk/gtk.h"

bool SwitchMove =  false;
bool IsCellVacant[9];

/* picking a random cell
 p1 - the character that is being written
 p2 - another character */
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

/* algorithm of attack (defence)
 p1 - character of combo, suspected to be won (Х/О)
 p2 - another character (Х/О)
 p3 - character that makes the string full filled (defence - p3=p2; attack p3=p1)*/
void defend_attack(char p1, char p2, char p3) {
    for(int i=0; i<3; i++) {
        /* check of colons */
        if ((((field[i]==field[i+6])&&(field[i]==p1))&&((field[i+3]!=p1)&&(field[i+3]!=p2)))&&(SwitchMove==false)) {
            field[i+3]=p3;
            pos = i + 3;
            SwitchMove=true;
        }
        if ((((field[i]==field[i+3])&&(field[i]==p1))&&((field[i+6]!=p1)&&(field[i+6]!=p2)))&&(SwitchMove==false)) {
            field[i+6]=p3;
            pos = i + 6;
            SwitchMove=true;
        }
        if ((((field[i+6]==field[i+3])&&(field[i+6]==p1))&&((field[i]!=p1)&&(field[i]!=p2)))&&(SwitchMove==false)) {
            field[i]=p3;
            pos = i;
            SwitchMove=true;
        }
        /* check of rows */
        if ((((field[3*i]==field[3*i+2])&&(field[3*i]==p1))&&((field[3*i+1]!=p1)&&(field[3*i+1]!=p2)))&&(SwitchMove==false)) {
            field[3*i+1]=p3;
            pos = 3*i+1;
            SwitchMove=true;
        }
        if ((((field[3*i]==field[3*i+1])&&(field[3*i]==p1))&&((field[3*i+2]!=p1)&&(field[3*i+2]!=p2)))&&(SwitchMove==false)) {
            field[3*i+2] =p3;
            pos = 3*i+2;
            SwitchMove = true;
        }
        if ((((field[3*i+2]==field[3*i+1])&&(field[3*i+2]==p1))&&((field[3*i]!=p1)&&(field[3*i]!=p2)))&&(SwitchMove==false)) {
            field[3*i] = p3;
            pos = 3*i;
            SwitchMove = true;
        }
    }
    /* check of diagonals */
    if ((((field[0]==field[8])&&(field[0]==p1))&&((field[4]!=p1)&&(field[4]!=p2)))||
        ((((field[2]==field[6])&&(field[2]==p1))&&((field[4]!=p1)&&(field[4]!=p2)))&&(SwitchMove==false))){
        field[4] = p3;
        pos = 4;
        SwitchMove=true;
    }
    if ((((field[0]==field[4])&&(field[0]==p1))&&((field[8]!=p1)&&(field[8]!=p2)))&&(SwitchMove==false)){
        field[8] = p3;
        pos = 8;
        SwitchMove=true;
    }
    if ((((field[2]==field[4])&&(field[2]==p1))&&((field[6]!=p1)&&(field[6]!=p2)))&&(SwitchMove==false)){
        field[6] = p3;
        pos = 6;
        SwitchMove=true;
    }
    if ((((field[8]==field[4])&&(field[8]==p1))&&((field[0]!=p1)&&(field[0]!=p2)))&&(SwitchMove==false)){
        field[0] = p3;
        pos = 0;
        SwitchMove=true;
    }
    if ((((field[6]==field[4])&&(field[6]==p1))&&((field[2]!=p1)&&(field[2]!=p2)))&&(SwitchMove==false)){
        field[2] = p3;
        pos = 2;
        SwitchMove=true;
    }
}

/* Easy bot
p1 - bot's character
p2 - opponent's character */
void bot_easy(char p1, char p2) {
    SwitchMove=false;
    rand_move(p1,p2);
    snprintf(buffer_cell_value, sizeof(buffer_cell_value), "%c", p1);
}

/* Medium bot
p1 - bot's character
p2 - opponent's character */
void bot_medium(char p1, char p2) {
    SwitchMove=false;
    defend_attack(p2,p1,p1);
    if (SwitchMove==false) {
        rand_move(p1,p2);
    }
    snprintf(buffer_cell_value, sizeof(buffer_cell_value), "%c", p1);
}

/* Hard bot
p1 - bot's character
p2 - opponent's character */
void bot_hard(char p1, char p2) {
    SwitchMove=false;
    defend_attack(p1,p2,p1);
    if (SwitchMove==false) {
        defend_attack(p2,p1,p1);
    }
    if (SwitchMove==false) {
        rand_move(p1,p2);
    }
    snprintf(buffer_cell_value, sizeof(buffer_cell_value), "%c", p1);
}