#include <gtk/gtk.h>
#include <stdio.h>
#include <stdbool.h>
#include "GTK_X_O.h"


char arr[9]={'1','2','3','4','5','6','7','8','9'};
int move_order=1;

char player1 = 'X';
char player2 = 'O';

static GtkWidget *Cell1;
static GtkWidget *Cell2;
static GtkWidget *Cell3;
static GtkWidget *Cell4;
static GtkWidget *Cell5;
static GtkWidget *Cell6;
static GtkWidget *Cell7;
static GtkWidget *Cell8;
static GtkWidget *Cell9;
static GtkWidget *presenter;
static GtkWidget *the_end;

/* проверка выйгрышной комбинации */
bool win() {
    for (int i=0; i<=2; i++) {
        if (arr[3*i]==arr[3*i+1]&&arr[3*i+1]==arr[3*i+2]) {
            return true;
        }
        if (arr[i]==arr[i+3]&&arr[i+3]==arr[i+6]) {
            return true;
        }
    }

    if ((arr[0]==arr[4]&&arr[4]==arr[8])||
        (arr[2]==arr[4]&&arr[4]==arr[6])) {
        return true;
    }
    else {
        return false;
    }
}

/* проверка на заполненность поля */
bool Fields_end() {
    int counter = 0;
    for (int i = 0; i <= 8; i++) {
        if (arr[i] == 'X' || arr[i] == 'O') {
            counter++; //Shows number of filled cells
        }
    }
    if (counter == 9) {
        return true;
    }
    else {
        return false;
    }
}

/*Ход игрока */
void human_move(GtkWidget *Cell, gpointer data_hum) {
    int HumanPos = data_hum;

    if (move_order %2 != 0) {
        player1 = 'X';
        player2 = 'O';
    }
    if (move_order %2 == 0) {
        player1 = 'O';
        player2 = 'X';
    }
    if (arr[HumanPos - 1] == player2) {
        gtk_label_set_text(GTK_LABEL(the_end), "Stop right there, you violated the law!");
        move_order++;
    }
    if (arr[HumanPos - 1] != player2) {
        arr[HumanPos - 1] = player1;
        char buffer1[2];
        snprintf(buffer1, sizeof (buffer1), "%c", player1);
        gtk_button_set_label(GTK_BUTTON(Cell), buffer1);
        move_order++;
    }
    if (win() == true) {
        gtk_label_set_text(GTK_LABEL(the_end), "You win! Game Over!");
    }
    if (Fields_end() == true) {
        gtk_label_set_text(GTK_LABEL(the_end), "End of the field, Game Over!");
    }
}

int main (int argc, char **argv) {

    GtkWidget *window, *grid, *button;
    gtk_init(&argc, &argv);

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "Tic-Tac-Toe");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width (GTK_CONTAINER (window), 20);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    grid = gtk_grid_new();
    gtk_container_add (GTK_CONTAINER(window), grid);

    Cell1 = gtk_button_new_with_label(" ");
    gtk_grid_attach (GTK_GRID(grid), Cell1, 0, 1, 1, 1);

    Cell2 = gtk_button_new_with_label(" ");
    gtk_grid_attach (GTK_GRID(grid), Cell2, 1, 1, 1, 1);

    Cell3 = gtk_button_new_with_label(" ");
    gtk_grid_attach (GTK_GRID(grid), Cell3, 2, 1, 1, 1);

    Cell4 = gtk_button_new_with_label(" ");
    gtk_grid_attach (GTK_GRID(grid), Cell4, 0, 2, 1, 1);

    Cell5 = gtk_button_new_with_label(" ");
    gtk_grid_attach (GTK_GRID(grid), Cell5, 1, 2, 1, 1);

    Cell6 = gtk_button_new_with_label(" ");
    gtk_grid_attach (GTK_GRID(grid), Cell6, 2, 2, 1, 1);

    Cell7 = gtk_button_new_with_label(" ");
    gtk_grid_attach (GTK_GRID(grid), Cell7, 0, 3, 1, 1);

    Cell8 = gtk_button_new_with_label(" ");
    gtk_grid_attach (GTK_GRID(grid), Cell8, 1, 3, 1, 1);

    Cell9 = gtk_button_new_with_label(" ");
    gtk_grid_attach (GTK_GRID(grid), Cell9, 2, 3, 1, 1);


    g_signal_connect (Cell1, "clicked", G_CALLBACK(human_move), 1);
    g_signal_connect (Cell2, "clicked", G_CALLBACK(human_move), 2);
    g_signal_connect (Cell3, "clicked", G_CALLBACK(human_move), 3);
    g_signal_connect (Cell4, "clicked", G_CALLBACK(human_move), 4);
    g_signal_connect (Cell5, "clicked", G_CALLBACK(human_move), 5);
    g_signal_connect (Cell6, "clicked", G_CALLBACK(human_move), 6);
    g_signal_connect (Cell7, "clicked", G_CALLBACK(human_move), 7);
    g_signal_connect (Cell8, "clicked", G_CALLBACK(human_move), 8);
    g_signal_connect (Cell9, "clicked", G_CALLBACK(human_move), 9);

    presenter = gtk_label_new ("It's your move");
    gtk_grid_attach (GTK_GRID(grid), presenter, 0, 0, 3, 1);

    the_end = gtk_label_new ("well, it's not enough");
    gtk_grid_attach (GTK_GRID(grid), the_end, 0, 4, 3, 1);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}