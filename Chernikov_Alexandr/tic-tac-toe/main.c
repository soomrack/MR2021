#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// size of one of the sides of the field
int FIELD_SIZE = 3;

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
    FieldState field_state;         // game stage
    Player players[2];                // players
    int current_player;             // which player now is doing a step
} Field;

void init_field(Field* field){

    // allocate memory for cells array
    field->cell_state_array = calloc(FIELD_SIZE, sizeof(enum CellState*));
    for (int i = 0; i < FIELD_SIZE; i++)
        field->cell_state_array[i] = calloc(FIELD_SIZE, sizeof(enum CellState*));
    // filling field with empty values
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
typedef enum{
    HORIZONTAL,
    VERTICAL,
    DIAGONAL
} LINE_TYPE;

bool check_line(Field *field,
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

bool check_cells_filling(Field *field){

    for (int x = 0; x < FIELD_SIZE; x++){
        for (int y = 0; y < FIELD_SIZE; y++){
            if (field->cell_state_array[x][y] == EMPTY) {
                return false;
            }
        }
    }
    return true;
}

bool check_horizontal_lines(Field *field){
    int x = 0;
    int step_x = 1;
    int step_y = 0;
    int num_of_steps = FIELD_SIZE - 1;
    for (int y = 0; y < FIELD_SIZE - 1; y++){
        if (check_line(field, x, y, step_x, step_y, num_of_steps)) {
            return true;
        }
    }
    return false;
}

bool check_vertical_lines(Field *field){
    int y = 0;
    int step_x = 0;
    int step_y = 1;
    int num_of_steps = FIELD_SIZE - 1;
    for (int x = 0; x < FIELD_SIZE - 1; x++){
        if (check_line(field, x, y, step_x, step_y, num_of_steps)) {
            return true;
        }
    }
    return false;
}

bool check_diagonal_lines(Field *field){

    int x = 0;
    int y = 0;
    int step_x = 1;
    int step_y = 1;
    int num_of_steps = FIELD_SIZE - 1;
    if (check_line(field, x, y,
                   step_x, step_y,
                   num_of_steps)) {
        return true;
    }

    x = FIELD_SIZE - 1;
    y = 0;
    step_x = -1;
    step_y = -1;
    num_of_steps = FIELD_SIZE - 1;
    if (check_line(field, x, y,
                   step_x, step_y,
                   num_of_steps)) {
        return true;
    }
    return false;
}

bool check_homogeneous_lines(Field *field, LINE_TYPE line_type){

    int x = 0;
    int y = 0;
    int step_x, step_y;
    int amount_of_lines;

    switch(line_type){
        case HORIZONTAL:
            step_x = 1;
            step_y = 0;
            amount_of_lines = FIELD_SIZE;
            break;
        case VERTICAL:
            step_x = 0;
            step_y = 1;
            amount_of_lines = FIELD_SIZE;
            break;
        case DIAGONAL:
            step_x = 1;
            step_y = 1;
            amount_of_lines = 2;
            break;
        default:
            ;
    }
    for (int i = 0; i < amount_of_lines; i++){
        if (check_line(field, x, y, step_x, step_y, FIELD_SIZE - 1)){
            return true;
        }
        switch(line_type){
            case HORIZONTAL:
                y++;
                break;
            case VERTICAL:
                x++;
                break;
            case DIAGONAL:
                x = FIELD_SIZE - 1;
                step_x = -1;
                step_y = -1;
                break;
            default:
                ;
        }
    }
    return false;
}

void check_field(Field* field){

    // check are all cells not empty
    bool all_cells_are_filled = check_cells_filling(field);

    // check is any horizontal filled
    bool horizontal_are_filled = check_horizontal_lines(field);
    /*
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
    }*/

    // check is any vertical filled
    bool vertical_are_filled = check_vertical_lines(field);
    /*
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
    }*/

    // check is any diagonal filled
    bool diagonal_are_filled = check_diagonal_lines(field);
    /*
    for (int i = 0; i < 2; i++){
        diagonal_are_filled = true;
        for (int j = 0; j < FIELD_SIZE - 1; j++){
            if ((field->cell_state_array[j][abs(j - (FIELD_SIZE-1)*i)] == EMPTY)||
            (field->cell_state_array[j][abs(j - (FIELD_SIZE-1)*i)] !=
            field->cell_state_array[j + 1][abs(j + 1 - (FIELD_SIZE-1)*i)])) {
                diagonal_are_filled = false;
            }
        }
        if (diagonal_are_filled)
            break;
    }*/
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

void input_coords(int *x, int *y){
    printf("Write two coordinates (horizontal and vertical) through the space: ");
    scanf("%d %d", x, y);
}

void output_game(Field* field){

    // print horizontal axis
    printf("\t");
    for(int x = 0; x < FIELD_SIZE; x++)
        printf("%d  ", x);
    putchar('\n');

    // print horizontal line
    printf("\t");
    for(int x = 0; x < FIELD_SIZE; x++)
        if (x != FIELD_SIZE - 1)
            printf("___");
        else
            printf("_");
    putchar('\n');

    // print the game field
    char cell_char;
    for(int y = 0; y < FIELD_SIZE; y++){
        printf("%d|\t", y);
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
    if (field->field_state == WIN){
        char* winner_name = field->players[field->current_player].player_name;
        printf("%s win!\n", winner_name);
    }

    // else if it is tie, output correct message
    else if (field->field_state == TIE)
        printf("Tie\n");
}

void intro(AppState* app_state){
    printf("1 - start the game\n0 - exit\n");

    // input value
    int input;
    scanf("%d", &input);

    // if input is wrong, print warning message and not change app_state
    if ((input != 0)&&(input != 1))
        printf("It seems your input was wrong. Please, try again.\n");
    else
        switch (input) {
        // if input is 1, change app_state to GAME
        case 1:
            *app_state = SIZE_INPUT;
            break;
        // if input is 0, change app_state to EXIT in order to exit the game
        case 0:
            *app_state = EXIT;
                break;
        }
}

void size_input(AppState* app_state){
    printf("Write field size: ");

    int input;
    scanf("%d", &input);

    // if input is wrong, print warning message and not change app_state
    if (input < 2)
        printf("It seems your input was wrong. Please, try again.\n");
    else{
        FIELD_SIZE = input;
        *app_state = GAME;
    }
}

void game(AppState* app_state){
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
    output_result(&tic_tac_toe_field);                              // if game is over then write its result
    *app_state = OUTRO;         // change application state to outro
}

void outro(AppState* app_state){

    printf("Are you want to play one more time?\n");
    printf("1 - yes, 0 - no\n");
    int outro_input;
    scanf("%d", &outro_input);

    // if input was wrong then not change state and repeat outro
    if ((outro_input != 0)&&(outro_input != 1))
        printf("It seems your input was wrong. Please, try again.\n");
    else
        switch (outro_input) {
        // if 1 then return to size input
            case 1:
                *app_state = SIZE_INPUT;
                break;
            // if 0 then exit game
            case 0:
                *app_state = EXIT;
                break;
        }
}

int main() {
    // create array with all possible functions in the application
    void (*op[4])(AppState*);

    op[0] = intro;      // game introduction
    op[1] = size_input; // size input
    op[2] = game;       // game process
    op[3] = outro;      // game outro and an offer to repeat

    // create app_state that show what action is needed now
    AppState app_state = INTRO;

    // While you dont need to exit, define next action by app_state
    while (app_state != EXIT){
        op[app_state](&app_state);
    }
    return 0;
}

