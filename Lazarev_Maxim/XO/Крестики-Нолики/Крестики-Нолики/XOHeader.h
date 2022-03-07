#define WIDTH 3
#define HEIGHT 3

#ifndef XOHEADER_H
#define XOHEADER_H

enum PLAYERTURN {
	X = 1,
	O = 2
};
enum GAMEMODE {
	PlayerVsBot = 1,
	PlayerVsPlayer = 2,
	BotVsBot = 3
};


extern char field[WIDTH][HEIGHT];
extern char input;
extern const char* gameStatus;

extern int turn;																							//Номер хода

extern bool correctInput;																					//Логическая переменная, хранящая информацию о корректности ввода

extern PLAYERTURN playerTurn;
extern GAMEMODE gameMode;

#endif //!XOHEADER_H