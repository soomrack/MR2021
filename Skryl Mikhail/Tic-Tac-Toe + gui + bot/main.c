#include <stdio.h>
#include <gtk/gtk.h>
#include <stdbool.h>
#include "Bot.h"
#include <stdlib.h>

void creating_menu(void);
void start_game(GtkWidget *menu_button1, gpointer data);
void field_making(GtkWidget *window);
void game(void);
void field_change(GtkWidget *button_change, gpointer data);
void win_check(int player_type);
void end_of_the_game(char winner_label[20]);
void button_block(void);
void next_menu(void);
void bot_menu(void);
void bot_turn(void);
void turn_order_menu(gpointer difficulty);

void(*Game_type)(void);
int(*bot_difficulty)(void);

GtkWidget *window;
GtkWidget *table;
GtkWidget *button[9];
char label='X';
char *label_temp="1";
char field_condition[10]="123456789";
int position=0;
bool isPlayer=FALSE;
int count=0;
int count1=0;
int clicked[9]={0,0,0,0,0,0,0,0,0};

int main(int argc, char ** argv) {
    gtk_init(&argc, &argv);
    creating_menu();
    gtk_main();
    return 0;
}

void creating_menu() {
    GtkWidget *vbox;
    GtkWidget *menu_label;
    GtkWidget *menu_button1, *menu_button2;
    window= gtk_window_new(GTK_WINDOW_TOPLEVEL);
    vbox= gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_window_set_title(GTK_WINDOW(window), "Tic-Tac-Toe");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 200);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    menu_label= gtk_label_new("Do you want to play?");
    menu_button1= gtk_button_new_with_label("Play");
    menu_button2= gtk_button_new_with_label("Quit");

    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT(menu_button2), "clicked", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT(menu_button1), "clicked", G_CALLBACK(next_menu), NULL);

    gtk_box_pack_start(GTK_BOX(vbox), menu_label, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(vbox), menu_button1, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(vbox), menu_button2, FALSE, FALSE, 10);

    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_show_all(window);
}

void next_menu() {
    GtkWidget *vbox;
    GtkWidget *next_window;
    GtkWidget *menu_label;
    GtkWidget *menu_button1, *menu_button2;
    next_window= gtk_window_new(GTK_WINDOW_TOPLEVEL);
    vbox= gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_window_set_title(GTK_WINDOW(next_window), "Tic-Tac-Toe");
    gtk_window_set_position(GTK_WINDOW(next_window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(next_window), 400, 200);
    gtk_container_set_border_width(GTK_CONTAINER(next_window), 10);

    menu_label= gtk_label_new("Choose a type of the game");
    menu_button1= gtk_button_new_with_label("Player vs. Player");
    menu_button2= gtk_button_new_with_label("Player vs. Computer");

    g_signal_connect(G_OBJECT(next_window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT(menu_button2), "clicked", G_CALLBACK(bot_menu), (gpointer)(intptr_t) 2);
    g_signal_connect(G_OBJECT(menu_button1), "clicked", G_CALLBACK(start_game), (gpointer)(intptr_t) 1);

    gtk_box_pack_start(GTK_BOX(vbox), menu_label, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(vbox), menu_button1, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(vbox), menu_button2, FALSE, FALSE, 10);

    gtk_container_add(GTK_CONTAINER(next_window), vbox);
    gtk_widget_show_all(next_window);
}

void bot_menu() {
    GtkWidget *vbox;
    GtkWidget *bot_window;
    GtkWidget *menu_label;
    GtkWidget *menu_button1, *menu_button2, *menu_button3;
    bot_window= gtk_window_new(GTK_WINDOW_TOPLEVEL);
    vbox= gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_window_set_title(GTK_WINDOW(bot_window), "Tic-Tac-Toe");
    gtk_window_set_position(GTK_WINDOW(bot_window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(bot_window), 400, 200);
    gtk_container_set_border_width(GTK_CONTAINER(bot_window), 10);

    menu_label= gtk_label_new("Select a difficulty");
    menu_button1= gtk_button_new_with_label("Easy");
    menu_button2= gtk_button_new_with_label("Medium");
    menu_button3= gtk_button_new_with_label("Hard");

    g_signal_connect(G_OBJECT(bot_window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT(menu_button1), "clicked", G_CALLBACK(start_game), (gpointer)(intptr_t) 2);
    g_signal_connect(G_OBJECT(menu_button2), "clicked", G_CALLBACK(start_game), (gpointer)(intptr_t) 3);
    g_signal_connect(G_OBJECT(menu_button3), "clicked", G_CALLBACK(start_game), (gpointer)(intptr_t) 4);

    gtk_box_pack_start(GTK_BOX(vbox), menu_label, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(vbox), menu_button1, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(vbox), menu_button2, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(vbox), menu_button3, FALSE, FALSE, 10);

    gtk_container_add(GTK_CONTAINER(bot_window), vbox);
    gtk_widget_show_all(bot_window);
}

void start_game(GtkWidget *menu_button1, gpointer data) {
    switch ((int)(intptr_t) data) {
        case (1): {
            Game_type=game;
            isPlayer=TRUE;
            break;
        }
        case (2): {
            Game_type=bot_turn;
            bot_difficulty=easy_bot;
            break;
        }
        case (3): {
            Game_type=bot_turn;
            bot_difficulty=medium_bot;
            break;
        }
        case (4): {
            Game_type=bot_turn;
            bot_difficulty=hard_bot;
            break;
        }
    }
    GtkWidget *field_window;
    field_window= gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(field_window),"Let's begin");
    gtk_window_set_position(GTK_WINDOW(field_window),GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(field_window), 400, 400);
    gtk_container_set_border_width(GTK_CONTAINER(field_window), 10);
    field_making(field_window);
    gtk_widget_show_all(field_window);
}

void field_making(GtkWidget *field_window) {
    GtkWidget *grid_button;
    table= gtk_grid_new();
    gtk_grid_set_baseline_row(GTK_GRID(table), 1);
    gtk_grid_set_column_homogeneous(GTK_GRID(table), TRUE);
    gtk_grid_set_row_homogeneous(GTK_GRID(table), TRUE);
    gtk_grid_set_row_baseline_position(GTK_GRID(table), 1, GTK_BASELINE_POSITION_CENTER);
    gtk_grid_set_row_spacing(GTK_GRID(table), 5);
    gtk_grid_set_column_spacing(GTK_GRID(table), 5);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            grid_button= gtk_button_new();
            gtk_grid_attach(GTK_GRID(table), grid_button, j, i, 1, 1);
            gtk_widget_set_halign(table, GTK_ALIGN_CENTER);
            gtk_widget_set_valign(table, GTK_ALIGN_CENTER);
        }
    }
    g_signal_connect(G_OBJECT(field_window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_container_add(GTK_CONTAINER(field_window), table);
    Game_type();
}

void game() {
    int k=0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            button[k] = gtk_grid_get_child_at(GTK_GRID(table), j, i);
            k = k + 1;
        }
    }
    for (int i = 0; i < 9; ++i) {
        if (clicked[i] == 0) {
            g_signal_connect(GTK_BUTTON(button[i]), "clicked", G_CALLBACK(field_change), (gpointer) (intptr_t) i);
            clicked[i]=1;
        }
    }
}

void field_change(GtkWidget *button_change, gpointer data) {
    position=(int)(intptr_t)data + 1;
    field_condition[position - 1] = label;
    gtk_button_set_label(GTK_BUTTON(button_change), &label);
    gtk_widget_set_sensitive(button_change, FALSE);
    if (label  == 'X') {
        label = '0';
    }
    else if (label  == '0') {
        label='X';
    }
    int player=1;
    win_check(player);
}

void bot_turn() {
    position=bot_difficulty();
    int k=0;
    int bot=0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            button[k] = gtk_grid_get_child_at(GTK_GRID(table), j, i);
            k = k + 1;
        }
    }
    printf("%d", position);
    printf("%c", field_condition[position]);
    gtk_button_set_label(GTK_BUTTON(button[position]), &label);
    gtk_widget_set_sensitive(button[position], FALSE);
    if (label  == 'X') {
        label = '0';
    }
    else if (label  == '0') {
        label='X';
    }
    win_check(bot);
}

