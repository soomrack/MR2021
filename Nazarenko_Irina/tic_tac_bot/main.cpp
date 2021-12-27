#include <stdio.h>
#include <conio.h>
#include <cstdlib>
#include "time.h"

char a[9]; int b;
char human, bot;
int check(char c, char d, char e) {

    if (((c == '0') && (d == '0')) && (e == '0')) {
        printf("win");

    }
    return(0);

}

void bot_goes(){int position;
    printf("%s","Now it's bot's turns\n");
    position=rand() % 8;
    a[position]=bot;
}


void human_goes(){int position;
    printf("%s","Choose the place for your symbol\n");
    scanf(" %d",&position);
    a[position-1]=human;
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

int main() {
    srand(time(NULL));
    for (int i=0;i<9;i++)
        a[i]=' ';
    printf("%s\n", "Choose your symbol :x or 0 ");
    human = getchar();
    while ((human != '0') && (human != 'x')) {
        human = getchar();
        printf("%s", "You have printed wrong symbol, try again.");
    }
    if (human == '0')
        bot = 'x';
    else bot = '0';
    print_field();
    human_goes();
    print_field();
    bot_goes();
    print_field();
    bot_goes();
    print_field();
}




    /*for(int i=0; i<=9;i++) {
        scanf(" %d", &b);
        if ((b<1)||(b>9)){
            printf("%s","You have printed wrong symbol, try again.");
            break;
        }

        scanf(" %c", &a[b-1]);
        if (((a[b-1])!='x')&&((a[b-1])!='0'))
        {
            printf("%s","You have printed wrong symbol, try again.");
            break;
        }

        print_field();


        check(a[0],a[1],a[2]);
        check(a[3],a[4],a[5]);
        check(a[6],a[7],a[8]);
        check(a[0],a[3],a[6]);
        check(a[1],a[4],a[7]);
        check(a[2],a[5],a[8]);
        check(a[0],a[4],a[7]);
        check(a[2],a[4],a[6]);
    };


    return 0;
}
*/
