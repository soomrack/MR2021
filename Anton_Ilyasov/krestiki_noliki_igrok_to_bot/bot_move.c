#include "bot_move.h"
#include <stdlib.h>
#include <string.h>


void bot_move(void)
{
	position_chislo = 0;
	int i = 0;
	position_chislo = 1 + rand() % (size * size);
	if ((field[position_chislo - 1] == 'X') || (field[position_chislo - 1] == 'O'))
	{
		bot_move();
	}
	else
	{
		field[position_chislo - 1] = 'O';
	}
}