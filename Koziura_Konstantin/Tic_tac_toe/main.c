#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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


void PrintField(){
    system("cls");
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

void Bot_move(char Symbol){
    char Position;

    while(1){
        Position = rand()%9;
        if((field[Position])==48||(field[Position])==88){
            continue;
        }
        field[Position]=Symbol;
        break;
    }
}

void Human_move(char Symbol){
    char Position;
    printf("%c's turn, enter position\n",Symbol);

    while(1){
        scanf(" %c",&Position);
        scanf( "%*[^\n]" );
        if((Position-49)<0 || (Position-49)>8||(field[Position-49])==48||(field[Position-49])==88){
            printf("Please re-enter\n");
            continue;
        }
        field[Position-49]=Symbol;
        break;
    }
}

void (*Gamer1_move)(char);
void (*Gamer2_move)(char);

void game(){
    _Bool eog =0;
    char Player = 48;
    while (!eog){
        PrintField();

        if(Player==48){
            Player=88;
            Gamer1_move(Player);
        } else {
            Player = 48;
            Gamer2_move(Player);
        }

        if(CheckWin()){
            system("cls");
            PrintField();
            printf("%c win\n",CheckWin());
            eog=1;
        }

    }
}

void StartGame(){
    char key;
    system("cls");
    printf("Enter 1 to start the game\n");
    while(1){

        scanf(" %c",&key);
        scanf( "%*[^\n]" );
        if(key=='1'){
            break;
        }
        printf("Please re-enter\n");
    }
    system("cls");
    printf("Enter the game mode number\n"
           "1 - Two humans game\n"
           "2 - Bot is \"X\" and human is \"0\"\n"
           "3 - Bot is \"0\" and human is \"X\"\n"
           "4 - Both players are bots\n");
    while(1){
        scanf(" %c",&key);
        scanf( "%*[^\n]" );
        if (key=='1') {
            Gamer1_move = Human_move;
            Gamer2_move = Human_move;
            break;
        } else if (key=='2'){
            Gamer1_move = Bot_move;
            Gamer2_move = Human_move;
            break;
        } else if (key=='3'){
            Gamer1_move = Human_move;
            Gamer2_move = Bot_move;
            break;
        } else if (key=='4') {
            Gamer1_move = Bot_move;
            Gamer2_move = Bot_move;
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

    srand(time(NULL));
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
