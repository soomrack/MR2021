#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// size of one of the sides of the field
const int FIELD_SIZE = 3;

// declare state of one cell
typedef enum{
    EMPTY,
    ZERO,
    CROSS
} CellState;

// declare state of field
typedef enum{
    GAME_IS_IN_PROCESS,     // game continues
    WIN,                    // one of the players is win
    TIE                     // tie happens, nobody can win
} FieldState;

// declare struct with player information
typedef struct{
    int player_number;              // number that define the order of players
    char* player_name;              // player name
    CellState player_cell_state;    // cell state in which this player turn the chosen cell in the field
} Player;

typedef struct{
    CellState** cell_state_array;   // states of all cells on the field
    FieldState field_state;         // game stage
    Player* players;                // players
    int current_player;             // which player now is doing a step
} Field;

void init_field(Field* field){

    // filling field with empty values
    field->cell_state_array = calloc(FIELD_SIZE, sizeof(enum CellState*));
    for (int i = 0; i < FIELD_SIZE; i++)
        field->cell_state_array[i] = calloc(FIELD_SIZE, sizeof(enum CellState*));
    for (int i = 0; i < FIELD_SIZE; i++){
        for (int j = 0; j < FIELD_SIZE; j++)
            field->cell_state_array[i][j] = EMPTY;
    }

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

    bool all_cells_are_filled;
    bool horizontal_are_filled;
    bool vertical_are_filled;
    bool diagonal_are_filled;

    // check are all cells not empty
    all_cells_are_filled = true;
    for (int x = 0; x < FIELD_SIZE; x++){
        for (int y = 0; y < FIELD_SIZE; y++){
            if (field->cell_state_array[x][y] == EMPTY) {
                all_cells_are_filled = false;
            }
        }
    }

    // check is any horizontal filled
    for (int y = 0; y < FIELD_SIZE; y++){
        horizontal_are_filled = true;
        for (int x = 0; x < FIELD_SIZE - 1; x++){
            if ((field->cell_state_array[x][y] == EMPTY)||
            (field->cell_state_array[x][y] != field->cell_state_array[x + 1][y])) {
                horizontal_are_filled = false;
            }
        }
        if (horizontal_are_filled)
            break;
    }

    // check is any vertical filled
    for (int x = 0; x < FIELD_SIZE; x++){
        vertical_are_filled = true;
        for (int y = 0; y < FIELD_SIZE - 1; y++){
            if ((field->cell_state_array[x][y] == EMPTY)||
                (field->cell_state_array[x][y] != field->cell_state_array[x][y + 1])) {
                vertical_are_filled = false;
            }
        }
        if (vertical_are_filled)
            break;
    }

    // check is any diagonal filled
    for (int i = 0; i < 2; i++){
        diagonal_are_filled = true;
        for (int j = 0; j < FIELD_SIZE - 1; j++){
            if ((field->cell_state_array[j][abs(j - FIELD_SIZE*i)] == EMPTY)||
            (field->cell_state_array[j][abs(j - FIELD_SIZE*i)] !=
            field->cell_state_array[j + 1][abs(j + 1 - FIELD_SIZE*i)])) {
                diagonal_are_filled = false;
            }
        }
        if (diagonal_are_filled)
            break;
    }
    // conditions to winning
    if (horizontal_are_filled||vertical_are_filled||diagonal_are_filled)
        field->field_state = WIN;

    // conditions to tie
    else if (all_cells_are_filled)
        field->field_state = TIE;
}

int update_field(Field* field, int x, int y){

    // if coordinates is out of the field area, return 1
    if ((x >= FIELD_SIZE)||(y >= FIELD_SIZE))
        return 1;

    // if coordinates has been already filled by someone, return 1
    if (field->cell_state_array[x][y] != EMPTY)
        return 1;

    //
    field->cell_state_array[x][y] = field->players[field->current_player].player_cell_state;

    // check field
    check_field(field);

    // if after checking the game is in progress, change the current player
    if (field->field_state == GAME_IS_IN_PROCESS){
        field->current_player = (field->current_player + 1) % 2;
    }

    // if input was correct, return 0
    return 0;
}

void input_coords(int *x, int *y){
    printf("Write two coordinates through the space: ");
    scanf("%d %d", x, y);
}

void output_game(Field* field){
    putchar('\t');
    for(int x = 0; x < FIELD_SIZE; x++)
        printf("%d  ", x);
    putchar('\n');

    char cell_char;
    for(int y = 0; y < FIELD_SIZE; y++){
        printf("%d\t", y);
        for(int x = 0; x < FIELD_SIZE; x++){
            switch (field->cell_state_array[x][y]){
                case EMPTY:
                    cell_char = '*';
                    break;
                case ZERO:
                    cell_char = '0';
                    break;
                case CROSS:
                    cell_char = 'X';
                    break;
            }
            printf("%c  ", cell_char);
        }
        putchar('\n');
    }
}

void output_input_warning(){
        printf("Input is wrong. Please, try again.");
        printf("\n");
}

void output_result(Field* field){
    // if someone wins, output the name of the winner
    if (field->field_state == WIN)
        printf("%s win!", field->players[field->current_player].player_name);

    // else if it is tie, output correct message
    else if (field->field_state == TIE)
        printf("Tie");
}

int main() {
    Field tic_tac_toe_field;            // declare field
    init_field(&tic_tac_toe_field);     // field inititalization

    int x, y;                           // declare currents coordinates of chosen cell
    int update_result = 0;              // special variable that check validity of chosen coordinates

    output_game(&tic_tac_toe_field);    // the first output of the game field
    while (tic_tac_toe_field.field_state == GAME_IS_IN_PROCESS){

        // if earlier you write wrong coordinates, this code outputs warning message
        if (update_result == 1){
            output_input_warning();
        }

        input_coords(&x, &y);                                       // current coordinates input
        update_result = update_field(&tic_tac_toe_field, x, y);     // update field with chosen coordinates
        output_game(&tic_tac_toe_field);                            // output game field

    }
    output_result(&tic_tac_toe_field);                              // if game is over write its result
    return 0;
}

