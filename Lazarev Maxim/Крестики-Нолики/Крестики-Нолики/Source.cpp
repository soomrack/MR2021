#include <iostream>
#include <iomanip>

using namespace std;


const short int WIDTH = 3, HEIGHT = 3;																//Ðàçìåð ïîëÿ (äâå êîíñòàíòû èíèöèàëèçèðîâàíû ïî ãëóïîñòè:))


enum PlayerTurn {																					//Ïåðå÷èñëåíèå èãðîêîâ
	X = 1,
	O = 2
};


int turn;																							//Íîìåð õîäà
char input;																							//Ââîä êëàâèàòóðû
const char *gameStatus;																				//Ñòàòóñ èãðû
char field[WIDTH][HEIGHT];																			//Ïîëå																						
bool correctInput;																					//Ëîãè÷åñêàÿ ïåðåìåííàÿ, õðàíÿùàÿ èíôîðìàöèþ î êîððåêòíîñòè ââîäà
PlayerTurn playerTurn;																				//Ñ÷åò÷èê î÷åðåäíîñòè õîäà

bool checkWin() {																					
	bool flag;
	int intDgFlag1 = 0, intDgFlag2 = 0, intVrFlag = 0, intGrFlag = 0;
	if (field[1][1] != '*') {
		for (int i = 0; i < WIDTH - 1; i++) {														//Ïðîâåðêà ïåðâîé äèàãîíàëè
			if (field[i + 1][i + 1] == field[i][i]) intDgFlag1++;
		}

		for (int i = 0; i < WIDTH - 1; i++) {														//Ïðîâåðêà âòîðîé äèàãîíàëè
			if (field[WIDTH-1-i][i] == field[WIDTH-1-(i+1)][i + 1]) intDgFlag2++;
		}
	}
	
	for (int i = 0; i < WIDTH; i++) {																//Ïðîâåðêà âåðòèêàëåé
		for (int j = 0; j < HEIGHT - 1; j++) {
			if (field[(WIDTH - 1) / 2][i] != '*')
				if (field[j + 1][i] == field[j][i]) intVrFlag++;
		}
		if (intVrFlag != 2) intVrFlag = 0;
		if (intVrFlag == 2) break;
	}

	for (int i = 0; i < HEIGHT; i++) {																//Ïðîâåðêà ãîðèçîíòàëåé
		for (int j = 0; j < HEIGHT - 1; j++) {
			if (field[i][(HEIGHT - 1) / 2] != '*')
				if (field[i][j + 1] == field[i][j]) intGrFlag++;
		}
		if (intGrFlag != 2) intGrFlag = 0;
		if (intGrFlag == 2) break;
	}



	if (intDgFlag1 == 2||intDgFlag2==2||intVrFlag==2||intGrFlag==2) flag = true;
	else flag = false;
	return flag;
}

bool checkDraw() {
	bool flag;
	int intFlag=0;

	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (field[i][j] != '*') intFlag++;
		}
	}
	if (intFlag == 9) flag = true;
	else flag = false;
	return flag;
}

void Setup() {																						//Óñòàíîâêà íàñòðîåê ïî óìîë÷àíèþ
	setlocale(LC_ALL, "Russian");
	
	playerTurn = X;
	turn = 0;																					
	gameStatus = "Èãðà íå îêîí÷åíà";

	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			 field[i][j] = '*';
		}
	}	
}

void Instruction() {																				//Ôóíêöèÿ äÿë âûâîäà èíñòðóêöèè 
	cout << "Èãðîê ¹1 - 'X', à Èãðîê ¹2 - '0'" << endl;
	cout << "Äëÿ óñòàíîâêè ñâîåãî ôëàãà â ñîîòâåòñòâóþùóþ ÿ÷åéêó ââåäèòå:" << endl;
	cout << "'q' - ÿ÷åéêà a11; 'w' - ÿ÷åéêà a12; 'e' - ÿ÷åéêà a13;" << endl;
	cout << "'a' - ÿ÷åéêà a21; 's' - ÿ÷åéêà a22; 'd' - ÿ÷åéêà a23;" << endl;
	cout << "'z' - ÿ÷åéêà a31; 'x' - ÿ÷åéêà a32; 'c' - ÿ÷åéêà a33;" << endl;
	cout << "Äëÿ âûõîäà èç èãðû ââåäèòå: 'o'." << endl;
}


void Draw(){																						//Ôóíêöèÿ äëÿ îòðèñîâêè ïîëÿ
	cout << endl << endl << endl;
	cout << "\t   Êðåñòèêè-Íîëèêè!" << endl << endl;
	cout << "\t     Õîä èãðîêà ¹" << playerTurn << endl << endl;
	
		for (int i = 0; i < HEIGHT; i++) {
			cout << "\t\t";
			for (int j = 0; j < WIDTH; j++) {
				cout << field[i][j]<<' ';
			}
			cout << endl << endl;
		}
	Instruction();
	cout << gameStatus<<endl;
	}


void Input() {
	cout << "Ââîä: ";
	cin >> setw(1) >> input;
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
		gameStatus = "Èãðà îêîí÷åíà!";
		Draw();
		cout << "Ïîáåäèë èãðîê " << playerTurn << endl << endl;
		exit(0);
	}
	
	if (checkDraw()) {
		gameStatus = "Èãðà îêîí÷åíà!";
		Draw();
		cout << "Íè÷üÿ!" << endl << endl;
		exit(0);
	}
}

int main() {
	
	Setup();

	while (1) {
		Draw();
		Input();
		Logic();
	}
	return 0;
}
