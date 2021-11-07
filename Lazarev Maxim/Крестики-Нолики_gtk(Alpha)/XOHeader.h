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

extern int turn;																							            //Номер хода

extern PLAYERTURN playerTurn;
extern GAMEMODE gameMode;

extern void (*game)();



#endif //!XOHEADER_H