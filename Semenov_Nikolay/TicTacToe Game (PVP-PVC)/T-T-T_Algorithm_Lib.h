#ifndef T_T_T_ALGORITHM_LIB_T_T_T_ALGORITHM_LIB_H
#define T_T_T_ALGORITHM_LIB_T_T_T_ALGORITHM_LIB_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void instructions();
char askYesNo(string question);
int askNumber(string question, int high, int low = 0);
int askGameType();
char humanPieceC();
char humanPieceP();
char opponent(char piece);
void displayBoard(const vector<char>* const pBoard);
char winner(const vector<char>* const pBoard);
bool isLegal(const vector<char>* const pBoard, int move);
int humanMove(const vector<char>* const pBoard, char human);
int computerMove(vector<char> board, char computer);
void announceWinnerC(char winner, char computer, char human);
void announceWinnerP(char winner, char human1, char human2);

#endif //T_T_T_ALGORITHM_LIB_T_T_T_ALGORITHM_LIB_H
