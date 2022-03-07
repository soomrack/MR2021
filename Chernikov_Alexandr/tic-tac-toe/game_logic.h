#ifndef TIC_TAC_TOE_GAME_LOGIC_H
#define TIC_TAC_TOE_GAME_LOGIC_H

// #include <stdbool.h>
// state of one cell
typedef enum{
    EMPTY,
    ZERO,
    CROSS
} CellState;

// type of the state of the game field
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

// field information
typedef struct{
    CellState** cell_state_array;   // states of all cells on the field
    int field_size;
    FieldState field_state;         // game stage
    Player players[2];              // array of 2 players info
    int current_player;             // number of which player now is doing a step
} Field;

void init_field(Field* field, int field_size);
void check_field(Field* field);
int update_field(Field* field, int x, int y);
void clear_field(Field *field);

#endif
