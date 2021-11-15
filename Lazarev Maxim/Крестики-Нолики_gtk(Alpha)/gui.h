#ifndef GUI_H
#define GUI_H
#include <iostream>
#include "gtk_lm.h"
#include "XOHeader.h"
#include "logic.h"

void gui_main ();

void list_to_game1_menu(GtkButton *button, gpointer data);
void list_to_game1_field(GtkButton *button, gpointer data);
void game1(GtkButton *button, gpointer data);

struct DataGame1 {
    MyLabelButton game1_field[3][3];
    DataGame1(MyLabelButton (*game1_field)[3]){
        for (int i = 0; i<3; i++) {
            for (int j = 0; j<3; j++){
                this->game1_field[j][i] = game1_field[j][i];
            }
        }
    }
};

#endif //GUI
