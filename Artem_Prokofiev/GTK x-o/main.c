#include <gtk/gtk.h>
#include <stdio.h>
#include <stdbool.h>


char arr[9]={'1','2','3','4','5','6','7','8','9'};

static GtkWidget *Cell1;
static GtkWidget *Cell2;
static GtkWidget *Cell3;
static GtkWidget *Cell4;
static GtkWidget *Cell5;
static GtkWidget *Cell6;
static GtkWidget *Cell7;
static GtkWidget *Cell8;
static GtkWidget *Cell9;
static GtkWidget *indication;
static GtkWidget *end;

bool win() { //check win
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

bool all_cells() { // cells ful
    int counter = 0;
    for (int i = 0; i <= 8; i++) {
        if (arr[i] == 'X' || arr[i] == 'O') {
            counter++;
        }
    }
    if (counter == 9) {
        return true;
    }
    else {
        return false;
    }
}

char player1 = 'X';
char player2 = 'O';
int order=1;

void move(GtkWidget *Cell, gpointer data) {
    int Pos = data;
    if (order %2 != 0) {
        player1 = 'X';
        player2 = 'O';
    }
    if (order %2 == 0) {
        player1 = 'O';
        player2 = 'X';
    }
    if (arr[Pos - 1] == player2) {
        gtk_label_set_text(GTK_LABEL(end), "Oh no, something goes wrong");
        order++;
    }
    if (arr[Pos - 1] != player2) {
        arr[Pos - 1] = player1;
        char buffer1[2];
        snprintf(buffer1, sizeof (buffer1), "%c", player1);
        gtk_button_set_label(GTK_BUTTON(Cell), buffer1);
        order++;
    }
    if (win() == true) {
        gtk_label_set_text(GTK_LABEL(end), "Victory");
    }
    if (all_cells() == true) {
        gtk_label_set_text(GTK_LABEL(end), "Draw");
    }
}

int main (int argc, char **argv) {

    GtkWidget *window, *grid;
    gtk_init(&argc, &argv);

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "X-0");
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

    g_signal_connect (Cell1, "clicked", G_CALLBACK(move), 1);
    g_signal_connect (Cell2, "clicked", G_CALLBACK(move), 2);
    g_signal_connect (Cell3, "clicked", G_CALLBACK(move), 3);
    g_signal_connect (Cell4, "clicked", G_CALLBACK(move), 4);
    g_signal_connect (Cell5, "clicked", G_CALLBACK(move), 5);
    g_signal_connect (Cell6, "clicked", G_CALLBACK(move), 6);
    g_signal_connect (Cell7, "clicked", G_CALLBACK(move), 7);
    g_signal_connect (Cell8, "clicked", G_CALLBACK(move), 8);
    g_signal_connect (Cell9, "clicked", G_CALLBACK(move), 9);

    indication = gtk_label_new ("Your time to move");
    gtk_grid_attach (GTK_GRID(grid), indication, 0, 0, 3, 1);

    end = gtk_label_new ("Not enough");
    gtk_grid_attach (GTK_GRID(grid), end, 0, 4, 3, 1);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}