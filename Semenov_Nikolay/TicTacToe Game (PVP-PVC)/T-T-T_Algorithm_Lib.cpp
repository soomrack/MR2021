#include "T-T-T_Algorithm_Lib.h"

const char X = 'X';
const char O = 'O';
const char EMPTY = ' ';
const char TIE = 'T';
const char NO_ONE = 'N';

void instructions(){
    cout << "  \n";
    cout << "Welcome to the ultimate Tic-Tac-Toe game!\n";
    cout << "--where human brain is pit against silicon processor\n";
    cout << "--or another human brain..\n\n";

    cout << "Make your move known by entering a number, 0 - 8.  The number\n";
    cout << "corresponds to the desired board position, as illustrated:\n\n";

    cout << "       0 | 1 | 2\n";
    cout << "       ---------\n";
    cout << "       3 | 4 | 5\n";
    cout << "       ---------\n";
    cout << "       6 | 7 | 8\n\n";

    cout << "Prepare yourself, human(s).  The battle is about to begin.\n\n";
}

char askYesNo(string question){
    char response;
    do{
        cout << question << " (y/n): ";
        cin >> response;
    }
    while (response != 'y' && response != 'n');
    return response;
}
int askNumber(string question, int high, int low){
    int number;
    do{
        cout << question << " (" << low << " - " << high << "): ";
        cin >> number;
    }
    while (number > high || number < low);
    return number;
}
int askGameType(){
    char gt = askYesNo("Do you want to play Tic-Tac-Toe in PVC mode?");
    if (gt == 'y'){
        cout << "\nYour bravery will be your undoing...   \n";
        return 0;
    }
    else{
        cout << "\nOk.. Maybe, another day. Prepare, humans!\n";
        return 1;
    }
}

char humanPieceC(){
    char go_first = askYesNo("Do you require the first move?");
    if (go_first == 'y'){
        cout << "\nThen take the first move.  You will need it.\n";
        return X;
    }
    else{
        cout << "\nYour bravery will be your undoing... I will go first.\n";
        return O;
    }
}
char humanPieceP(){
    char go_first = askYesNo("Do you require the first move?");
    if (go_first == 'y'){
        cout << "\nThen Player_1 takes the first move. \n";
        return X;
    }
    else{
        cout << "\nThen Player_2 goes first.\n";
        return O;
    }
}
char opponent(char piece){
    if (piece == X){
        return O;
    }
    else{
        return X;
    }
}

void displayBoard(const vector<char>* const pBoard){
    cout << "\n\t" << (*pBoard)[0] << " | " << (*pBoard)[1] << " | " << (*pBoard)[2];
    cout << "\n\t" << "---------";
    cout << "\n\t" << (*pBoard)[3] << " | " << (*pBoard)[4] << " | " << (*pBoard)[5];
    cout << "\n\t" << "---------";
    cout << "\n\t" << (*pBoard)[6] << " | " << (*pBoard)[7] << " | " << (*pBoard)[8];
    cout << "\n\n";
}
char winner(const vector<char>* const pBoard){
    // all possible winning rows
    const int WINNING_ROWS[8][3] = { { 0, 1, 2 },
                                     { 3, 4, 5 },
                                     { 6, 7, 8 },
                                     { 0, 3, 6 },
                                     { 1, 4, 7 },
                                     { 2, 5, 8 },
                                     { 0, 4, 8 },
                                     { 2, 4, 6 } };
    const int TOTAL_ROWS = 8;

    for (int row = 0; row < TOTAL_ROWS; ++row){
        if (((*pBoard)[WINNING_ROWS[row][0]] != EMPTY) &&
            ((*pBoard)[WINNING_ROWS[row][0]] == (*pBoard)[WINNING_ROWS[row][1]]) &&
            ((*pBoard)[WINNING_ROWS[row][1]] == (*pBoard)[WINNING_ROWS[row][2]]))
        {
            return (*pBoard)[WINNING_ROWS[row][0]];
        }
    }
    if (count(pBoard->begin(), pBoard->end(), EMPTY) == 0)
        return TIE;

    return NO_ONE;
}
inline bool isLegal(int move, const vector<char>* pBoard)
{
    return ((*pBoard)[move] == EMPTY);
}

int humanMove(const vector<char>* const pBoard, char human){
    int move = askNumber("Where will you move?", (pBoard->size() - 1));
    while (!isLegal(move, pBoard)){
        cout << "\nThat square is already occupied.\n";
        move = askNumber("Where will you move?", (pBoard->size() - 1));
    }
    cout << "Fine...\n";
    return move;
}
int computerMove(vector<char> board, char computer){
    unsigned int move = 0;
    bool found = false;

    //if computer can win on next move, that’s the move to make
    while (!found && move < board.size()){
        if (isLegal(move, &board)){
            //try move
            board[move] = computer;
            //test for winner
            found = winner(&board) == computer;
            //undo move
            board[move] = EMPTY;
        }

        if (!found){
            ++move;
        }
    }

    //otherwise, if opponent can win on next move, that's the move to make
    if (!found){
        move = 0;
        char human = opponent(computer);
        while (!found && move < board.size()){
            if (isLegal(move, &board)){
                //try move
                board[move] = human;
                //test for winner
                found = winner(&board) == human;
                //undo move
                board[move] = EMPTY;
            }

            if (!found){
                ++move;
            }
        }
    }

    //otherwise, moving to the best open square is the move to make
    if (!found){
        move = 0;
        unsigned int i = 0;

        const int BEST_MOVES[] = { 4, 0, 2, 6, 8, 1, 3, 5, 7 };
        //pick best open square
        while (!found && i <  board.size()){
            move = BEST_MOVES[i];
            if (isLegal(move, &board)){
                found = true;
            }
            ++i;
        }
    }
    cout << "I shall take square number " << move << endl;
    return move;
}

void announceWinnerC(char winner, char computer, char human){
    if (winner == computer){
        cout << winner << "'s won!\n";
        cout << "As I predicted, human, I am triumphant once more -- proof\n";
        cout << "that computers are superior to humans in all regards.\n";
    }
    else if (winner == human){
        cout << winner << "'s won!\n";
        cout << "No, no!  It cannot be!  Somehow you tricked me, human.\n";
        cout << "But never again!  I, the computer, so swear it!\n";
    }
    else{
        cout << "It's a tie.\n";
        cout << "You were most lucky, human, and somehow managed to tie me.\n";
        cout << "Celebrate... for this is the best you will ever achieve.\n";
    }
}
void announceWinnerP(char winner, char human1, char human2){
    if (winner == human1){
        cout << winner << "'s won!\n";
        cout << "Player_1 wins!\n";
    }
    else if (winner == human2){
        cout << winner << "'s won!\n";
        cout << "Player_2 wins!\n";
    }
    else{
        cout << "It's a tie.\n";
    }
}