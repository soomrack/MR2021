#include <stdio.h>
#include <conio.h>
#include <cstdlib>
#include "time.h"

char a[9]; int flag_turn, flag_win=0;
char human, bot;
int check(char c, char d, char e) {

    if (((c == human) && (d == human)) && (e == human)) {
        flag_win=1;
        printf("%s","Human wins");

    }
    if (((c == bot) && (d == bot)) && (e == bot)) {
        flag_win=1;
        printf("%s","Bot wins");

    }
    return(0);

}

void print_field() {
    printf("%c|", a[0]);
    printf("%c|", a[1]);
    printf("%c\n", a[2]);
    printf("- - -\n");
    printf("%c|", a[3]);
    printf("%c|", a[4]);
    printf("%c\n", a[5]);
    printf("- - -\n");
    printf("%c|", a[6]);
    printf("%c|", a[7]);
    printf("%c\n", a[8]);
}

void bot_goes(){int position;
    printf("%s","Now it's bot's turns\n");
    position=rand() % 8;
    while ((a[position])!=' '){
        position=rand() % 8;
    }
    a[position]=bot;
    print_field();
}

void human_goes(){int position;
    printf("%s","Choose the place for your symbol\n");
    scanf(" %d",&position);
    while ((a[position-1])!=' '){
        printf("%s","This place is already engaged, try again\n");
        scanf(" %d",&position);
    }
    a[position-1]=human;
    print_field();
}

void turn(){
    if (flag_turn==1){
        bot_goes();
        flag_turn=0;
    }
    else {
        flag_turn=1;
        human_goes();
    }

}


int main() {
    int count=0;
    srand(time(NULL));
    for (int i=0;i<9;i++)
        a[i]=' ';
    printf("%s\n", "Choose your symbol :x or 0 ");
    human = getchar();
    while ((human != '0') && (human != 'x')) {
        printf("%s", "You have printed wrong symbol, try again.");
        human = getchar();

    }
    if (human == '0')
        bot = 'x';
    else bot = '0';
    print_field();
    while ((flag_win!=1)&&(count<9)){
      turn();
        check(a[0],a[1],a[2]);
        check(a[3],a[4],a[5]);
        check(a[6],a[7],a[8]);
        check(a[0],a[3],a[6]);
        check(a[1],a[4],a[7]);
        check(a[2],a[5],a[8]);
        check(a[0],a[4],a[8]);
        check(a[2],a[4],a[6]);
        count++;
    }
if ((count==9)&&(flag_win!=1)){
    printf("%s", "Draw");
}
}




