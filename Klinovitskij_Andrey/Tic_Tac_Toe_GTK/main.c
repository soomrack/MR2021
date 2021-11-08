#include <gtk/gtk.h>
#include <stdio.h>
#include<stdlib.h>

char field[10] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'}; //Field array. X or 0


char mark = 'X';

static GtkWidget *Cell1;
static GtkWidget *Cell2;
static GtkWidget *Cell3;
static GtkWidget *Cell4;
static GtkWidget *Cell5;
static GtkWidget *Cell6;
static GtkWidget *Cell7;
static GtkWidget *Cell8;
static GtkWidget *Cell9;
static GtkWidget *header;
static GtkWidget *footer;
static GtkWidget *window;
static GtkWidget *grid;

// All possible situations to win
int checkWin() {
    // return 1 = Win
    // return 2 = Draw
    // return 0 = Game in progress

    for (int i = 0; i <= 2; i++) {
        if ((field[i] == field[i + 1]) && (field[i + 1] == field[i + 2]))
            return 1;
        if ((field[i] == field[i + 3]) && (field[i + 3] == field[i + 6]))
            return 1;
    }
    if ((field[0] == field[4]) && (field[4] == field[8]))
        return 1;
    if ((field[2] == field[4]) && (field[4] == field[6]))
        return 1;

    if ((field[0] != '1') || (field[1] != '2') || (field[2] != '3') || (field[3] != '4') || (field[4] != '5') ||
        (field[5] != '6') || (field[6] != '7') || (field[7] != '8') || (field[8] != '9'))
        return 0;
    return 2;
}

void Foolproof(int Position, char Mark, int *player) { //Foolproof for mistakes
    if (Position == 1 && field[0] == '1')
        gtk_button_set_label(GTK_BUTTON(Cell1), Mark);
    else if (Position == 2 && field[1] == '2')
        gtk_button_set_label(GTK_BUTTON(Cell2), Mark);
    else if (Position == 3 && field[2] == '3')
        gtk_button_set_label(GTK_BUTTON(Cell3), Mark);
    else if (Position == 4 && field[3] == '4')
        gtk_button_set_label(GTK_BUTTON(Cell4), Mark);
    else if (Position == 5 && field[4] == '5')
        gtk_button_set_label(GTK_BUTTON(Cell5), Mark);
    else if (Position == 6 && field[5] == '6')
        gtk_button_set_label(GTK_BUTTON(Cell6), Mark);
    else if (Position == 7 && field[6] == '7')
        gtk_button_set_label(GTK_BUTTON(Cell7), Mark);
    else if (Position == 8 && field[7] == '8')
        gtk_button_set_label(GTK_BUTTON(Cell8), Mark);
    else if (Position == 9 && field[8] == '9')
        gtk_button_set_label(GTK_BUTTON(Cell9), Mark);
    else {
        //Motivational message!
        gtk_label_set_text(GTK_LABEL(footer), "Try again");
        (*player)--; //Back on our turn
    }
}

int move(gpointer data) {
    int player = 1;
    int Position = data;
    int win;
    win = checkWin();
    player = (player % 2) ? 1 : 2;
    if (player % 2 == 1) {
        mark = 'X';
    } else {
        mark = '0';
    }

    Foolproof(Position, mark, &player);
    field[Position - 1] = mark;

    player++;
    if (win == 1) {
        if (--player == 1)
            gtk_label_set_text(GTK_LABEL(footer), "Player 1 win!");
        else
            gtk_label_set_text(GTK_LABEL(footer), "Player 2 win!");
        return 0;
    }
    if (win == 0) {
        gtk_label_set_text(GTK_LABEL(footer), "End of the field, Game Over!");
        return 0;
    }

}

void field3x3() {  //Create a tic-tac-toe field  \x1B - color

    /*

    It doesn't work! (╯ ° □ °) ╯ (┻━┻)

    for (int i=0; i<3; i++)
    {
        for (int j=0; j<3; i++)
        {
            Cell = gtk_button_new_with_label(" ");
            g_signal_connect (Cell, "clicked", G_CALLBACK(move), (int)(3*i+j));
            gtk_grid_attach(GTK_GRID(grid), Cell, j, i, 1, 1);
        }
    }
    */

    Cell1 = gtk_button_new_with_label(" ");
    g_signal_connect (Cell1, "button-press-event", G_CALLBACK(move), 1);
    gtk_grid_attach(GTK_GRID(grid), Cell1, 0, 1, 1, 1);

    Cell2 = gtk_button_new_with_label(" ");
    g_signal_connect (Cell2, "button-press-event", G_CALLBACK(move), 2);
    gtk_grid_attach(GTK_GRID(grid), Cell2, 1, 1, 1, 1);

    Cell3 = gtk_button_new_with_label(" ");
    g_signal_connect (Cell3, "button-press-event", G_CALLBACK(move), 3);
    gtk_grid_attach(GTK_GRID(grid), Cell3, 2, 1, 1, 1);

    Cell4 = gtk_button_new_with_label(" ");
    g_signal_connect (Cell4, "button-press-event", G_CALLBACK(move), 4);
    gtk_grid_attach(GTK_GRID(grid), Cell4, 0, 2, 1, 1);

    Cell5 = gtk_button_new_with_label(" ");
    g_signal_connect (Cell5, "button-press-event", G_CALLBACK(move), 5);
    gtk_grid_attach(GTK_GRID(grid), Cell5, 1, 2, 1, 1);

    Cell6 = gtk_button_new_with_label(" ");
    g_signal_connect (Cell6, "button-press-event", G_CALLBACK(move), 6);
    gtk_grid_attach(GTK_GRID(grid), Cell6, 2, 2, 1, 1);

    Cell7 = gtk_button_new_with_label(" ");
    g_signal_connect (Cell7, "button-press-event", G_CALLBACK(move), 7);
    gtk_grid_attach(GTK_GRID(grid), Cell7, 0, 3, 1, 1);

    Cell8 = gtk_button_new_with_label(" ");
    g_signal_connect (Cell8, "button-press-event", G_CALLBACK(move), 8);
    gtk_grid_attach(GTK_GRID(grid), Cell8, 1, 3, 1, 1);

    Cell9 = gtk_button_new_with_label(" ");
    g_signal_connect (Cell9, "button-press-event", G_CALLBACK(move), 9);
    gtk_grid_attach(GTK_GRID(grid), Cell9, 2, 3, 1, 1);

    header = gtk_label_new("Tic-Tac-Toe");
    gtk_grid_attach(GTK_GRID(grid), header, 0, 0, 3, 1);

    footer = gtk_label_new("Game in progress");
    gtk_grid_attach(GTK_GRID(grid), footer, 0, 4, 3, 1);

}


int main(int argc, char **argv) {

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW (window), "Tic Tac Toe");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER (window), 20);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    field3x3();

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}