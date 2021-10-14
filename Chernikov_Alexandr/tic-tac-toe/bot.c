#include "game_logic.h"

const int MAX_DEPTH = 5;    // max num of players move which is considered by bot

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

/* Implementation of algorithm "minimax" (with alpha beta)
 *
 * It's a recursive algorithm which evaluate move profitability.
 * Return 0 when the game ends with tie.
 * Return depth or -depth (depends on player's number),
 * if winning is occured on depth-1 move
 * */
int minimax(Field field, int depth, int alpha, int beta){
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
        if (beta <= alpha)
            break;
        for (int y = 0; y < field.field_size; y++){

            if (field.cell_state_array[x][y] == EMPTY){
                CellState cell_state = field.players[field.current_player].player_cell_state;
                field.cell_state_array[x][y] = cell_state;
                if (field.current_player == 0){
                    eval = max(eval, minimax(field, depth - 1, alpha, beta));
                    alpha = max(alpha, eval);
                }
                else{
                    eval = min(eval, minimax(field, depth - 1, alpha, beta));
                    beta = min(beta, eval);
                }
                field.cell_state_array[x][y] = EMPTY;
            }

        }
    }

    return eval;
}

// function for bot's game move
void bot_move(int *x, int *y, Field field){
    int best_eval;
    int new_eval;

    int alpha = -MAX_DEPTH;
    int beta = MAX_DEPTH;

    if (field.current_player == 0)
        best_eval = -MAX_DEPTH;
    else
        best_eval = MAX_DEPTH;

    // checking all cells in the nested cycle
    for (int i = 0; i < field.field_size; i++) {
        for (int j = 0; j < field.field_size; j++) {

            // if current cell is empty then evaluate it's profitability for move
            if (field.cell_state_array[i][j] == EMPTY) {
                // filling the cell with correct sign and get eval
                CellState cell_state = field.players[field.current_player].player_cell_state;
                field.cell_state_array[i][j] = cell_state;
                new_eval = minimax(field, MAX_DEPTH, alpha, beta);

                // find coords with the best eval
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
                // empty the cell for another checking
                field.cell_state_array[i][j] = EMPTY;
            }
        }
    }
}
