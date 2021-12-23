#include <stdio.h>
#include <stdbool.h>

void field();//вывод поля
void Replacement(char player, int pfield);//вставка на поле символа игрока
bool win(char cell);//проверка на победу


char player1='X'; // символ игрока 1
char player2='0'; // символ игрока 2
int pfield1; //место для player 1
int pfield2; //место для player 2
char pf[9]={'1','2','3','4','5','6','7','8','9'}; //playing field
int n=0;//общий счетчик ходов
int bad=0;//ошибка, когда выбраннна заполненная клетка,она остается равна 0, ход повторяется, если пустая, то прибавляется единица и идет игра дальше

int main() {
    while (n<10){
        field();
        n++;
        while (bad<1){
            printf("\nPlayer 1, Select the cell number:");
            for (int i=0;((pfield1=getchar())!='\n')||(i<1);i++) {
                Replacement(player1, pfield1);
            }
        }
        bad=0;
        if (win(player1)) {
            field();
            printf("\nPlayer number 1 won");
            return 0;
        }


        n++;
        if (n<10){
            field();
            while (bad<1){
                printf("\nPlayer 2, Select the cell number:");
                for (int i=0;((pfield2=getchar())!='\n')||(i<1);i++) {
                    Replacement(player2, pfield2);
                }
            }
            bad=0;
            if (win(player2)){//конец игры,если все ячейки заполнены, но никто не победил
                field();
                printf("\nPlayer number 2 won");
                return 0;
            }
        }
        else {
            printf("Game is over");
        }
    }
    return 0;
}

void field(){//вывод поля на экран
    printf("\n %c | %c | %c \n",pf[0],pf[1],pf[2]);
    printf("----------\n");
    printf(" %c | %c | %c \n",pf[3],pf[4],pf[5]);
    printf("----------\n");
    printf(" %c | %c | %c\n",pf[6],pf[7],pf[8]);
}

void Replacement(char player, int pfield){ //вставка на поле символа игрока
    for (int i=0;i<9;i++){
        if ((pfield-49)==i){
            if ((pf[i]=='1')||(pf[i]=='2')||(pf[i]=='3')||\
            (pf[i]=='4')||(pf[i]=='5')||(pf[i]=='6')||\
            (pf[i]=='7')||(pf[i]=='8')||(pf[i]=='9')){
                pf[i]=player;
                bad++;
            }
            else {
                printf("Select an empty cell");
            }
        }
    }
}

bool win(char cell) { //посылаем сюда 0 или X, проверка на победу
    if (cell==pf[0]){
        if (cell==pf[1]){
            if (cell==pf[2]){
                return true;
            }
        }
        else if (cell==pf[3]){
            if (cell==pf[6]){
                return true;
            }
        }
        else if (cell==pf[4]){
            if (cell==pf[8]){
                return true;
            }
        }
    }
    if (cell==pf[1]){
        if (cell==pf[4]){
            if (cell==pf[7]){
                return true;
            }
        }
    }
    if (cell==pf[2]){
        if (cell==pf[5]){
            if (cell==pf[8]){
                return true;
            }
        }
        else if (cell==pf[4]){
            if (cell==pf[6]){
                return true;
            }
        }
    }
    if (cell==pf[3]){
        if (cell==pf[4]){
            if (cell==pf[5]){
                return true;
            }
        }
    }
    if (cell==pf[6]){
        if (cell==pf[7]){
            if (cell==pf[8]){
                return true;
            }
        }

    }
    return false;
}

