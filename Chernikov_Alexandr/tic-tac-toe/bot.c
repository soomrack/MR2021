#include "game_logic.h"

const int MAX_DEPTH = 5;

int max(int a, int b){
    if (a > b){
        return a;
    }
    return b;
}

int min(int a, int b){
    if (a < b){
        return a;
    }
    return b;
}

int minimax(Field field, int depth){
    check_field(&field);
    if (depth == 0 || field.field_state == TIE)
        return 0;
    if (field.field_state == WIN){
        if (field.current_player == 0)
            return depth;
        else
            return -depth;
    }

    field.current_player = (field.current_player + 1) % 2;

    int eval;
    if (field.current_player == 0)
        eval = -depth;
    else
        eval = depth;

    for (int x = 0; x < field.field_size; x++){
        for (int y = 0; y < field.field_size; y++){

            if (field.cell_state_array[x][y] == EMPTY){
                CellState cell_state = field.players[field.current_player].player_cell_state;
                field.cell_state_array[x][y] = cell_state;
                if (field.current_player == 0)
                    eval = max(eval, minimax(field, depth - 1));
                else
                    eval = min(eval, minimax(field, depth - 1));
                field.cell_state_array[x][y] = EMPTY;
            }

        }
    }

    return eval;
}

void bot_move(int *x, int *y, Field field){
    int best_eval;
    int new_eval;

    if (field.current_player == 0)
        best_eval = -MAX_DEPTH;
    else
        best_eval = MAX_DEPTH;


    for (int i = 0; i < field.field_size; i++) {
        for (int j = 0; j < field.field_size; j++) {

            if (field.cell_state_array[i][j] == EMPTY) {
                CellState cell_state = field.players[field.current_player].player_cell_state;
                field.cell_state_array[i][j] = cell_state;
                new_eval = minimax(field, MAX_DEPTH);

                if (field.current_player == 0) {
                    if (new_eval > best_eval) {
                        best_eval = new_eval;
                        *x = i;
                        *y = j;
                    }
                }
                else {
                    if (new_eval < best_eval) {
                        best_eval = new_eval;
                        *x = i;
                        *y = j;
                    }
                }
                field.cell_state_array[i][j] = EMPTY;
            }
        }
    }
}
