#include <synchapi.h>
#include <cstdlib>
#include <ctime>
#include "BotIO.h"

int generateRandomField(MyLabelButton (*field)[3],int (*availableField)[WIDTH]) {
    int k = 0;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            (strcmp((char*)field[i][j].get_label()," ") == 0) ? (availableField[i][j] = ++k) : (availableField[i][j] = 0);
        }
    }
    return k;
}

void botInput(MyLabelButton (*field)[3]) {
    srand((int)time(0));

    int availableField[HEIGHT][WIDTH];
    int randomRange = generateRandomField(field,availableField);
    int randomCell;
    randomCell = 1 + (rand() % randomRange);

    (turn % 2 == 0) ? (playerTurn = X) : (playerTurn = O);

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (availableField[i][j] == randomCell) {
                Sleep(500);
                (playerTurn == X) ? (field[i][j].set_label("X")) : (field[i][j].set_label("O"));
                field[i][j].set_unactive();
            }
        }
    }

    turn++;
}

void playerInput(MyLabelButton (*field)[3],MyLabelButton pressed_button){
    (turn % 2 == 0) ? (playerTurn = X) : (playerTurn = O);
    if (playerTurn == X) {
        pressed_button.set_label("X");
    }
    else pressed_button.set_label("O");
    pressed_button.set_unactive();
    turn++;
};

bool checkWin(MyLabelButton (*field)[3]) {
    bool flag;
    int intDgFlag1 = 0, intDgFlag2 = 0, intVrFlag = 0, intGrFlag = 0;
    if (strcmp((char*)field[1][1].get_label()," ") != 0) {
        for (int i = 0; i < WIDTH - 1; i++) {														//Проверка первой диагонали

            if (strcmp((char*)field[i+1][i+1].get_label(),(char*)field[i][i].get_label())==0) intDgFlag1++;
        }

        for (int i = 0; i < WIDTH - 1; i++) {														//Проверка второй диагонали
            if (strcmp((char*)field[WIDTH- 1-i][i].get_label(),(char*)field[WIDTH-1-(i + 1)][i + 1].get_label())==0)
                intDgFlag2++;
        }
    }

    for (int i = 0; i < WIDTH; i++) {																//Проверка вертикалей
        for (int j = 0; j < HEIGHT - 1; j++) {
            if (strcmp((char*)field[(WIDTH-1)/2][i].get_label()," ")!=0)
                if (strcmp((char*)field[j + 1][i].get_label(),(char*)field[j][i].get_label())==0) intVrFlag++;
        }
        if (intVrFlag != 2) intVrFlag = 0;
        if (intVrFlag == 2) break;
    }

    for (int i = 0; i < HEIGHT; i++) {																//Проверка горизонталей
        for (int j = 0; j < HEIGHT - 1; j++) {
            if (strcmp((char*)field[i][(HEIGHT - 1) / 2].get_label()," ")!=0)
                if (strcmp((char*)field[i][j+1].get_label(),(char*)field[i][j].get_label())==0) intGrFlag++;
        }
        if (intGrFlag != 2) intGrFlag = 0;
        if (intGrFlag == 2) break;
    }

    if (intDgFlag1 == 2 || intDgFlag2 == 2 || intVrFlag == 2 || intGrFlag == 2) flag = true;
    else flag = false;
    return flag;
}

bool checkDraw(MyLabelButton (*field)[3]) {
    bool flag;
    int intFlag = 0;

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (strcmp((char*)field[i][j].get_label()," ")!=0) intFlag++;
        }
    }
    if (intFlag == 9) flag = true;
    else flag = false;
    return flag;
}

