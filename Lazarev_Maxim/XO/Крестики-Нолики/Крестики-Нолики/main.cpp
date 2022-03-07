#include <iostream>
#include "BotIO.h"
#include "XOHeader.h"

using namespace std;

void chooseMode();
void Setup();
void Input();
void Logic();
void Draw();
void Instruction();
bool checkWin();
bool checkDraw();

void (*game)();
void gamePlayerVsBot();
void gamePlayerVsPlayer();


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
	Setup();

	while (1) {
		game();
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void chooseMode() {
	cout << "Пожалуйста, выбирите режим игры!"<<endl;
	cout << "Для режима Игрок против Компьютера введите '1'." << endl;
	cout << "Для режима Игрок против Игрока введите '2'." << endl;
	cout << "Ввод: ";
	cin >> input;
	cout << endl;

	switch (input)
	{
	default:
		chooseMode();
		break;
	case('1'):
		gameMode = PlayerVsBot;
		game = gamePlayerVsBot;
		break;
	case('2'):
		gameMode = PlayerVsPlayer;
		game = gamePlayerVsPlayer;
		break;
	case('3'):
		gameMode = BotVsBot;
		break;
	}

}

void Setup() {																						//Установка настроек по умолчанию
	chooseMode();
	playerTurn = X;
	turn = 0;
	gameStatus = "Игра не окончена";

	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			field[i][j] = '*';
		}
	}
}

void Input() {
	cout << "Ввод: ";
	cin  >> input;
	switch (input) {
	default:
		correctInput = false;
		break;

	case ('o'):
		correctInput = true;
		exit(0);
		break;

	case ('q'):
		if (field[0][0] == '*') {
			(playerTurn == X) ? (field[0][0] = 'X') : (field[0][0] = '0');
			correctInput = true;
		}
		else correctInput = false;
		break;

	case ('w'):
		if (field[0][1] == '*') {
			(playerTurn == X) ? (field[0][1] = 'X') : (field[0][1] = '0');
			correctInput = true;
		}
		else correctInput = false;
		break;

	case ('e'):
		if (field[0][2] == '*') {
			(playerTurn == X) ? (field[0][2] = 'X') : (field[0][2] = '0');
			correctInput = true;
		}
		else correctInput = false;
		break;

	case ('a'):
		if (field[1][0] == '*') {
			(playerTurn == X) ? (field[1][0] = 'X') : (field[1][0] = '0');
			correctInput = true;
		}
		else correctInput = false;
		break;

	case ('s'):
		if (field[1][1] == '*') {
			(playerTurn == X) ? (field[1][1] = 'X') : (field[1][1] = '0');
			correctInput = true;
		}
		else correctInput = false;
		break;

	case ('d'):
		if (field[1][2] == '*') {
			(playerTurn == X) ? (field[1][2] = 'X') : (field[1][2] = '0');
			correctInput = true;
		}
		else correctInput = false;
		break;

	case ('z'):
		if (field[2][0] == '*') {
			(playerTurn == X) ? (field[2][0] = 'X') : (field[2][0] = '0');
			correctInput = true;
		}
		else correctInput = false;
		break;

	case ('x'):
		if (field[2][1] == '*') {
			(playerTurn == X) ? (field[2][1] = 'X') : (field[2][1] = '0');
			correctInput = true;
		}
		else correctInput = false;
		break;

	case ('c'):
		if (field[2][2] == '*') {
			(playerTurn == X) ? (field[2][2] = 'X') : (field[2][2] = '0');
			correctInput = true;
		}
		else correctInput = false;
		break;
	}
}

void Logic() {
	if (correctInput) turn++;
	(turn % 2 == 0) ? (playerTurn = X) : (playerTurn = O);

	if (checkWin()) {
		turn--;
		(turn % 2 == 0) ? (playerTurn = X) : (playerTurn = O);
		gameStatus = "Игра окончена!";
		Draw();
		cout << "Победил игрок " << playerTurn << endl << endl;
		exit(0);
	}

	if (checkDraw()) {
		gameStatus = "Игра окончена!";
		Draw();
		cout << "Ничья!" << endl << endl;
		exit(0);
	}
} 

void Draw() {																						//Функция для отрисовки поля
	cout << endl << endl << endl;
	cout << "\t   Крестики-Нолики!" << endl << endl;
	cout << "\t     Ход игрока №" << playerTurn << endl << endl;

	for (int i = 0; i < HEIGHT; i++) {
		cout << "\t\t";
		for (int j = 0; j < WIDTH; j++) {
			cout << field[i][j] << ' ';
		}
		cout << endl << endl;
	}
	Instruction();
	cout << gameStatus << endl;
}

void Instruction() {																				//Функция дял вывода инструкции 
	cout << "Игрок №1 - 'X', а Игрок №2 - '0'" << endl;
	cout << "Для установки своего флага в соответствующую ячейку введите:" << endl;
	cout << "'q' - ячейка a11; 'w' - ячейка a12; 'e' - ячейка a13;" << endl;
	cout << "'a' - ячейка a21; 's' - ячейка a22; 'd' - ячейка a23;" << endl;
	cout << "'z' - ячейка a31; 'x' - ячейка a32; 'c' - ячейка a33;" << endl;
	cout << "Для выхода из игры введите: 'o'." << endl;
}

bool checkWin() {
	bool flag;
	int intDgFlag1 = 0, intDgFlag2 = 0, intVrFlag = 0, intGrFlag = 0;
	if (field[1][1] != '*') {
		for (int i = 0; i < WIDTH - 1; i++) {														//Проверка первой диагонали
			if (field[i + 1][i + 1] == field[i][i]) intDgFlag1++;
		}

		for (int i = 0; i < WIDTH - 1; i++) {														//Проверка второй диагонали
			if (field[WIDTH - 1 - i][i] == field[WIDTH - 1 - (i + 1)][i + 1]) intDgFlag2++;
		}
	}

	for (int i = 0; i < WIDTH; i++) {																//Проверка вертикалей
		for (int j = 0; j < HEIGHT - 1; j++) {
			if (field[(WIDTH - 1) / 2][i] != '*')
				if (field[j + 1][i] == field[j][i]) intVrFlag++;
		}
		if (intVrFlag != 2) intVrFlag = 0;
		if (intVrFlag == 2) break;
	}

	for (int i = 0; i < HEIGHT; i++) {																//Проверка горизонталей
		for (int j = 0; j < HEIGHT - 1; j++) {
			if (field[i][(HEIGHT - 1) / 2] != '*')
				if (field[i][j + 1] == field[i][j]) intGrFlag++;
		}
		if (intGrFlag != 2) intGrFlag = 0;
		if (intGrFlag == 2) break;
	}



	if (intDgFlag1 == 2 || intDgFlag2 == 2 || intVrFlag == 2 || intGrFlag == 2) flag = true;
	else flag = false;
	return flag;
}

bool checkDraw() {
	bool flag;
	int intFlag = 0;

	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (field[i][j] != '*') intFlag++;
		}
	}
	if (intFlag == 9) flag = true;
	else flag = false;
	return flag;
}


void gamePlayerVsPlayer(){
	Draw();
	Input();
	Logic();
}

void gamePlayerVsBot() {
	Draw();
	Input();
	Logic();
	Draw();
	botInput();
	Logic();
}