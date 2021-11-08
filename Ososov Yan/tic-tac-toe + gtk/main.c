#include <gtk/gtk.h>
#include <stdio.h>
#include <ctype.h>
#include "Bot.h"


char a[9];
const char * name1[20], * name2[20];
int result;
int queue = 1;


static GtkWidget  * entry1, * entry2, *label3, *button2, * grid, * window,  * label4, * label5 , * button4, * cell1,  * cell2, * cell3, * cell4, * cell5, * cell6, * cell7, * cell8,* cell, * cell9;


void definition_of_players(){
    *name1 = gtk_entry_get_text (GTK_ENTRY(entry1));
    *name2 = gtk_entry_get_text (GTK_ENTRY(entry2));
    if (  strcmp(name1[0], "\0") == 0 || strcmp(name2[0], "\0") == 0){
        label3 = gtk_label_new("The names weren't entered. Try again!");
    } else {
        gtk_widget_set_sensitive(button2, TRUE);
        gtk_widget_set_sensitive(entry1, FALSE);
        gtk_widget_set_sensitive(entry2, FALSE);
    }

}

void Introduction(int argc, char **argv){
    GtkWidget * button1, * label1, * label2;
    gtk_init (&argc, &argv);
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), " Introduction");
    g_signal_connect (G_OBJECT (window), "destroy", gtk_main_quit, NULL);

    grid = gtk_grid_new();
    gtk_container_add( GTK_CONTAINER(window), grid);

    label1 = gtk_label_new("To start the game firstly chose names of players");
    gtk_grid_attach(GTK_GRID(grid), label1, 0, 1, 1, 1 );

    label2 = gtk_label_new("Name of player who goes first with 'x'");
    gtk_grid_attach(GTK_GRID(grid), label2, 0, 2, 1, 1 );

    entry1 = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry1, 0, 3, 1, 1 );

    label2 = gtk_label_new("Name of player who goes second with '0'");
    gtk_grid_attach(GTK_GRID(grid), label2, 0, 4, 1, 1 );

    entry2 = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry2, 0, 5, 1, 1 );

    label3 = gtk_label_new("both of strings should be contained");
    gtk_grid_attach(GTK_GRID(grid), label3, 0, 6, 1, 1 );

    button1 = gtk_button_new_with_label("Save");
    g_signal_connect ( button1, "clicked",G_CALLBACK(definition_of_players),NULL);
    gtk_grid_attach(GTK_GRID(grid), button1, 0, 7, 1, 1 );

    button2 =gtk_button_new_with_label("Start the game");
    g_signal_connect ( button2, "clicked",gtk_main_quit, NULL);
    gtk_grid_attach(GTK_GRID(grid), button2, 1, 7, 1, 1 );
    gtk_widget_set_sensitive(button2, FALSE);

    gtk_widget_show_all (window);
    gtk_main ();
}

void Who_is_the_winner(int g){
    if ( g == 1){
        gtk_label_set_label(GTK_LABEL(label5), "Winner");
        gtk_label_set_label(GTK_LABEL(label4), *name1);
        result = 1;
    }
    if ( g == 8){
        result = 1;
        gtk_label_set_label(GTK_LABEL(label5), "Winner");
        gtk_label_set_label(GTK_LABEL(label4), *name2);
    }

}

void determining_the_winner(){
    int sum;
    for (int i = 0 ; i <= 2 ; i++) {
        sum = a[i+0] * a[i+3] * a[i+6];
        Who_is_the_winner(sum);
    }
    for (int i = 0 ; i < 9 ; i=i+3) {
        sum = a[0+i] * a[1+i] * a[2+i];
        Who_is_the_winner(sum);
    }
    sum = a[0] * a[4] * a[8];
    Who_is_the_winner(sum);
    sum = a[2] * a[4] * a[6];
    Who_is_the_winner(sum);

}

void Draft(int x){
    if (x == 10 && result == 0){
        gtk_label_set_label(GTK_LABEL(label5), "is winner");
        gtk_label_set_label(GTK_LABEL(label4), "Nobody");
    }
}

int move1(GtkWidget * cell, gpointer number){
    const char * symbol_inside_cell;
    if (queue % 2 == 1){
        symbol_inside_cell = "X";
        a[(intptr_t)number] = 1;
        gtk_label_set_label(GTK_LABEL(label4), *name2);
    } else{
        symbol_inside_cell = "0";
        a[(intptr_t)number] = 2;
        gtk_label_set_label(GTK_LABEL(label4), *name1);
    }
    gtk_button_set_label(GTK_BUTTON(cell), symbol_inside_cell);
    gtk_widget_set_sensitive(cell, FALSE);
    queue++;
    determining_the_winner();
    Draft(queue);
}

