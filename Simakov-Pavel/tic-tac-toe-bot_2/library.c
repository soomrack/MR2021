#include "library.h"

#include <stdlib.h>

int bot_move()
{
    int bot_position = rand()%9;
    return bot_position;
}
