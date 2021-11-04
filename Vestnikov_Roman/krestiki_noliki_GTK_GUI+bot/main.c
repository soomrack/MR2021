#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include "check_library.h"
#include "bot.h"

void congratulation();
void completion();
void visual();
int for_win();
static void create_field();
void remove_field();
void callback_button(GtkButton *button, gpointer data);
void closeApp() {
    gtk_main_quit();
}

typedef struct _identifier {
    int x;
    int y;
} identifier;

int human_weapon, bot_weapon;
int choice1, choice2;
int size = 0;
int pole[10][10];
int size_for_win;
int victory = 0;
GtkWidget *window;
int step = 0;
char *winner_announcement;
GtkWidget *label_winner;

identifier id[10 * 10];
GtkWidget *radio_button_player1, *radio_button_player2;
GtkWidget *radio_button_bot1, *radio_button_bot2;
GtkWidget *grid;

int (*Gamer01_move)();

int (*Gamer02_move)();

/* Функция основного процесса игры */
void play() {

    victory = 0;

    for (step = 1; victory != 1 && victory != 2 && victory != 3; step++) {

        switch (choice1) {
            case 1:
                human_weapon = 1;
                bot_weapon = 2;
                break;
            case 2:
                bot_weapon = 1;
                human_weapon = 2;
                break;
            default:
                break;
        }

        victory = Gamer01_move(step, size, pole, size_for_win, human_weapon, bot_weapon, grid);     //Ход крестика
        if (victory == 1 || victory == 3) break;
        /* Выставление нужных позиций боту и игроку */
        switch (choice2) {
            case 1:
                bot_weapon = 1;
                human_weapon = 2;
                break;
            case 2:
                human_weapon = 1;
                bot_weapon = 2;
                break;
            default:
                break;
        }

        victory = Gamer02_move(step, size, pole, size_for_win, human_weapon, bot_weapon, grid);     //Ход нолика
    }
    congratulation();
    gtk_label_set_label((GtkLabel *) label_winner, winner_announcement);
}


int Human_move() { //Крестик
    gtk_main();                                                     //Вход в режим нажатия кнопок
    victory = check(size, pole, size_for_win);
    return victory;
}


/* Функция обработки данных после нажатия кнопки игрового поля */
void callback_button(GtkButton *button, gpointer data) {

    identifier *id_button = data;                                   //Передача данных о координатах

    if (victory != 1 && victory != 2) {                             //Заполнение поля при условии отсутствия победителя
        if (pole[id_button->y - 1][id_button->x - 1] == 0) {        //Заполнение поля при условии пустоты клетки


            if (human_weapon == 1)                                  //Ставит Х
            {
                gtk_button_set_label(button, "X");
                pole[id_button->y - 1][id_button->x - 1] = 1;
            } else if (human_weapon == 2)                           //Ставит 0
            {
                gtk_button_set_label(button, "0");
                pole[id_button->y - 1][id_button->x - 1] = 2;
            }

            victory = check(size, pole, size_for_win);

            gtk_main_quit();
        }
    }
}

/* Функция управления кнопкой сброса/старта */
void callback_reset(GtkButton *button_reset, gpointer data) {
    /* Проверка radiobutton и выставление соответствующих правил игры */
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_button_player1)) == TRUE) {
        Gamer01_move = Human_move;
        choice1 = 1;
    }
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_button_bot1)) == TRUE) {
        Gamer01_move = Bot_move;
        choice1 = 2;
    }

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_button_player2)) == TRUE) {
        Gamer02_move = Human_move;
        choice2 = 1;
    }
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_button_bot2)) == TRUE) {
        Gamer02_move = Bot_move;
        choice2 = 2;
    }

    step = 0;
    victory = 0;
    /* Установка выбранного размера поля */
    const char *size_text = gtk_entry_get_text(GTK_ENTRY((GtkWidget *) data));
    size = atoi(size_text);
    if (size < 3 || size > 10) {
        gtk_label_set_label((GtkLabel *) label_winner, "Sorry, the field can only have a size from 3 to 10");
        return;
    }

    remove_field();
    create_field();

    size_for_win = for_win();

    for (int i = 1; i <= size; i++) {
        for (int j = 1; j <= size; j++) {
            gtk_button_set_label((GtkButton *) gtk_grid_get_child_at((GtkGrid *) grid, i - 1, j - 1), "");
        }
    }
    completion();
    gtk_button_set_label(button_reset, "Reset");

    gtk_label_set_label((GtkLabel *) label_winner, "Good Luck");
    play();
}

/* Функция создания сетки и кнопок в ней */
void create_field() {
    GtkButton *button;
    unsigned int counter = 0;
    step = 0;
    /* Создаём кнопки в соответствии с размерами поля */
    for (int i = 1; i <= size; i++) {
        for (int j = 1; j <= size; j++) {
            id[counter].x = i;      //Передаём данные для определения позиции нажатой кнопки
            id[counter].y = j;
            button = (GtkButton *) gtk_button_new_with_label("");  //Создаём пустую кнопку
            /* Ставим выполнение функции при нажатии на кнопку */
            g_signal_connect (button, "clicked", G_CALLBACK(callback_button), &id[counter]);
            counter++;
            gtk_grid_attach(GTK_GRID (grid), (GtkWidget *) button, i - 1, j - 1, 1, 1);
            gtk_widget_show((GtkWidget *) button);
        }
    }

}