void win_check(int player_type) {
    bool win = FALSE;
    char winner_announcement[50] = "Winner is  ";
    for (int i = 0; i < 3; ++i) {
        if ((field_condition[3 * i] == field_condition[3 * i + 1])  && (field_condition[3 * i] == field_condition[3 * i + 2])) {
            win = TRUE;
            winner_announcement[11]=field_condition[3*i];
            end_of_the_game(winner_announcement);
        }
        if ((field_condition[i] == field_condition[i + 3]) && (field_condition[i] == field_condition[i + 6])) {
            win = TRUE;
            winner_announcement[11]=field_condition[i];
            end_of_the_game(winner_announcement);
        }
    }
    if ((field_condition[0] == field_condition[4]) && (field_condition[0] == field_condition[8])) {
        win = TRUE;
        winner_announcement[11]=field_condition[0];
        end_of_the_game(winner_announcement);
    }
    if ((field_condition[2] == field_condition[4]) && (field_condition[2] == field_condition[6])) {
        win = TRUE;
        winner_announcement[11]=field_condition[2];
        end_of_the_game(winner_announcement);
    }
    if ((field_condition[0] != '1') && (field_condition[1] != '2') && (field_condition[2] != '3') &&
        (field_condition[3] != '4') && (field_condition[4] != '5') && (field_condition[5] != '6') &&
        (field_condition[6] != '7')  && (field_condition[7] != '8') && (field_condition[8] != '9') && (win == FALSE)) {
        strcpy(winner_announcement, "DRAW!");
        end_of_the_game(winner_announcement);
    }
    if ((player_type == 1) && (win == FALSE) && (isPlayer == FALSE)) {
        bot_turn();
    }
    if ((player_type == 0) && (win == FALSE)) {
        game();
    }
}

void end_of_the_game(char winner_label[20]) {
    button_block();

    GtkWidget *ending_window;
    GtkWidget *ending_button;
    GtkWidget *ending_label;
    GtkWidget *vbox;

    ending_window= gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(ending_window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(ending_window), "Congratulations!");
    gtk_window_set_default_size(GTK_WINDOW(ending_window), 200, 100);
    gtk_container_set_border_width(GTK_CONTAINER(ending_window), 10);
    g_signal_connect(G_OBJECT(ending_window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    ending_label= gtk_label_new(winner_label);
    gtk_label_set_width_chars(GTK_LABEL(ending_label), 12);

    ending_button= gtk_button_new_with_label("OK");
    g_signal_connect(G_OBJECT(ending_button), "clicked", G_CALLBACK(gtk_main_quit), NULL);

    vbox= gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);

    gtk_box_pack_start(GTK_BOX(vbox), ending_label, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(vbox), ending_button, FALSE, FALSE, 10);

    gtk_container_add(GTK_CONTAINER(ending_window), vbox);

    gtk_widget_show_all(ending_window);
}

void button_block() {
    for (int i = 0; i < 9; ++i) {
        gtk_widget_set_sensitive(button[i], FALSE);
    }
}