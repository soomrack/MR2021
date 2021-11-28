#include "Bot.h"
#include <stdio.h>
#include "gtk/gtk.h"
#include <time.h>
#include <stdlib.h>

int Avoidance_of_repetition(int poss){
    if (a[poss] == 1 || a[poss] == 2){
        return(0);
    } else{
        return (1);
    }

}

int Bot(){
    int pos ;
    time_t t;
    do {
        srand(time(&t));
        pos = rand()%8;
        printf("%d",pos);
        printf("%d",a[pos]);
    } while(Avoidance_of_repetition(pos) == 0);
    printf("%d",*a+pos);
    return pos;

}
/*void Bot_move(){
    int c = Bot();
    switch (c){
        case (0): gtk_button_clicked(GTK_BUTTON(cell1));
        case (1): gtk_button_clicked(GTK_BUTTON(cell2));
        case (2): gtk_button_clicked(GTK_BUTTON(cell3));
        case (3): gtk_button_clicked(GTK_BUTTON(cell4));
        case (4): gtk_button_clicked(GTK_BUTTON(cell5));
        case (5): gtk_button_clicked(GTK_BUTTON(cell6));
        case (6): gtk_button_clicked(GTK_BUTTON(cell7));
        case (7): gtk_button_clicked(GTK_BUTTON(cell8));
        case (8): gtk_button_clicked(GTK_BUTTON(cell9));
        default:;
            printf("gbcz");
    }
}*/
