#include "T-T-T_Algorithm_Lib.h"
using namespace std;

const char X = 'X';
const char O = 'O';
const char EMPTY = ' ';
const char TIE = 'T';
const char NO_ONE = 'N';

int main(){
    int move;
    const int NUM_SQUARES = 9;
    vector<char> board(NUM_SQUARES, EMPTY);
    instructions();
    int gametype= askGameType();

    if (gametype==0) {
        char human = humanPieceC();
        char computer = opponent(human);
        char turn = X;
        displayBoard(&board);

        while (winner(&board) == NO_ONE) {
            if (turn == human) {
                move = humanMove(&board, human);
                board[move] = human;
            } else {
                move = computerMove(board, computer);
                board[move] = computer;
            }
            displayBoard(&board);
            turn = opponent(turn);
        }
        announceWinnerC(winner(&board), computer, human);
        return 0;
    }
    else if (gametype==1){
        char human1 = humanPieceP();
        char human2 = opponent(human1);
        char turn = X;
        displayBoard(&board);

        while (winner(&board) == NO_ONE) {
            if (turn == human1) {
                move = humanMove(&board, human1);
                board[move] = human1;
            } else {
                move = humanMove(&board, human2);
                board[move] = human2;
            }
            displayBoard(&board);
            turn = opponent(turn);
        }
        announceWinnerP(winner(&board), human1, human2);
        return 0;
    }
}