/*GtkWidget definition_cell(int b){
    switch (b) {
        case'0':{
            (gpointer)(intptr_t)(0);
            return * cell1;
        }
        case'1':{
            (gpointer)(intptr_t)(1);
            return * cell2;
        }
        case'2':{
            (gpointer)(intptr_t)(2);
            return * cell3;
        }
        case'3':{
            (gpointer)(intptr_t)(3);
            return * cell4;
        }
        case'4':{
            (gpointer)(intptr_t)(4);
            return * cell5;
        }

        case'5':{
            (gpointer)(intptr_t)(5);
            return * cell6;
        }
        case'6':{
            (gpointer)(intptr_t)(6);
            return * cell7;
        }
        case'7':{
            (gpointer)(intptr_t)(7);
            return * cell8;
        }
        case'8':{
            (gpointer)(intptr_t)(8);
            return * cell9;
        }
        default:{}


    }
}

void Bot_move_first(){
    *cell = definition_cell(Bot(a[0]));
    gtk_test_widget_click(cell, );


}
void Bot_move_second(){

}
void Battle_of_Bots(){

}


void game_mode(){
    if ( strcmp(name1[0], "Bot") == 0 || strcmp(name2[0], "Bot") != 0 ){
        Bot_move_second();
    } else{
        if(strcmp(name1[0], "Bot") != 0 || strcmp(name2[0], "Bot") == 0){
            Bot_move_first();
        } else{
            if (strcmp(name1[0], "Bot") == 0 || strcmp(name2[0], "Bot") == 0 ){
                Battle_of_Bots();
            }
        }
    }

}*/

int canvas (int argc, char **argv)
{
    gtk_init (&argc, &argv);

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), " Tic - Tac - Toe");
    //g_signal_connect (G_OBJECT (window), "destroy", gtk_main_quit, NULL);

    grid = gtk_grid_new();
    gtk_container_add( GTK_CONTAINER(window), grid);

    cell1 = gtk_button_new_with_label(&a[0]);
    g_signal_connect ( cell1, "clicked",G_CALLBACK(move1),(gpointer)(intptr_t)(0));
    gtk_grid_attach(GTK_GRID(grid), cell1, 0, 1, 1, 1 );

    cell2 = gtk_button_new_with_label(&a[1]);
    g_signal_connect ( cell2, "clicked",G_CALLBACK(move1),(gpointer)(intptr_t)(1));
    gtk_grid_attach(GTK_GRID(grid), cell2, 0, 2, 1, 1 );

    cell3 = gtk_button_new_with_label(&a[2]);
    g_signal_connect ( cell3, "clicked",G_CALLBACK(move1),(gpointer)(intptr_t)(2));
    gtk_grid_attach(GTK_GRID(grid), cell3, 0, 3, 1, 1 );

    cell4 = gtk_button_new_with_label(&a[3]);
    g_signal_connect ( cell4, "clicked",G_CALLBACK(move1),(gpointer)(intptr_t)(3));
    gtk_grid_attach(GTK_GRID(grid), cell4, 1, 1, 1, 1 );

    cell5 = gtk_button_new_with_label(&a[4]);
    g_signal_connect ( cell5, "clicked",G_CALLBACK(move1),(gpointer)(intptr_t)(4));
    gtk_grid_attach(GTK_GRID(grid), cell5, 1, 2, 1, 1 );

    cell6 = gtk_button_new_with_label(&a[5]);
    g_signal_connect ( cell6, "clicked",G_CALLBACK(move1),(gpointer)(intptr_t)(5));
    gtk_grid_attach(GTK_GRID(grid), cell6, 1, 3, 1, 1 );

    cell7 = gtk_button_new_with_label(&a[6]);
    g_signal_connect ( cell7, "clicked",G_CALLBACK(move1),(gpointer)(intptr_t)(6));
    gtk_grid_attach(GTK_GRID(grid), cell7, 2, 1, 1, 1 );

    cell8 = gtk_button_new_with_label(&a[7]);
    g_signal_connect ( cell8, "clicked",G_CALLBACK(move1),(gpointer)(intptr_t)(7));
    gtk_grid_attach(GTK_GRID(grid), cell8, 2, 2, 1, 1 );

    cell9 = gtk_button_new_with_label(&a[8]);
    g_signal_connect ( cell9, "clicked",G_CALLBACK(move1),(gpointer)(intptr_t)(8));
    gtk_grid_attach(GTK_GRID(grid), cell9, 2, 3, 1, 1 );

    label4 = gtk_label_new(*name1);
    gtk_grid_attach(GTK_GRID(grid), label4, 0, 4, 1, 1 );

    label5 = gtk_label_new("Which move");
    gtk_grid_attach(GTK_GRID(grid), label5, 1, 4, 1, 1 );

    /*button4 = gtk_button_new_with_label("restart");
    g_signal_connect ( button4, "clicked",G_CALLBACK(restart),(gpointer)(intptr_t)(10));
    gtk_grid_attach(GTK_GRID(grid), button4, 1, 5, 1, 1 );*/


    determining_the_winner();

    gtk_widget_show_all (window);
    gtk_main ();

    return 0;
}


int main (int argc, char **argv){
    Introduction(argc, argv);
    canvas(argc, argv);
}
