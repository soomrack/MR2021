#ifndef KRESTIKI_NOLIKI_LIBRARY_H
#define KRESTIKI_NOLIKI_LIBRARY_H

int Human_move(int step, int size, int pole[size][size], int size_for_win, int human_weapon, int bot_weapon);   //Человек

int Bot_move(int step, int size, int pole[size][size], int size_for_win, int bot_weapon, int human_weapon);     //Бот

int check_2(int razmer_for_win, int kr, int nol);

int check(int size, int pole[size][size], int size_for_win);

void syntax(int *a, int *b, int size, int pole[size][size]);

#endif //KRESTIKI_NOLIKI_LIBRARY_H