/* Функция удаления сетки по столбцам */
void remove_field() {
    for (int k = 0; k < 11; k++)
        gtk_grid_remove_column((GtkGrid *) grid, 0);
}

/* Функция определения комбинации для победы */
int for_win() {
    if (size == 3) size_for_win = 3;
    else if (size < 8) size_for_win = 4;
    else size_for_win = 5;

    return size_for_win;
}

/* Функция создания игрового поля */
void create_window(int argc, char *argv[]) {

    gtk_init (&argc, &argv);

    /* Создаём основное окно программы */
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW (window), "***Tic-Tac-Toe***");

    /* Определяем обработчика сигналов delete_event* для выхода из GTK. */
    g_signal_connect (G_OBJECT(window), "destroy", gtk_main_quit, NULL);
    gtk_window_set_default_size(GTK_WINDOW(window), 900, 600);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    /* Устанавливаем ширину окантовки окна программы */
    gtk_container_set_border_width(GTK_CONTAINER (window), 10);
    GtkWidget *hbox_main;
    hbox_main = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);


    /* Создаём левую часть экрана */
    GtkWidget *vbox_left, *hbox_gamer1, *hbox_gamer2;
    vbox_left = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *label_player1, *label_player2;
    hbox_gamer1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    label_player1 = gtk_label_new("Gamer 1 →");
    radio_button_player1 = gtk_radio_button_new_with_label(NULL, "Human");
    radio_button_bot1 = gtk_radio_button_new_with_label(
            gtk_radio_button_get_group(GTK_RADIO_BUTTON (radio_button_player1)), "Bot");
    gtk_box_pack_start(GTK_BOX(hbox_gamer1), label_player1, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox_gamer1), radio_button_player1, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox_gamer1), radio_button_bot1, TRUE, FALSE, 0);

    hbox_gamer2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    label_player2 = gtk_label_new("Gamer 2 →");
    radio_button_player2 = gtk_radio_button_new_with_label(NULL, "Human");
    radio_button_bot2 = gtk_radio_button_new_with_label(
            gtk_radio_button_get_group(GTK_RADIO_BUTTON (radio_button_player2)), "Bot");
    gtk_box_pack_start(GTK_BOX(hbox_gamer2), label_player2, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox_gamer2), radio_button_player2, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox_gamer2), radio_button_bot2, TRUE, FALSE, 0);

    gtk_box_pack_start(GTK_BOX(vbox_left), hbox_gamer1, TRUE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(vbox_left), hbox_gamer2, TRUE, FALSE, 10);


    /* Создаём правую часть экрана */
    GtkWidget *vbox_right;
    GtkWidget *size_entry;
    GtkWidget *size_label;
    vbox_right = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    size_label = gtk_label_new("What field size do you want?\n(enter 3 for the standard game): ");
    size_entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox_right), size_label, TRUE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(vbox_right), size_entry, TRUE, FALSE, 10);


    /* Создаём центральную часть экрана */
    GtkWidget *label_name;
    GtkWidget *vbox_center;
    GtkButton *button_reset;
    vbox_center = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    label_name = gtk_label_new("***Tic-Tac-Toe***");
    grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    button_reset = (GtkButton *) gtk_button_new_with_label("Start");
    g_signal_connect (button_reset, "clicked", G_CALLBACK(callback_reset), size_entry);
    label_winner = gtk_label_new("Good Luck");
    gtk_box_pack_start(GTK_BOX(vbox_center), label_name, TRUE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(vbox_center), grid, TRUE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(vbox_center), label_winner, TRUE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(vbox_center), (GtkWidget *) button_reset, TRUE, FALSE, 10);


    gtk_box_pack_start(GTK_BOX(hbox_main), vbox_left, TRUE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(hbox_main), vbox_center, TRUE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(hbox_main), vbox_right, TRUE, FALSE, 10);

    gtk_container_add(GTK_CONTAINER (window), hbox_main);
}

/* Основная функция */
int main(int argc, char *argv[]) {
    create_window(argc, argv);
    gtk_widget_show_all(window);
    /* Входим в gtk_main и ждем событий X сервера для начала выполнения действий! */
    gtk_main();
    return 0;
}

/* Функция вывода поздравления */
void congratulation() {
    if (victory == 1) winner_announcement = "Congratulations to the CROSS with the victory!";
    if (victory == 2) winner_announcement = "Congratulations to the ZERO with the victory!";
    if (victory == 3) winner_announcement = "Drawn game!";
}

/* Функция первоначального заполнения поля пустыми клетками */
void completion() {
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++)
            pole[i][j] = 0;
    }
}

void visual() // Отображает поле (отключено, нужна только для разработки)
{
    for (int t = 0; t < size; t++) printf("==");
    printf("=\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (pole[i][j] == 0) printf("| ");
            if (pole[i][j] == 1) printf("|X");
            if (pole[i][j] == 2) printf("|0");
        }
        printf("| %d\n", i + 1);
        for (int t = 0; t < size; t++) printf("==");
        printf("=\n");
    }
    for (int t = 0; t < size; t++) printf(" %d", t + 1);
    printf("\n");
}
