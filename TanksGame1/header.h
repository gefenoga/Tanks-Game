// header.h

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>

#define BOARD_SIZE 11
#define WRAPPER_BOARD_SIZE (BOARD_SIZE + 2)

// Typedef declaration
typedef enum
{
	TANK = 'O',
	BREAKABLE_WALL = 'X',
	UNBREAKABLE_WALL = '*',
	EMPTY = ' ' 
} boardPiece;
typedef enum
{
	FALSE,
	TRUE
}Boolean;
typedef struct
{
	int xPos;
	int yPos;
	Boolean isDead;
}Tank;


// Function prototypes
void fillBoards(Tank *itnkTank1, Tank *itnkTank2);
void printWrapperBoard();
void menu();
void moveTank(Tank *itnkCurrTank);
void normalShoot(Tank* itnkTank1, Tank* itnkTank2);
void switchShoot(Tank* itnkTank1, Tank* itnkTank2);
void airBomb(Tank* itnkTank1, Tank* itnkTank2);
void CheckEnding(Tank* itnkTank1, Tank* itnkTank2);