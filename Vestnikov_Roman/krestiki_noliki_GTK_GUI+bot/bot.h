#ifndef BOT_BOT_H
#define BOT_BOT_H
#include <gtk/gtk.h>
#include "check_library.h"
#include "types.h"

int Bot_move(int step, int size, Cell pole[10][10], int size_for_win, int human_weapon, int bot_weapon, GtkWidget *grid);
int end(int size, Cell pole[10][10], int size_for_win, GtkWidget *grid, int xx, int yy, int bot_weapon);

#endif //BOT_BOT_H
