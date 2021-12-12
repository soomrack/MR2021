#include <gtk/gtk.h>
#include <stdio.h>
#include <stdbool.h>
#include "Bot.h"

int move_order = 1;
char field[9]={'1','2','3','4','5','6','7','8','9'};
int pos = 0;
char buffer_cell_value[2];

static GtkWidget *bot_first, *reset;
static GtkWidget *Cell[9];
static GtkWidget *presenter;
static GtkWidget *the_end;


int (*gameplay) (GtkWidget *Cell, gpointer data);
void (*gamer01_move) (char p1, char p2);
void (*gamer02_move) (char p1, char p2);

bool win() {
    for (int w=0; w<=2; w++) {
        if (field[3*w]==field[3*w+1]&&field[3*w+1]==field[3*w+2]) return true;
        if (field[w]==field[w+3]&&field[w+3]==field[w+6])  return true;
    }
    if ((field[0]==field[4]&&field[4]==field[8])||(field[2]==field[4]&&field[4]==field[6])) return true;
    else return false;
}

bool end_of_field() {
    int filled_cells = 0;
    for (int e = 0; e <= 8; e ++) {
        if (field[e] == 'X'||field[e] == 'O')
            filled_cells ++;
    }
    if (filled_cells == 9)  return true;
    else return false;
}

void human_move(char p1, char p2) {
    if (field[pos - 1] == p2) {
        gtk_label_set_text(GTK_LABEL(the_end), "Cheater detected, lose your turn!");
    }
    if (field[pos - 1] != p2){
        field[pos - 1] = p1;
        snprintf(buffer_cell_value, sizeof(buffer_cell_value), "%c", p1);
    }
}

void write_bot_choice () {
    gamer02_move('O', 'X');
    gtk_button_set_label(GTK_BUTTON(Cell[pos]), buffer_cell_value);
}

void bot_first_move () {
    write_bot_choice();
    gtk_widget_set_sensitive(bot_first, FALSE);
}

void disable_field () {
    for(int i = 0; i < 9; ++i)
        gtk_widget_set_sensitive(Cell[i], FALSE);
}

void enable_field () {
    for(int i = 0; i < 9; ++i)
        gtk_widget_set_sensitive(Cell[i], TRUE);
}

void reset_func (GtkWidget *reset, gpointer data) {
    move_order =1;
    for (int i=0; i<=8; i++) {
        field[i]= i+'0';
    }
    for(int i = 0; i < 9; ++i)
        gtk_button_set_label(GTK_BUTTON(Cell[i]), " ");

    gtk_label_set_text(GTK_LABEL(the_end), "It's a big brain time");
    win();
    enable_field();
    if (gamer02_move == human_move) {
        gtk_widget_set_sensitive(bot_first, FALSE);
    }
    else {
        gtk_widget_set_sensitive(bot_first, TRUE);
    }
}

int gameplay_bot(GtkWidget *Cell, gpointer data) {

    gtk_widget_set_sensitive(bot_first, FALSE);
    pos = (int)(intptr_t)data;
    gamer01_move('X', 'O');
    gtk_button_set_label(GTK_BUTTON(Cell), buffer_cell_value);
    if (win() == true) {
        gtk_label_set_text(GTK_LABEL(the_end), "X win! Game Over!");
        disable_field();
    }
    else {
        if(end_of_field() == true) {
            gtk_label_set_text(GTK_LABEL(the_end), "End of the field, Game Over!");
            disable_field();
        }
    }
    if ((win() != true)&&(end_of_field() != true)) {
        gtk_label_set_text(GTK_LABEL(presenter),"Bot is thinking...");
        write_bot_choice();
        gtk_label_set_text(GTK_LABEL(presenter),"Your move!");
        if (win() == true) {
            gtk_label_set_text(GTK_LABEL(the_end), "O win! Game Over!");
            disable_field();
        }
        else {
            if (end_of_field() == true) {
                gtk_label_set_text(GTK_LABEL(the_end), "End of the field, Game Over!");
                disable_field();
            }
        }
    }
}

int pole(int argc, char **argv) {
    GtkWidget *window, *grid;
    gtk_init(&argc, &argv);

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "Tic-Tac-Toe");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width (GTK_CONTAINER (window), 20);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    grid = gtk_grid_new();
    gtk_container_add (GTK_CONTAINER(window), grid);

    for(int i = 0; i < 9; ++i) {
        Cell[i] = gtk_button_new_with_label(" ");
        g_signal_connect (Cell[i], "clicked",
                          G_CALLBACK(gameplay), (gpointer) (intptr_t) (1));
        gtk_grid_attach(GTK_GRID(grid), Cell[i], 0, 1, 1, 1);
    }

    presenter = gtk_label_new ("Tic-Tac-Toe");
    gtk_grid_attach (GTK_GRID(grid), presenter, 0, 0, 3, 1);

    the_end = gtk_label_new ("It's a big brain time!");
    gtk_grid_attach (GTK_GRID(grid), the_end, 0, 4, 3, 1);

    reset = gtk_button_new_with_label("Reset");
    g_signal_connect (reset, "clicked", G_CALLBACK(reset_func), NULL);
    gtk_grid_attach (GTK_GRID(grid), reset, 4, 3, 1, 1);

    bot_first = gtk_button_new_with_label("Bot 1st");
    g_signal_connect (bot_first, "clicked", G_CALLBACK(bot_first_move), NULL);
    gtk_grid_attach (GTK_GRID(grid), bot_first, 4, 1, 1, 1);

    gtk_widget_show_all(window);
    gtk_main();
}

void start_screen() {
    int difficulty;
    printf("   Welcome to the Tic-Tac-Toe game\n");
    gameplay = gameplay_bot;
    gamer01_move=human_move;
}

int main (int argc, char **argv) {
    start_screen();
    pole(argc, argv);
    return 0;
}