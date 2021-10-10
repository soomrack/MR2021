#include <stdio.h>

char field[9];

void init(){
    for (int i = 0; i < 9; ++i) {
        field[i]=49+i;
    }
}

_Bool EndOfField(){
    _Bool check = 1;
    for (int i = 0; i < 9; ++i) {
        if (field[i]!=48 && field[i]!=88){
            check = 0;
        }
    }
    return check;
}


void PtintField(){
    for (int i = 0; i < 3; ++i){
        printf("%c|%c|%c\n",field[i*3],field[i*3+1],field[i*3+2]);
        printf("-----\n");
    }
}

char CheckWin(){
    for (int i = 0; i < 3; ++i) {
        if((field[i*3]+field[i*3+1]+field[i*3+2])==144){
            return '0';
        }
        if((field[i*3]+field[i*3+1]+field[i*3+2])==264){
            return 'X';
        }
        if((field[3+i]+field[6+i]+field[0+i])==144){
            return '0';
        }
        if((field[3+i]+field[6+i]+field[0+i])==264){
            return 'X';
        }
    }
    if((field[0]+field[4]+field[8])==144){
        return '0';
    }
    if((field[0]+field[4]+field[8])==264){
        return 'X';
    }
    if((field[2]+field[4]+field[6])==144){
        return '0';
    }
    if((field[2]+field[4]+field[6])==264){
        return 'X';
    }
    if (EndOfField()) {return 1;}
    return 0;
}

void game(){
    _Bool eog =0;
    char Player = 48;
    char Position;

    while (!eog){
        PtintField();

        if(Player==48){
            Player=88;
        } else Player = 48;

        printf("%c's turn, enter position\n",Player);

        while(1){
            scanf(" %c",&Position);
            scanf( "%*[^\n]" );
            if((Position-49)<0 || (Position-49)>8||(field[Position-49])==48||(field[Position-49])==88){
                printf("Please re-enter\n");
                continue;
            }
            field[Position-49]=Player;
            break;
        }

        if(CheckWin()){
            printf("%c win\n",CheckWin());
            eog=1;
        }

    }
}

void StartGame(){
    char key;
    printf("Enter 1 to start the game\n");
    while(1){

        scanf(" %c",&key);
        scanf( "%*[^\n]" );
        if(key=='1'){
            break;
        }
        printf("Please re-enter\n");
    }
}

_Bool CheckReplay(){
    char check;
    printf("Do you want to play again?(Enter y/n)\n");
    while(1){
        scanf(" %c",&check);
        scanf( "%*[^\n]" );
        if(check=='y'||check=='Y'){
            return 1;
        }
        if(check=='n'||check=='N'){
            return 0;
        }
        printf("Please re-enter\n");
    }
}

int main() {
    _Bool replay = 1;
    while (replay) {
        init();
        StartGame();
        game();
        if (!CheckReplay()){
            replay=0;
            printf("Thanks for playing");
        }
    }
    return 0;
}
