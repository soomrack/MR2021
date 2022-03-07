#include <gtk/gtk.h>
#include <stdbool.h>
#include<stdlib.h>

char field[10]="123456789";
char *player1mk="X";
char *player2mk="O";

int movecnt = 1;

static GtkWidget *window;
static GtkWidget *Cell1;
static GtkWidget *Cell2;
static GtkWidget *Cell3;
static GtkWidget *Cell4;
static GtkWidget *Cell5;
static GtkWidget *Cell6;
static GtkWidget *Cell7;
static GtkWidget *Cell8;
static GtkWidget *Cell9;
static GtkWidget *label;
static GtkWidget *grid;

//проверка на выигрыш
bool checkwin(){
    for (int i=0;i<3;i++) {
        if (field[i]==field[i+3]&&field[i+6]==field[i+3]) //проверка линий
            return true;
        if (field[3*i]==field[3*i+1]&&field[3*i]==field[3*i+2])
            return true;
    }
    if (field[0]==field[4]&&field[8]==field[4]) //проверка диагоналей
        return true;
    if (field[2]==field[4]&&field[6]==field[4])
        return true;
    return false;
}

// проверка, заполнена ли выбранная ячейка
bool cellcheck(pos){
    if (field[pos-1]=='X'||field[pos-1]=='O')
        return true;
    else return false;
}

// ход игрока
void move(GtkWidget *Cell, gpointer data) {
    int pos=0;
    pos=atoi(data);
    if (cellcheck(pos)==false&&checkwin()==false){
        if (movecnt % 2 == 1){
            gtk_button_set_label(GTK_BUTTON(Cell), player1mk);
            field[pos-1]='X';
            movecnt++;
            if(checkwin()==true){
                gtk_label_set_text(GTK_LABEL(label), "Игрок 1 победил!");
            }
        }
        else{
            gtk_button_set_label(GTK_BUTTON(Cell), player2mk);
            field[pos-1]='O';
            movecnt++;
            if(checkwin()==true){
                gtk_label_set_text(GTK_LABEL(label), "Игрок 2 победил!");
            }
        }
        if (movecnt>9&&checkwin()==false)
            gtk_label_set_text(GTK_LABEL(label), "Ничья!");
    }

}
int main(int argc, char **argv) {

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW (window), "Крестики-нолики");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER (window), 20);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    Cell1 = gtk_button_new_with_label(" ");
    g_signal_connect(Cell1, "clicked", G_CALLBACK(move), "1");
    gtk_grid_attach(GTK_GRID(grid), Cell1, 0, 1, 1, 1);

    Cell2 = gtk_button_new_with_label(" ");
    g_signal_connect (Cell2, "clicked", G_CALLBACK(move), "2");
    gtk_grid_attach(GTK_GRID(grid), Cell2, 1, 1, 1, 1);

    Cell3 = gtk_button_new_with_label(" ");
    g_signal_connect (Cell3, "clicked", G_CALLBACK(move), "3");
    gtk_grid_attach(GTK_GRID(grid), Cell3, 2, 1, 1, 1);

    Cell4 = gtk_button_new_with_label(" ");
    g_signal_connect (Cell4, "clicked", G_CALLBACK(move), "4");
    gtk_grid_attach(GTK_GRID(grid), Cell4, 0, 2, 1, 1);

    Cell5 = gtk_button_new_with_label(" ");
    g_signal_connect (Cell5, "clicked", G_CALLBACK(move), "5");
    gtk_grid_attach(GTK_GRID(grid), Cell5, 1, 2, 1, 1);

    Cell6 = gtk_button_new_with_label(" ");
    g_signal_connect (Cell6, "clicked", G_CALLBACK(move), "6");
    gtk_grid_attach(GTK_GRID(grid), Cell6, 2, 2, 1, 1);

    Cell7 = gtk_button_new_with_label(" ");
    g_signal_connect (Cell7, "clicked", G_CALLBACK(move), "7");
    gtk_grid_attach(GTK_GRID(grid), Cell7, 0, 3, 1, 1);

    Cell8 = gtk_button_new_with_label(" ");
    g_signal_connect (Cell8, "clicked", G_CALLBACK(move), "8");
    gtk_grid_attach(GTK_GRID(grid), Cell8, 1, 3, 1, 1);

    Cell9 = gtk_button_new_with_label(" ");
    g_signal_connect (Cell9, "clicked", G_CALLBACK(move), "9");
    gtk_grid_attach(GTK_GRID(grid), Cell9, 2, 3, 1, 1);

    label = gtk_label_new("Игра продолжается...");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 4, 3, 1);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}