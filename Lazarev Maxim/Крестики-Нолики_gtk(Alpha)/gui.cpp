#include "gui.h"

void gui_main(){

    MyWindow window("XO");
    window.set_border_width(50);

    MyStack stack;

    MyVBox menu(10);
    MyLabelButton labelButton1("Режим \"Игрок против Компьютера\"");
    MyLabelButton labelButton2("Режим \"Игрок против Игрока\"");
    menu.pack_start(&labelButton1, TRUE, FALSE, 5);
    menu.pack_start(&labelButton2,TRUE, FALSE, 5);

    MyHBox game1(10);
    MyVBox column[3];
    MyLabelButton field[3][3];

    for (int i = 0; i<3; i++){
        game1.pack_start(&column[i], TRUE, FALSE, 5);
    }
    for (int i = 0; i<3; i++) {
        for (int j = 0; j<3; j++){
            column[i].pack_start(&field[i][j],TRUE, FALSE, 5);
        }
    }

    stack.add_child(&menu,"Menu");
    stack.add_child(&game1,"Game1");
    stack.set_child("Menu");


    labelButton1.set_signal(CLICKED,G_CALLBACK(list_to_game_plVSbot), &stack);
    labelButton2.set_signal(CLICKED,G_CALLBACK(list_to_game_plVSbot), &stack);

    window.add_child(&stack);
    window.show_window();
    gtk_main();
}

void list_to_game_plVSbot(GtkButton *button, gpointer data) {
    MyStack *a = (MyStack*)data;
    a->set_child("Game1");
}
