#ifndef TIC_TAC_TOE_GAME_LOGIC_H
#define TIC_TAC_TOE_GAME_LOGIC_H

#include <stdbool.h>

// size of one of the sides of the field

// state of one cell
typedef enum{
    EMPTY,
    ZERO,
    CROSS
} CellState;

typedef enum{
    INTRO,
    SIZE_INPUT,
    GAME,
    OUTRO,
    EXIT,
} AppState;

// state of field
typedef enum{
    GAME_IS_IN_PROCESS,     // game continues
    WIN,                    // one of the players is win
    TIE                     // tie happens, nobody can win
} FieldState;


// struct with player information
typedef struct{
    int player_number;              // number that defines the order of players
    char* player_name;              // player name
    CellState player_cell_state;    // cell state in which this player turn the chosen cell in the field
} Player;

typedef struct{
    CellState** cell_state_array;   // states of all cells on the field
    int field_size;
    FieldState field_state;         // game stage
    Player players[2];              // players
    int current_player;             // which player now is doing a step
} Field;

void init_field(Field* field, int field_size);

void check_field(Field* field);

int update_field(Field* field, int x, int y);

#endif
