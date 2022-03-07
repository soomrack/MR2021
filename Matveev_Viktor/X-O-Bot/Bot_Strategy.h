// Bot_Strategy.h : включаемый файл для стандартных системных включаемых файлов
// или включаемые файлы для конкретного проекта.

#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef BOT_STRATEGY
#define BOT_STRATEGY

void rand_move(char ind1, char ind2);
void something_smart(char ind_arr[9], char ind1, char ind2, char ind3);

void bot_easy(char ind1, char ind2);

void bot_hard(char ind1, char ind2);

#endif
// TODO: установите здесь ссылки на дополнительные заголовки, требующиеся для программы.
