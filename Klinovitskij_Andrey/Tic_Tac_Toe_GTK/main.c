#include <gtk/gtk.h>
#include <stdio.h>
#include<stdlib.h>

char field[10] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'}; //Field array. X or 0
char *mark = 'X';

int player=0;

int A = 1;
int B = 2;
int C = 3;
int D = 4;
int E = 5;
int F = 6;
int G = 7;
int H = 8;
int J = 9;

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

    if ((field[0] != '1') && (field[1] != '2') && (field[2] != '3') && (field[3] != '4') && (field[4] != '5') &&
        (field[5] != '6') && (field[6] != '7') && (field[7] != '8') && (field[8] != '9'))
        return 0;
    return 2;
}

void Foolproof(int Position) { //Foolproof for mistakes
    char *lable;
    if (mark == 'X') {
        lable = "X";
    } else {
        lable = "0";
    }
    if (Position == 1 && field[0] == '1')
        gtk_button_set_label(GTK_BUTTON(Cell1), lable);
    else if (Position == 2 && field[1] == '2')
        gtk_button_set_label(GTK_BUTTON(Cell2), lable);
    else if (Position == 3 && field[2] == '3')
        gtk_button_set_label(GTK_BUTTON(Cell3), lable);
    else if (Position == 4 && field[3] == '4')
        gtk_button_set_label(GTK_BUTTON(Cell4), lable);
    else if (Position == 5 && field[4] == '5')
        gtk_button_set_label(GTK_BUTTON(Cell5), lable);
    else if (Position == 6 && field[5] == '6')
        gtk_button_set_label(GTK_BUTTON(Cell6), lable);
    else if (Position == 7 && field[6] == '7')
        gtk_button_set_label(GTK_BUTTON(Cell7), lable);
    else if (Position == 8 && field[7] == '8')
        gtk_button_set_label(GTK_BUTTON(Cell8), lable);
    else if (Position == 9 && field[8] == '9')
        gtk_button_set_label(GTK_BUTTON(Cell9), lable);
    else {
        //Motivational message!
        gtk_label_set_text(GTK_LABEL(footer), "Try again");
        (player)--; //Back on our turn
    }
}

int move(GtkWidget *button, gpointer *data) {
    int Position = *data;
    int win;

//////// BUG
    printf("\n\n\n ERROR!!!\n");
    printf("   A = %p \n", &A);
    printf("Data = %p \n", data);
    printf("butt = %p \n", button);

    player = (player % 2) ? 1 : 2;
    if (player % 2 == 1) {
        mark = '0';
    } else {
        mark = 'X';
    }

    Foolproof(Position);
    field[Position - 1] = mark;

    player++;

    win = checkWin();
    if (win == 1) {
        if (--player == 1)
            gtk_label_set_text(GTK_LABEL(footer), "Player 2 win!");
        else
            gtk_label_set_text(GTK_LABEL(footer), "Player 1 win!");
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
    Cell1 = gtk_button_new_with_label("W");
    g_signal_connect(G_OBJECT(Cell1), "clicked", G_CALLBACK(move), &A);
    gtk_grid_attach(GTK_GRID(grid), Cell1, 0, 1, 1, 1);

    Cell2 = gtk_button_new_with_label(" ");
    g_signal_connect (Cell2, "clicked", G_CALLBACK(move), &B);
    gtk_grid_attach(GTK_GRID(grid), Cell2, 1, 1, 1, 1);

    Cell3 = gtk_button_new_with_label(" ");
    g_signal_connect (Cell3, "clicked", G_CALLBACK(move), &C);
    gtk_grid_attach(GTK_GRID(grid), Cell3, 2, 1, 1, 1);

    Cell4 = gtk_button_new_with_label(" ");
    g_signal_connect (Cell4, "clicked", G_CALLBACK(move), &D);
    gtk_grid_attach(GTK_GRID(grid), Cell4, 0, 2, 1, 1);

    Cell5 = gtk_button_new_with_label(" ");
    g_signal_connect (Cell5, "clicked", G_CALLBACK(move), &E);
    gtk_grid_attach(GTK_GRID(grid), Cell5, 1, 2, 1, 1);

    Cell6 = gtk_button_new_with_label(" ");
    g_signal_connect (Cell6, "clicked", G_CALLBACK(move), &F);
    gtk_grid_attach(GTK_GRID(grid), Cell6, 2, 2, 1, 1);

    Cell7 = gtk_button_new_with_label(" ");
    g_signal_connect (Cell7, "clicked", G_CALLBACK(move), &G);
    gtk_grid_attach(GTK_GRID(grid), Cell7, 0, 3, 1, 1);

    Cell8 = gtk_button_new_with_label(" ");
    g_signal_connect (Cell8, "clicked", G_CALLBACK(move), &H);
    gtk_grid_attach(GTK_GRID(grid), Cell8, 1, 3, 1, 1);

    Cell9 = gtk_button_new_with_label(" ");
    g_signal_connect (Cell9, "clicked", G_CALLBACK(move), &J);
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