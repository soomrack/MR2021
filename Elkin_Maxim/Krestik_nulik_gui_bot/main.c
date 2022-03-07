#include <gtk/gtk.h>
#include <stdio.h>
#include <stdbool.h>
#include "BotXO.h"

/*working variables*/
int move_order = 1;
char field[9]={'1','2','3','4','5','6','7','8','9'};
int pos = 0;
char buffer_cell_value[2];

/* widgets for gtk*/
static GtkWidget *Cell1, *Cell2, *Cell3,
                 *Cell4, *Cell5, *Cell6,
                 *Cell7, *Cell8, *Cell9,
                 *bot_first, *reset;
static GtkWidget *presenter;
static GtkWidget *the_end;

/* functors*/

int (*gameplay) (GtkWidget *Cell, gpointer data);
void (*gamer01_move) (char p1, char p2);
void (*gamer02_move) (char p1, char p2);

/* checks win combo */
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

/* checks filling of the field */
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
    switch (pos) {
        case 0:
            gtk_button_set_label(GTK_BUTTON(Cell1), buffer_cell_value);
            break;
        case 1:
            gtk_button_set_label(GTK_BUTTON(Cell2), buffer_cell_value);
            break;
        case 2:
            gtk_button_set_label(GTK_BUTTON(Cell3), buffer_cell_value);
            break;
        case 3:
            gtk_button_set_label(GTK_BUTTON(Cell4), buffer_cell_value);
            break;
        case 4:
            gtk_button_set_label(GTK_BUTTON(Cell5), buffer_cell_value);
            break;
        case 5:
            gtk_button_set_label(GTK_BUTTON(Cell6), buffer_cell_value);
            break;
        case 6:
            gtk_button_set_label(GTK_BUTTON(Cell7), buffer_cell_value);
            break;
        case 7:
            gtk_button_set_label(GTK_BUTTON(Cell8), buffer_cell_value);
            break;
        case 8:
            gtk_button_set_label(GTK_BUTTON(Cell9), buffer_cell_value);
            break;
    }
}

/* function starts, when player allows bot make first move*/
void bot_first_move () {
    write_bot_choice();
    gtk_widget_set_sensitive(bot_first, FALSE);
}

void disable_field () {
    gtk_widget_set_sensitive(Cell1, FALSE);
    gtk_widget_set_sensitive(Cell2, FALSE);
    gtk_widget_set_sensitive(Cell3, FALSE);
    gtk_widget_set_sensitive(Cell4, FALSE);
    gtk_widget_set_sensitive(Cell5, FALSE);
    gtk_widget_set_sensitive(Cell6, FALSE);
    gtk_widget_set_sensitive(Cell7, FALSE);
    gtk_widget_set_sensitive(Cell8, FALSE);
    gtk_widget_set_sensitive(Cell9, FALSE);
}

void enable_field () {
    gtk_widget_set_sensitive(Cell1, TRUE);
    gtk_widget_set_sensitive(Cell2, TRUE);
    gtk_widget_set_sensitive(Cell3, TRUE);
    gtk_widget_set_sensitive(Cell4, TRUE);
    gtk_widget_set_sensitive(Cell5, TRUE);
    gtk_widget_set_sensitive(Cell6, TRUE);
    gtk_widget_set_sensitive(Cell7, TRUE);
    gtk_widget_set_sensitive(Cell8, TRUE);
    gtk_widget_set_sensitive(Cell9, TRUE);
}

