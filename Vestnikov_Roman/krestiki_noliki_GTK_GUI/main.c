#include <gtk/gtk.h>
#include <stdio.h>

int check();
int check_2(int kr, int nol);
void congratulation();
void completion();

void closeApp(GtkWidget *window, gpointer data) {
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

/* Функция обработки данных после нажатия кнопки */
void callback(GtkButton *button, gpointer data) {

    step++; //Счётчик ходов

    identifier *id = data;

    if (pole[id->y - 1][id->x - 1] == 0) {      //Заполнение поля при условии пустоты клетки
        if (step % 2 == 1) {
            gtk_button_set_label(button, "X");
            pole[id->y - 1][id->x - 1] = 1;
        } else {
            gtk_button_set_label(button, "0");
            pole[id->y - 1][id->x - 1] = 2;
        }
    } else step--;

    victory = check();
    if (victory == 1 || victory == 2 || victory == 3) {     //Закрытие программы при условии победы или ничьей
        closeApp(G_OBJECT (window), 0);
    }

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

    GtkWidget *button;
    GtkWidget *grid;

    gtk_init (&argc, &argv);
    /* Создаём основное окно программы */
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW (window), "***Tic-Tac-Toe***");
    /* Определяем обработчика сигналов delete_event* для выхода из GTK. */
    g_signal_connect (G_OBJECT(window), "destroy", gtk_main_quit, NULL);
    /* Устанавливаем ширину окантовки окна программы */
    gtk_container_set_border_width(GTK_CONTAINER (window), 10);
    /* Создаём сетку для упаковки виджетов. */
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER (window), grid);
    int x = size;     //Определяем переменные для хранения номера кнопки
    int y = size;
    identifier id[x * y];
    unsigned int counter = 0;
    step = 0;
    for (int i = 1; i <= size; i++) {
        for (int j = 1; j <= size; j++) {
            id[counter].x = i;
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
    gtk_widget_show(grid);
    gtk_widget_show(window);

    /* Входим в gtk_main и ждем событий X сервера для начала выполнения действий! */
    gtk_main();

    congratulation();
    return 0;
}

/* Функция вывода поздравления */
void congratulation()
{
    if (victory == 1) printf("\n\nCongratulations to the cross with the victory!\n");
    if (victory == 2) printf("\n\nCongratulations to the zero with the victory!\n");
    if (victory == 3) printf("\n\nDrawn game!\n");
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

/* Функция проверки на победу/ничью */
int check()
{
    victory = 0;
    int i, j;
    int  kr = 0, nol = 0, c = 0;

    for (i = 0; i < size; i++) { //Проверка по горизонтали
        for (j = 0; j < size - 1; j++) {
            if (kr < size_for_win - 1 && nol < size_for_win - 1) {
                if (pole[i][j] == 1 && pole[i][j + 1] == 1) kr++;
                else kr = 0;
                if (pole[i][j] == 2 && pole[i][j + 1] == 2) nol++;
                else nol = 0;
            }
        }
        victory = check_2(kr, nol);
        if (victory == 1 || victory == 2) break;
        kr = 0;
        nol = 0;
    }

    for (j = 0; j < size; j++) { //Проверка по вертикали
        for (i = 0; i < size - 1; i++) {
            if (kr < size_for_win - 1 && nol < size_for_win - 1) {
                if (pole[i][j] == 1 && pole[i + 1][j] == 1) kr++;
                else kr = 0;
                if (pole[i][j] == 2 && pole[i + 1][j] == 2) nol++;
                else nol = 0;
            }
        }
        victory = check_2(kr, nol);
        if (victory == 1 || victory == 2) break;
        kr = 0;
        nol = 0;
    }

    for (i = 0; i < size - 1; i++) { //Проверка по одной диагонали
        for (j = 0; j < size - 1; j++) {
            if (kr < size_for_win - 1 && nol < size_for_win - 1) {
                if (pole[i][j] == 1 && pole[i + 1][j + 1] == 1) {
                    kr = 1;
                    for (int t = 1; t < size_for_win - 1; t++) {
                        if (pole[i + t][j + t] == 1 && pole[i + t + 1][j + t + 1] == 1) kr++;

                    }
                    if (kr == size_for_win - 1) break;
                } else kr = 0;
                if (pole[i][j] == 2 && pole[i + 1][j + 1] == 2) {
                    nol = 1;
                    for (int t = 1; t < size_for_win - 1; t++) {
                        if (pole[i + t][j + t] == 2 && pole[i + t + 1][j + t + 1] == 2) nol++;
                    }
                    if (nol == size_for_win - 1) break;
                } else nol = 0;
            }
        }
        victory = check_2(kr, nol);
        if (victory == 1 || victory == 2) break;
        kr = 0;
        nol = 0;
    }

    for (i = 0; i < size - 1; i++) { //Проверка по другой диагонали
        for (j = 1; j < size; j++) {
            if (kr < size_for_win - 1 && nol < size_for_win - 1) {
                if (pole[i][j] == 1 && pole[i + 1][j - 1] == 1) {
                    kr = 1;
                    for (int t = 1; t < size_for_win - 1; t++) {
                        if (pole[i + t][j - t] == 1 && pole[i + t + 1][j - t - 1] == 1)
                            kr++;

                    }
                    if (kr == size_for_win - 1) break;
                } else kr = 0;

                if (pole[i][j] == 2 && pole[i + 1][j - 1] == 2) {
                    nol = 1;
                    for (int h = 1; h < size_for_win; h++) {
                        if (pole[i + h][j - h] == 2 && pole[i + h + 1][j - h - 1] == 2) nol++;

                    }
                    if (nol == size_for_win - 1) break;
                } else nol = 0;
            }
        }
        victory = check_2(kr, nol);
        if (victory == 1 || victory == 2) break;
        kr = 0;
        nol = 0;
    }


    for (j = 0; j < size; j++) { //Проверка на ничью
        for (i = 0; i < size; i++) {
            if (pole[i][j] != 0 && victory == 0) c++;
        }
    }
    if (c == size * size) victory = 3;
    return victory;
}

/* Дополнительная функция проверки */
int check_2(int kr, int nol) {
    victory = 0;
    if (size_for_win == 3) {
        if (kr == 2) {
            victory = 1;
        }
        if (nol == 2) {
            victory = 2;
        }
    } else if (size_for_win == 4) {
        if (kr == 3) {
            victory = 1;
        }
        if (nol == 3) {
            victory = 2;
        }
    } else {
        if (kr == 4) {
            victory = 1;
        }
        if (nol == 4) {
            victory = 2;
        }
    }
    return victory;
}