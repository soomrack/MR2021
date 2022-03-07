#include <stdlib.h>
#include <stdbool.h>

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


static bool check_line(Field *field, int x, int y, int step_x, int step_y, int num_of_steps);
static bool check_horizontal_lines(Field *field);
static bool check_vertical_lines(Field *field);
static bool check_diagonal_lines(Field *field);
static bool check_cells_filling(Field *field);


void init_field(Field* field, int field_size){

    // allocate memory for cells array
    field->cell_state_array = calloc(field_size, sizeof(enum CellState*));
    for (int i = 0; i < field_size; i++)
        field->cell_state_array[i] = calloc(field_size, sizeof(enum CellState*));
    // filling field with empty values
    for (int i = 0; i < field_size; i++){
        for (int j = 0; j < field_size; j++)
            field->cell_state_array[i][j] = EMPTY;
    }

    // define field size
    field->field_size = field_size;

    // initially the game continues
    field->field_state = GAME_IS_IN_PROCESS;


    // player 1 information
    field->players[0].player_number = 0;
    field->players[0].player_name = "Player 1";
    field->players[0].player_cell_state = CROSS;

    // player 2 information
    field->players[1].player_number = 1;
    field->players[1].player_name = "Player 2";
    field->players[1].player_cell_state = ZERO;

    // current player
    field->current_player = 0;
}

void check_field(Field* field){

    // check are all cells not empty
    bool all_cells_are_filled = check_cells_filling(field);

    // check is any horizontal filled
    bool horizontal_are_filled = check_horizontal_lines(field);

    // check is any vertical filled
    bool vertical_are_filled = check_vertical_lines(field);

    // check is any diagonal filled
    bool diagonal_are_filled = check_diagonal_lines(field);

    // conditions to winning
    if (horizontal_are_filled || vertical_are_filled || diagonal_are_filled)
        field->field_state = WIN;

        // condition to tie
    else if (all_cells_are_filled)
        field->field_state = TIE;
}

int update_field(Field* field, int x, int y){

    // if coordinates is out of the field area, return 1
    if ((x >= field->field_size) || (y >= field->field_size))
        return 1;

    // if coordinates has been already filled by someone, return 1
    if (field->cell_state_array[x][y] != EMPTY)
        return 1;

    // fill the chosen cell with character of current player
    CellState current_player_cell_state = field->players[field->current_player].player_cell_state;
    field->cell_state_array[x][y] = current_player_cell_state;

    // check field
    check_field(field);

    // if after checking the game is in progress, change the current player
    if (field->field_state == GAME_IS_IN_PROCESS){
        field->current_player = (field->current_player + 1) % 2;
    }

    // if the input was correct, return 0
    return 0;
}

void clear_field(Field *field){

    for (int i = 0; i < field->field_size; i++){
        for (int j = 0; j < field->field_size; j++)
            field->cell_state_array[i][j] = EMPTY;
    }

    field->field_state = GAME_IS_IN_PROCESS;

    field->players[0].player_number = 0;
    field->players[0].player_name = "Player 1";
    field->players[0].player_cell_state = CROSS;

    field->players[1].player_number = 1;
    field->players[1].player_name = "Player 2";
    field->players[1].player_cell_state = ZERO;

    field->current_player = 0;
}


// check one line (horizontal, vertical or diagonal)
// return true if line filled by the same signs
// otherwise return false
static bool check_line(Field *field,
                int x, int y,
                int step_x, int step_y,
                int num_of_steps){
    if (num_of_steps == 0){
        return true;
    }
    bool cell_is_empty = field->cell_state_array[x][y] == EMPTY;

    CellState current_cell_state = field->cell_state_array[x][y];
    CellState next_cell_state = field->cell_state_array[x + step_x][y + step_y];
    bool current_is_not_next = current_cell_state != next_cell_state;

    if (cell_is_empty || current_is_not_next) {
        return false;
    }
    return check_line(field,
                      x + step_x, y + step_y,
                      step_x, step_y,
                      num_of_steps - 1);
}

// true if all cells is not empty
// otherwise false
static bool check_cells_filling(Field *field){

    for (int x = 0; x < field->field_size; x++){
        for (int y = 0; y < field->field_size; y++){
            if (field->cell_state_array[x][y] == EMPTY) {
                return false;
            }
        }
    }
    return true;
}

static bool check_horizontal_lines(Field *field){
    int x = 0;
    int step_x = 1;
    int step_y = 0;
    int num_of_steps = field->field_size - 1;
    for (int y = 0; y < field->field_size; y++){
        if (check_line(field, x, y, step_x, step_y, num_of_steps)) {
            return true;
        }
    }
    return false;
}

static bool check_vertical_lines(Field *field){
    int y = 0;
    int step_x = 0;
    int step_y = 1;
    int num_of_steps = field->field_size - 1;
    for (int x = 0; x < field->field_size; x++){
        if (check_line(field, x, y, step_x, step_y, num_of_steps)) {
            return true;
        }
    }
    return false;
}

static bool check_diagonal_lines(Field *field){

    int x = 0;
    int y = 0;
    int step_x = 1;
    int step_y = 1;
    int num_of_steps = field->field_size - 1;
    if (check_line(field, x, y,
                   step_x, step_y,
                   num_of_steps)) {
        return true;
    }

    x = field->field_size - 1;
    y = 0;
    step_x = -1;
    step_y = 1;
    num_of_steps = field->field_size - 1;
    if (check_line(field, x, y,
                   step_x, step_y,
                   num_of_steps)) {
        return true;
    }
    return false;
}
