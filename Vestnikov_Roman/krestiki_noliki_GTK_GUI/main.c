#include <gtk/gtk.h>
#include <stdio.h>
#include "check_library.h"

void congratulation();
void completion();

void closeApp() {
    gtk_main_quit();
}

typedef struct _identifier {
    int x;
    int y;
} identifier;

int size;
int pole[10][10];
int size_for_win;
int victory;
GtkWidget *window;
int step;
char *winner_announcement;
GtkWidget *label_winner;
GtkWidget *grid;

/* Функция обработки данных после нажатия кнопки */
void callback(GtkButton *button, gpointer data) {

    step++; //Счётчик ходов

    identifier *id = data;
if (victory != 1 && victory != 2 ) {            //Заполнение поля при условии отсутствия победителя
    if (pole[id->y - 1][id->x - 1] == 0) {      //Заполнение поля при условии пустоты клетки
        if (step % 2 == 1) {
            gtk_button_set_label(button, "X");
            pole[id->y - 1][id->x - 1] = 1;
        } else {
            gtk_button_set_label(button, "0");
            pole[id->y - 1][id->x - 1] = 2;
        }
    } else step--;
    victory = check(victory, size, pole, size_for_win);
}
    if (victory == 1 || victory == 2 || victory == 3) {     //Объявление победителя при условии победы или ничьей
        //closeApp(G_OBJECT (window), 0);
        congratulation();
        gtk_label_set_label((GtkLabel *) label_winner, winner_announcement);
    }
}

void callback_reset(GtkButton *button_reset, gpointer data) {
    step=0;
    victory=0;
    completion();
    for (int i = 1; i <= size; i++) {
        for (int j = 1; j <= size; j++) {
            gtk_button_set_label((GtkButton *) gtk_grid_get_child_at((GtkGrid *) grid, i - 1, j - 1), "");
        }
    }

    gtk_label_set_label((GtkLabel *) label_winner, "Good Luck");
}

/* Функция определения размеров игрового поля */
int field_size() {
    int word;
    printf("What field size do you want? (enter 3 for the standard game)\n");
    word = scanf("%d", &size);
    while ((word != 1) || size > 10 || size < 3) {
        if (word != 1) scanf("%*s");
        printf("Incorrect input!\n");
        printf("Try again: ");
        word = scanf("%d", &size);
    }
    return size;
}

/* Функция определения комбинации для победы */
int for_win() {
    if (size == 3) size_for_win = 3;
    else if (size < 8) size_for_win = 4;
    else size_for_win = 5;

    return size_for_win;
}

/* Основная функция процесса игры */
int main(int argc, char *argv[]) {

    size = field_size();
    size_for_win = for_win();
    completion();

    /* Тип указателей на виджеты - GtkWidget */

    GtkWidget *button, *button_reset;
    GtkWidget *label_name;
    GtkWidget *vbox;

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

    label_name = gtk_label_new("***Tic-Tac-Toe***");

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    grid = gtk_grid_new();

    int x = size;     //Определяем переменные для хранения номера кнопки
    int y = size;
    identifier id[x * y];
    unsigned int counter = 0;
    step = 0;
    /* Создаём кнопки в соответствии с размерами поля */
    for (int i = 1; i <= size; i++) {
        for (int j = 1; j <= size; j++) {
            id[counter].x = i;      //Передаём данные для определения позиции нажатой кнопки
            id[counter].y = j;
            button = gtk_button_new_with_label("");  //Создаём пустую кнопку
            /* Ставим выполнение функции при нажатии на кнопку */
            g_signal_connect (button, "clicked", G_CALLBACK(callback), &id[counter]);
            counter++;
            gtk_grid_attach(GTK_GRID (grid), button, i - 1, j - 1, 1, 1);
            gtk_widget_show(button);
        }
    }
    /* Показываем сетку и экран */
    gtk_widget_set_halign (grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign (grid, GTK_ALIGN_CENTER);
    /* Создаём кнопку сброса */
    button_reset = gtk_button_new_with_label("Reset");
    g_signal_connect (button_reset, "clicked", G_CALLBACK(callback_reset), NULL);

    label_winner = gtk_label_new("Good Luck");
    /* Упаковываем все виджеты */
    gtk_box_pack_start(GTK_BOX(vbox), label_name, TRUE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(vbox), grid, TRUE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(vbox), grid, TRUE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(vbox), label_winner, TRUE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(vbox), button_reset, TRUE, FALSE, 10);
    gtk_container_add(GTK_CONTAINER (window), vbox);

    gtk_widget_show_all(window);

    /* Входим в gtk_main и ждем событий X сервера для начала выполнения действий! */
    gtk_main();

    return 0;
}

/* Функция вывода поздравления */
void congratulation()
{
    if (victory == 1) winner_announcement = "Congratulations to the CROSS with the victory!";
    if (victory == 2) winner_announcement = "Congratulations to the ZERO with the victory!";
    if (victory == 3) winner_announcement = "Drawn game!";
}

/* Функция первоначального заполнения поля пустыми клетками */
void completion()
{
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++)
            pole[i][j] = 0;
    }
}