#include "BotXO.h"
#include "stdbool.h"
#include "time.h"
#include "stdlib.h"
#include "stdio.h"

bool SwitchMove =  false;
char field[9];
bool IsCellVacant[9];

// выбор случайной свободной клетки
// p1 - записываемый символ
// p2 - другой символ
void rand_move(char p1, char p2) {
    int RandomCell = 0;
    for (int e = 0; e <= 8; e++) {
        if ((field[e] == p1) || (field[e] == p2)) {
            IsCellVacant[e] = false;
        }
        else {
            IsCellVacant[e] = true;
        }
        printf("%d\n", IsCellVacant[e]);
    }
    do {
        srand(time(NULL));
        RandomCell = rand() % 9;
        if (IsCellVacant[RandomCell] == true) {
            field[RandomCell] = p1;
            SwitchMove = true;
        }
    } while (SwitchMove == false);
    }

// алгоритм защиты
// p1 - символ комбинации, подозрительной на выйгрышную (Х/О)
// p2 - другой символ (Х/О)
// p3 - символ дополняющий строку до конца (защита - p3=p2; атака p3=p1)
void defend_attack(char p1, char p2, char p3) {
    for(int i=0; i<3; i++) {
        // проверка вертикальных строчек
        if ((((field[i]==field[i+6])&&(field[i]==p1))&&((field[i+3]!=p1)&&(field[i+3]!=p2)))&&(SwitchMove==false)) {
            field[i+3]=p3;
            SwitchMove=true;
        }
        if ((((field[i]==field[i+3])&&(field[i]==p1))&&((field[i+6]!=p1)&&(field[i+6]!=p2)))&&(SwitchMove==false)) {
            field[i+6]=p3;
            SwitchMove=true;
        }
        if ((((field[i+6]==field[i+3])&&(field[i+6]==p1))&&((field[i]!=p1)&&(field[i]!=p2)))&&(SwitchMove==false)) {
            field[i]=p3;
            SwitchMove=true;
        }
        // проверка горизонтальных строчек
        if ((((field[3*i]==field[3*i+2])&&(field[3*i]==p1))&&((field[3*i+1]!=p1)&&(field[3*i+1]!=p2)))&&(SwitchMove==false)) {
            field[3*i+1]=p3;
            SwitchMove=true;
        }
        if ((((field[3*i]==field[3*i+1])&&(field[3*i]==p1))&&((field[3*i+2]!=p1)&&(field[3*i+2]!=p2)))&&(SwitchMove==false)) {
            field[3*i+2] =p3;
            SwitchMove = true;
        }
        if ((((field[3*i+2]==field[3*i+1])&&(field[3*i+2]==p1))&&((field[3*i]!=p1)&&(field[3*i]!=p2)))&&(SwitchMove==false)) {
            field[3*i] = p3;
            SwitchMove = true;
        }
    }
    // проверка диагоналей
    if ((((field[0]==field[8])&&(field[0]==p1))&&((field[4]!=p1)&&(field[4]!=p2)))||
        ((((field[2]==field[6])&&(field[2]==p1))&&((field[4]!=p1)&&(field[4]!=p2)))&&(SwitchMove==false))){
        field[4]=p3;
        SwitchMove=true;
    }
    if ((((field[0]==field[4])&&(field[0]==p1))&&((field[8]!=p1)&&(field[8]!=p2)))&&(SwitchMove==false)){
        field[8]=p3;
        SwitchMove=true;
    }
    if ((((field[2]==field[4])&&(field[2]==p1))&&((field[6]!=p1)&&(field[6]!=p2)))&&(SwitchMove==false)){
        field[6]=p3;
        SwitchMove=true;
    }
    if ((((field[8]==field[4])&&(field[8]==p1))&&((field[0]!=p1)&&(field[0]!=p2)))&&(SwitchMove==false)){
        field[0]=p3;
        SwitchMove=true;
    }
    if ((((field[6]==field[4])&&(field[6]==p1))&&((field[2]!=p1)&&(field[2]!=p2)))&&(SwitchMove==false)){
        field[2]=p3;
        SwitchMove=true;
    }
}

// Легкий бот
// p1 - символ бота
void bot_easy(char p1, char p2) {
    SwitchMove=false;
    printf("Bot's move!\n");
    rand_move(p1,p2);
}

// Средний бот
// p1 - символ бота
// p2 - символ противника
void bot_medium(char p1, char p2) {
    SwitchMove=false;
    printf("Bot's move!\n");
    defend_attack(p2,p1,p1);
    if (SwitchMove==false) {
        rand_move(p1,p2);
    }
}

// Сложный бот
// p1 - символ бота
// p2 - символ противника
void bot_hard(char p1, char p2) {
    SwitchMove=false;
    printf("Bot's move!\n");
    defend_attack(p1,p2,p1);
    if (SwitchMove==false) {
        defend_attack(p2,p1,p1);
    }
    if (SwitchMove==false) {
        rand_move(p1,p2);
    }
}