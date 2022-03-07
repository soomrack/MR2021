#include <iostream>
#include <cstdlib>
#include <ctime>
#include "BotIO.h"
 
int generateRandomField(int (*availableField)[WIDTH]) {
	int k = 0;
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			(field[i][j] == '*') ? (availableField[i][j] = ++k) : (availableField[i][j] = 0);
		}
	}
	return k;
}

void botInput() {
	srand((int)time(0));

	int availableField[HEIGHT][WIDTH];
	int randomRange = generateRandomField(availableField);
	int randomCell;
	randomCell = 1 + (rand() % randomRange);

	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (availableField[i][j] == randomCell) {
				(playerTurn == X) ? (field[i][j] = 'X') : (field[i][j] = '0');
				correctInput = true;
			}
		}
	}

};