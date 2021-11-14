#include "gui.h"

void gui_main(){

    MyWindow window("XO");
    window.set_border_width(50);

    MyStack stack;

    MyVBox main_menu;
    MyLabelButton main_menu_labelButton1("Режим \"Игрок против Компьютера\"");
    MyLabelButton main_menu_labelButton2("Режим \"Игрок против Игрока\"");
    main_menu.pack_start(&main_menu_labelButton1);
    main_menu.pack_start(&main_menu_labelButton2);

    MyVBox game1_menu;
    MyLabelButton game1_menu_labelButton1("Play X");
    MyLabelButton game1_menu_labelButton2("Play O");
    game1_menu.pack_start(&game1_menu_labelButton1);
    game1_menu.pack_start(&game1_menu_labelButton2);


    MyHBox game1_line;
    MyVBox game1_column[3];
    MyLabelButton game1_field[3][3];
    DataGame1 dataGame1(game1_field);

    for (int i = 0; i<3; i++){
        game1_line.pack_start(&game1_column[i], TRUE, FALSE, 5);
    }
    for (int i = 0; i<3; i++) {
        for (int j = 0; j<3; j++){
            game1_column[i].pack_start(&game1_field[j][i],TRUE, FALSE, 5);
            game1_field[i][j].set_label(" ");
            game1_field[i][j].set_signal(CLICKED,G_CALLBACK(game1), &dataGame1);
        }
    }


    stack.add_child(&main_menu,"mainMenu");
    stack.add_child(&game1_menu, "game1Menu");
    stack.add_child(&game1_line,"game1Field");
    stack.set_child("mainMenu");


    main_menu_labelButton1.set_signal(CLICKED,G_CALLBACK(list_to_game1_menu), &stack);
    main_menu_labelButton2.set_signal(CLICKED,G_CALLBACK(list_to_game1_menu), &stack);
    game1_menu_labelButton1.set_signal(CLICKED,G_CALLBACK(list_to_game1_field), &stack);
    game1_menu_labelButton2.set_signal(CLICKED,G_CALLBACK(list_to_game1_field), &stack);

    window.add_child(&stack);
    window.show_window();
    gtk_main();
}

void list_to_game1_menu(GtkButton *button, gpointer data) {
    MyStack *a = (MyStack*)data;
    a->set_child("game1Menu");
}

void list_to_game1_field(GtkButton *button, gpointer data){
    MyStack *a = (MyStack*)data;
    a->set_child("game1Field");

    char *ch = (char*)gtk_button_get_label(GTK_BUTTON(button));
    turn = 0;
    if (strcmp(ch,"Play X")==0)
    player1 = X;
    else player1 = O;
}

void game1(GtkButton *button, gpointer data){
    MyLabelButton label_button(button);
    (turn % 2 == 0) ? (playerTurn = X) : (playerTurn = O);
    if (playerTurn == X) {
        label_button.set_label("X");
    }
    else label_button.set_label("O");
    turn++;
}