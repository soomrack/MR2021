#include <gtk/gtk.h>
#include <stdio.h>
#include <stdbool.h>

char field[9]={'1','2','3','4','5','6','7','8','9'};
int move_order=1;

char player = 'X';
char opponent = 'O';

static GtkWidget *Cell1;
static GtkWidget *presenter;
static GtkWidget *the_end;

/* проверка выйгрышной комбинации */
bool win() {

    for (int w=0; w<=2; w++) {
        if (field[3*w]==field[3*w+1]&&field[3*w+1]==field[3*w+2]) {
            return true;
        }
        if (field[w]==field[w+3]&&field[w+3]==field[w+6]) {
            return true;
        }
    }

    if ((field[0]==field[4]&&field[4]==field[8])||
        (field[2]==field[4]&&field[4]==field[6])) {
        return true;
    }
    else {
        return false;
    }
}

/* проверка на заполненность поля */
bool end_of_field() {
    int filled_cells = 0;
    for (int e = 0; e <= 8; e ++) {
        if (field[e] == 'X'||field[e] == 'O') {
            filled_cells ++;
        }
    }
    if (filled_cells == 9) {
        return true;
    }
    else {
        return false;
    }
}

void human_move(GtkWidget *Cell, gpointer data) {
    int HumanPos = data;

    if (move_order %2 != 0) {
        player = 'X';
        opponent = 'O';
    }
    if (move_order %2 == 0) {
        player = 'O';
        opponent = 'X';
    }
    if (field[HumanPos - 1] == opponent) {
        gtk_label_set_text(GTK_LABEL(the_end), "Cheater detected, lose a turn!");
        move_order++;
    }
    if (field[HumanPos - 1] != opponent) {
        field[HumanPos - 1] = player;
        char buffer1[2];
        snprintf(buffer1, sizeof (buffer1), "%c", player);
        gtk_button_set_label(GTK_BUTTON(Cell), buffer1);
        move_order++;
    }
    if (win() == true) {
        gtk_label_set_text(GTK_LABEL(the_end), "You win! Game Over!");
    }
    if (end_of_field() == true) {
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
    g_signal_connect (Cell1, "clicked", G_CALLBACK(human_move), 1);
    gtk_grid_attach (GTK_GRID(grid), Cell1, 0, 1, 1, 1);

    Cell1 = gtk_button_new_with_label(" ");
    g_signal_connect (Cell1, "clicked", G_CALLBACK(human_move), 2);
    gtk_grid_attach (GTK_GRID(grid), Cell1, 1, 1, 1, 1);

    Cell1 = gtk_button_new_with_label(" ");
    g_signal_connect (Cell1, "clicked", G_CALLBACK(human_move), 3);
    gtk_grid_attach (GTK_GRID(grid), Cell1, 2, 1, 1, 1);

    Cell1 = gtk_button_new_with_label(" ");
    g_signal_connect (Cell1, "clicked", G_CALLBACK(human_move), 4);
    gtk_grid_attach (GTK_GRID(grid), Cell1, 0, 2, 1, 1);

    Cell1 = gtk_button_new_with_label(" ");
    g_signal_connect (Cell1, "clicked", G_CALLBACK(human_move), 5);
    gtk_grid_attach (GTK_GRID(grid), Cell1, 1, 2, 1, 1);

    Cell1 = gtk_button_new_with_label(" ");
    g_signal_connect (Cell1, "clicked", G_CALLBACK(human_move), 6);
    gtk_grid_attach (GTK_GRID(grid), Cell1, 2, 2, 1, 1);

    Cell1 = gtk_button_new_with_label(" ");
    g_signal_connect (Cell1, "clicked", G_CALLBACK(human_move), 7);
    gtk_grid_attach (GTK_GRID(grid), Cell1, 0, 3, 1, 1);

    Cell1 = gtk_button_new_with_label(" ");
    g_signal_connect (Cell1, "clicked", G_CALLBACK(human_move), 8);
    gtk_grid_attach (GTK_GRID(grid), Cell1, 1, 3, 1, 1);

    Cell1 = gtk_button_new_with_label(" ");
    g_signal_connect (Cell1, "clicked", G_CALLBACK(human_move), 9);
    gtk_grid_attach (GTK_GRID(grid), Cell1, 2, 3, 1, 1);

    presenter = gtk_label_new ("It's your move");
    gtk_grid_attach (GTK_GRID(grid), presenter, 0, 0, 3, 1);

    the_end = gtk_label_new ("well, it's not enough");
    gtk_grid_attach (GTK_GRID(grid), the_end, 0, 4, 3, 1);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}