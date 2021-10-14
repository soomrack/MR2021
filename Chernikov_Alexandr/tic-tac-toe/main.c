#include <stdio.h>

#include "game_logic.h"
#include "bot.h"

int field_size;

typedef void (*Move) (int*, int*, Field field);

void human_move(int *x, int *y, Field field){
    printf("Write two coordinates (horizontal and vertical) through the space: ");
    scanf("%d %d", x, y);
}

void output_game(Field* field){

    // print horizontal axis
    printf("\t");
    for(int x = 0; x < field_size; x++)
        printf("%d  ", x);
    putchar('\n');

    // print horizontal line
    printf("\t");
    for(int x = 0; x < field_size; x++)
        if (x != field_size - 1)
            printf("___");
        else
            printf("_");
    putchar('\n');

    // print the game field
    char cell_char;
    for(int y = 0; y < field_size; y++){
        printf("%d|\t", y);
        for(int x = 0; x < field_size; x++){
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
        field_size = input;
        *app_state = GAME;
    }
}

Move players_move[2] = {
        human_move,
        bot_move
};

void game(AppState* app_state){
    Field field;                    // declare field
    init_field(&field, field_size); // field inititalization

    int x, y;                           // declare currents coordinates of chosen cell
    int update_result = 0;              // special variable that check validity of chosen coordinates
    Move player_move;

    output_game(&field);    // the first output of the game field
    while (field.field_state == GAME_IS_IN_PROCESS){

        // if earlier you write wrong coordinates, this code outputs warning message
        if (update_result == 1){
            output_input_warning();
        }

        player_move = players_move[field.current_player];

        player_move(&x, &y, field);                     // current coordinates input
        update_result = update_field(&field, x, y);     // update field with chosen coordinates
        output_game(&field);                            // output game field

    }
    output_result(&field);                              // if game is over then write its result
    *app_state = OUTRO;                                 // change application state to outro
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

// declare type of working function
typedef void (*worker) (AppState*);
// create table to align function with their corresponding states
worker FSM_table[4] = {
        [INTRO] = intro,
        [SIZE_INPUT] = size_input,
        [GAME] = game,
        [OUTRO] = outro,
};

int main() {

    // create app_state that show what action is needed now
    AppState app_state = INTRO;

    // While you dont need to exit, define next action by app_state
    while (app_state != EXIT){
        FSM_table[app_state](&app_state);
    }
    return 0;
}

