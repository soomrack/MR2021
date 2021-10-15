#include "BotXO.h"
#include "stdbool.h"
#include "time.h"
#include "stdlib.h"
#include "stdio.h"

bool z=false;
char arr[8];
int vac[8];
int x;

// выбор случайной свободной клетки
// p1 - записываемый символ
// p2 - другой символ
void rand_move(char p1, char p2) {
    if (z == false) {
        for (int e = 0; e <= 8; e++) {
            if (arr[e] == p1 || arr[e] == p2) {
                vac[e] = 10;
            } else {
                vac[e] = e;
            }
        }
        do {
            srand(time(NULL));
            x = rand() % 9;
            z = false;
            for (int e = 0; e <= 8; e++) {
                if (vac[e] == x) {
                    arr[e] = p1;
                    z = true;
                }
            }
        } while (z == false);
    }
}

// алгоритм защиты
// p1 - символ комбинации, подозрительной на выйгрышную (Х/О)
// p2 - другой символ (Х/О)
// p3 - символ дополняющий строку до конца (защита - p3=p2; атака p3=p1)
void defend_attack(char p1, char p2, char p3) {
    for(int i=0; i<3; i++) {
        // проверка вертикальных строчек
        if ((((arr[i]==arr[i+6])&&(arr[i]==p1))&&((arr[i+3]!=p1)&&(arr[i+3]!=p2)))&&(z==false)) {
            arr[i+3]=p3;
            z=true;
        }
        if ((((arr[i]==arr[i+3])&&(arr[i]==p1))&&((arr[i+6]!=p1)&&(arr[i+6]!=p2)))&&(z==false)) {
            arr[i+6]=p3;
            z=true;
        }
        if ((((arr[i+6]==arr[i+3])&&(arr[i+6]==p1))&&((arr[i]!=p1)&&(arr[i]!=p2)))&&(z==false)) {
            arr[i]=p3;
            z=true;
        }
        // проверка горизонтальных строчек
        if ((((arr[3*i]==arr[3*i+2])&&(arr[3*i]==p1))&&((arr[3*i+1]!=p1)&&(arr[3*i+1]!=p2)))&&(z==false)) {
            arr[3*i+1]=p3;
            z=true;
        }
        if ((((arr[3*i]==arr[3*i+1])&&(arr[3*i]==p1))&&((arr[3*i+2]!=p1)&&(arr[3*i+2]!=p2)))&&(z==false)) {
            arr[3*i+2] =p3;
            z = true;
        }
        if ((((arr[3*i+2]==arr[3*i+1])&&(arr[3*i+2]==p1))&&((arr[3*i]!=p1)&&(arr[3*i]!=p2)))&&(z==false)) {
            arr[3*i] = p3;
            z = true;
        }
    }
    // проверка диагоналей
    if ((((arr[0]==arr[8])&&(arr[0]==p1))&&((arr[4]!=p1)&&(arr[4]!=p2)))||
        ((((arr[2]==arr[6])&&(arr[2]==p1))&&((arr[4]!=p1)&&(arr[4]!=p2)))&&(z==false))){
        arr[4]=p3;
        z=true;
    }
    if ((((arr[0]==arr[4])&&(arr[0]==p1))&&((arr[8]!=p1)&&(arr[8]!=p2)))&&(z==false)){
        arr[8]=p3;
        z=true;
    }
    if ((((arr[2]==arr[4])&&(arr[2]==p1))&&((arr[6]!=p1)&&(arr[6]!=p2)))&&(z==false)){
        arr[6]=p3;
        z=true;
    }
    if ((((arr[8]==arr[4])&&(arr[8]==p1))&&((arr[0]!=p1)&&(arr[0]!=p2)))&&(z==false)){
        arr[0]=p3;
        z=true;
    }
    if ((((arr[6]==arr[4])&&(arr[6]==p1))&&((arr[2]!=p1)&&(arr[2]!=p2)))&&(z==false)){
        arr[2]=p3;
        z=true;
    }
}

// Легкий бот
// p1 - символ бота
void bot_easy(char p1, char p2) {
    z=false;
    printf("Bot's move!\n");
    rand_move(p1,p2);
}

// Средний бот
// p1 - символ бота
// p2 - символ противника
void bot_medium(char p1, char p2) {
    z=false;
    printf("Bot's move!\n");
    defend_attack(p2,p1,p1);
    if (z==false) {
        rand_move(p1,p2);
    }
}

// Сложный бот
// p1 - символ бота
// p2 - символ противника
void bot_hard(char p1, char p2) {
    z=false;
    printf("Bot's move!\n");
    defend_attack(p1,p2,p1);
    if (z==false) {
        defend_attack(p2,p1,p1);
    }
    if (z==false) {
        rand_move(p1,p2);
    }
}