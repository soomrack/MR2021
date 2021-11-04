#ifndef BOT_BOT_H
#define BOT_BOT_H
#include <gtk/gtk.h>

int Bot_move(int step, int size, int pole[10][10], int size_for_win, int human_weapon, int bot_weapon, GtkWidget *grid);
int end(int size, int pole[10][10], int size_for_win, GtkWidget *grid, int xx, int yy, int bot_weapon);

#endif //BOT_BOT_H