/* clears field */
void reset_func (GtkWidget *reset, gpointer data) {
    move_order =1;
    for (int i=0; i<=8; i++) {
        field[i]= i+'0';
    }
    gtk_button_set_label(GTK_BUTTON(Cell1), " ");
    gtk_button_set_label(GTK_BUTTON(Cell2), " ");
    gtk_button_set_label(GTK_BUTTON(Cell3), " ");
    gtk_button_set_label(GTK_BUTTON(Cell4), " ");
    gtk_button_set_label(GTK_BUTTON(Cell5), " ");
    gtk_button_set_label(GTK_BUTTON(Cell6), " ");
    gtk_button_set_label(GTK_BUTTON(Cell7), " ");
    gtk_button_set_label(GTK_BUTTON(Cell8), " ");
    gtk_button_set_label(GTK_BUTTON(Cell9), " ");
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

/* multiplayer gameplay scenario */
int gameplay_mp(GtkWidget *Cell, gpointer data) {

    pos = (int)(intptr_t)data;
    if (move_order%2 != 0) {
        gamer01_move('X', 'O');
        gtk_button_set_label(GTK_BUTTON(Cell), buffer_cell_value);
        if (win() == true) {
            gtk_label_set_text(GTK_LABEL(the_end), "X win! Game Over!");
            disable_field();
        };
    }
    if (move_order%2 == 0) {
        gamer01_move('O', 'X');
        gtk_button_set_label(GTK_BUTTON(Cell), buffer_cell_value);
        if (win() == true) {
            gtk_label_set_text(GTK_LABEL(the_end), "O win! Game Over!");
            disable_field();
        }
    }
    if ((end_of_field() == true) && (win()!=true)) {
        gtk_label_set_text(GTK_LABEL(the_end), "End of the field, Game Over!");
    }
    move_order++;
}

/* gameplay with bot scenario */
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

/* initials gtk window with gui of the game */
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

    Cell1 = gtk_button_new_with_label(" ");
    g_signal_connect (Cell1, "clicked",
                      G_CALLBACK(gameplay), (gpointer)(intptr_t)(1));
    gtk_grid_attach (GTK_GRID(grid), Cell1, 0, 1, 1, 1);

    Cell2 = gtk_button_new_with_label(" ");
    g_signal_connect (Cell2, "clicked",
                      G_CALLBACK(gameplay), (gpointer)(intptr_t)(2));
    gtk_grid_attach (GTK_GRID(grid), Cell2, 1, 1, 1, 1);

    Cell3 = gtk_button_new_with_label(" ");
    g_signal_connect (Cell3, "clicked",
                      G_CALLBACK(gameplay), (gpointer)(intptr_t)(3));
    gtk_grid_attach (GTK_GRID(grid), Cell3, 2, 1, 1, 1);

    Cell4 = gtk_button_new_with_label(" ");
    g_signal_connect (Cell4, "clicked",
                      G_CALLBACK(gameplay), (gpointer)(intptr_t)(4));
    gtk_grid_attach (GTK_GRID(grid), Cell4, 0, 2, 1, 1);

    Cell5 = gtk_button_new_with_label(" ");
    g_signal_connect (Cell5, "clicked",
                      G_CALLBACK(gameplay), (gpointer)(intptr_t)(5));
    gtk_grid_attach (GTK_GRID(grid), Cell5, 1, 2, 1, 1);

    Cell6 = gtk_button_new_with_label(" ");
    g_signal_connect (Cell6, "clicked",
                      G_CALLBACK(gameplay), (gpointer)(intptr_t)(6));
    gtk_grid_attach (GTK_GRID(grid), Cell6, 2, 2, 1, 1);

    Cell7 = gtk_button_new_with_label(" ");
    g_signal_connect (Cell7, "clicked",
                      G_CALLBACK(gameplay), (gpointer)(intptr_t)(7));
    gtk_grid_attach (GTK_GRID(grid), Cell7, 0, 3, 1, 1);

    Cell8 = gtk_button_new_with_label(" ");
    g_signal_connect (Cell8, "clicked",
                      G_CALLBACK(gameplay), (gpointer)(intptr_t)(8));
    gtk_grid_attach (GTK_GRID(grid), Cell8, 1, 3, 1, 1);

    Cell9 = gtk_button_new_with_label(" ");
    g_signal_connect (Cell9, "clicked",
                      G_CALLBACK(gameplay), (gpointer)(intptr_t)(9));
    gtk_grid_attach (GTK_GRID(grid), Cell9, 2, 3, 1, 1);

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
    if (gameplay == gameplay_mp) {
        gtk_widget_hide(bot_first);
    }
    gtk_main();
}

/* defines game mode */
void start_screen() {
    int game_mode;
    int difficulty;
    printf("   Welcome to the Tic-Tac-Toe game\n"
           "   Select the type of a game\n"
           "   1 - Single Player\n"
           "   2 - Multiplayer\n");
    scanf("%d", &game_mode);
    switch (game_mode) {
        case 1:
            gameplay = gameplay_bot;
            gamer01_move=human_move;
            printf("   Select a difficulty level\n"
                   "   1 - Easy\n"
                   "   2 - Medium\n"
                   "   3 - Hard\n");
            scanf("%d", &difficulty);
            switch (difficulty) {
                case 1:
                    gamer02_move=bot_easy;
                    break;
                case 2:
                    gamer02_move= bot_medium;
                    break;
                case 3:
                    gamer02_move= bot_hard;
                    break;
                default:
                    printf("something went wrong");
                }
                break;
        case 2:
            gameplay = gameplay_mp;
            gamer01_move=human_move;
            gamer02_move=human_move;
            break;
        default:
            printf("something went wrong\n");
    }
}

int main (int argc, char **argv) {
    start_screen();
    pole(argc, argv);
    return 0;
}