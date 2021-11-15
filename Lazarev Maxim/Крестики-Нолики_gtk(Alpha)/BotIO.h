#include "XOHeader.h"
#include "gtk_lm.h"
#ifndef BOTIO_H
#define BOTIO_H

int generateRandomField(MyLabelButton (*game1_field)[3],int (*availableField)[WIDTH]);
void botInput(MyLabelButton (*field)[3]);
void playerInput(MyLabelButton (*field)[3],MyLabelButton pressed_button);

bool checkWin(MyLabelButton (*field)[3]);
bool checkDraw(MyLabelButton (*field)[3]);

#endif // !BOTIO_H
