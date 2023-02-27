// Header.cpp

#include "header.h"

// Constant Global variables definition
const int DIRECTION_X[9] = { 0, -1, -1, -1, 0, 0, 1, 1, 1 };
const int DIRECTION_Y[9] = { 0, -1, 0, 1, -1, 1, -1, 0, 1 };

// Global variables declaration
boardPiece BOARD[BOARD_SIZE][BOARD_SIZE];
boardPiece WRAPPER_BOARD[WRAPPER_BOARD_SIZE][WRAPPER_BOARD_SIZE];
int NUMBER_OF_WALLS;

//---------------------------------------------------------------------
//                             Fill Boards
//                            -------------
// 
// General		: The fuction fills the board and wrapped board 
//				  according to game rules.
//
// Parameters	: 
//		itnkTank1		- an adress of the first player's tank.
//		itnkTank2		- an adress of the second player's tank.
//
// Return Value : None.
//
//---------------------------------------------------------------------
void fillBoards(Tank* itnkTank1, Tank* itnkTank2)
{
	// Variable definition
	int nBoardRowsIndex;
	int nBoardColumnsIndex;
	int nWrapperRowsIndex;
	int nWrapperColumnsIndex;

	// Code section
	NUMBER_OF_WALLS = 0;

	// A nested loop that fills up the board
	for (nBoardRowsIndex = 0; nBoardRowsIndex < BOARD_SIZE; nBoardRowsIndex++)
	{
		for (nBoardColumnsIndex = 0; 
			 nBoardColumnsIndex < BOARD_SIZE; 
			 nBoardColumnsIndex++)
		{

			// Starting point of tanks
			if (nBoardRowsIndex == BOARD_SIZE / 2 && 
			   (nBoardColumnsIndex == 0 || nBoardColumnsIndex == BOARD_SIZE - 1))
			{
				BOARD[nBoardRowsIndex][nBoardColumnsIndex] = TANK;
			}

			else if (nBoardRowsIndex % 2 == 1 && nBoardColumnsIndex % 2 == 1) 
			{
				BOARD[nBoardRowsIndex][nBoardColumnsIndex] = BREAKABLE_WALL;
				NUMBER_OF_WALLS++;
			}
			else 
			{
				BOARD[nBoardRowsIndex][nBoardColumnsIndex] = EMPTY;
			}
		}
	}

	// A nested loop that initializes the wrapper board
	for (nWrapperRowsIndex = 0; 
		 nWrapperRowsIndex < WRAPPER_BOARD_SIZE; 
		 nWrapperRowsIndex++)
	{
		for (nWrapperColumnsIndex = 0; 
			 nWrapperColumnsIndex < WRAPPER_BOARD_SIZE; 
			 nWrapperColumnsIndex++)
		{
			WRAPPER_BOARD[nWrapperRowsIndex][nWrapperColumnsIndex] = UNBREAKABLE_WALL;
		}
	}

	// A nested loop that fills up the wrapper board
	for (nBoardRowsIndex = 0, nWrapperRowsIndex = 1;
		nWrapperRowsIndex < WRAPPER_BOARD_SIZE - 1;
		nBoardRowsIndex++, nWrapperRowsIndex++)
	{
		for (nBoardColumnsIndex = 0, nWrapperColumnsIndex = 1;
			nWrapperColumnsIndex < WRAPPER_BOARD_SIZE  -1;
			nBoardColumnsIndex++, nWrapperColumnsIndex++)
		{
			WRAPPER_BOARD[nWrapperRowsIndex][nWrapperColumnsIndex] = 
				BOARD[nBoardRowsIndex][nBoardColumnsIndex];
		}
	}

	// Starting positions of tanks
	itnkTank1->xPos = WRAPPER_BOARD_SIZE / 2;
	itnkTank1->yPos = 1;
	itnkTank2->xPos = WRAPPER_BOARD_SIZE / 2;
	itnkTank2->yPos = WRAPPER_BOARD_SIZE - 2;
	itnkTank1->isDead = FALSE;
	itnkTank2->isDead = FALSE;
}

//---------------------------------------------------------------------
//                          print Wrapper Board
//                         --------------------- 
// 
// General		: The fuction prints the wrapper board.
//
// Parameters	: 
//		None.
//
// Return Value : None.
//
//---------------------------------------------------------------------
void printWrapperBoard() 
{
	// Variable definition
	int nWrapperRowsIndex;
	int nWrapperColumnsIndex;

	// Prints the wrapper board content
	for (nWrapperRowsIndex = 0;
		 nWrapperRowsIndex < WRAPPER_BOARD_SIZE;
		 nWrapperRowsIndex++)
	{
		for (nWrapperColumnsIndex = 0; 
			 nWrapperColumnsIndex < WRAPPER_BOARD_SIZE; 
			 nWrapperColumnsIndex++)
		{
			printf("%c ", WRAPPER_BOARD[nWrapperRowsIndex][nWrapperColumnsIndex]);
		}
		printf("\n");
	}
}

//---------------------------------------------------------------------
//                             Check Ending
//                            --------------
// 
// General		: The fuction ends the game if one of the tanks is 
//				  dead or if all the breakable walls are broken.
//
// Parameters	: 
//		itnkTank1		- an adress of the first player's tank.
//		itnkTank2		- an adress of the second player's tank.
//
// Return Value : None.
//
//---------------------------------------------------------------------
void CheckEnding(Tank* itnkTank1, Tank* itnkTank2) 
{
	// Code section
	if (itnkTank1->isDead) 
	{
		printf("Tank 2 won!\n");
		exit(1);
	}
	if (itnkTank2->isDead) 
	{
		printf("Tank 1 won!\n");
		exit(1);
	}
	if (NUMBER_OF_WALLS == 0) 
	{
		printf("No More breakable walls!\n");
		exit(1);
	}
	
}

//---------------------------------------------------------------------
//                               Move Tank
//                              -----------
// 
// General		: The fuction moves the tank given to a certain spot 
//				  on the board according to user input.
//
// Parameters	: 
//		itnkCurrTank	- an adress of the a certain player's tank.
//
// Return Value : None.
//
//---------------------------------------------------------------------
void moveTank(Tank* itnkCurrTank)
{
	// Variable definition
	int nDirection;
	int nNumOfSquares;
	int nTempPos_X;
	int nTempPos_Y;
	int nSquaresCounter;

	// Code section
	printf("Enter direction and amount of squares (1-up, 2-right, 3-down, 4-left): ");
	scanf("%d %d", &nDirection, &nNumOfSquares);
	nTempPos_X = itnkCurrTank->xPos;
	nTempPos_Y = itnkCurrTank->yPos;
	nSquaresCounter = 1;

	// Covering every direction
	switch (nDirection) 
	{
		// Up
		case (1):
			WRAPPER_BOARD[itnkCurrTank->xPos][itnkCurrTank->yPos] = EMPTY;
			nTempPos_X--;
			while (WRAPPER_BOARD[nTempPos_X][nTempPos_Y] == EMPTY && 
				   nSquaresCounter < nNumOfSquares + 1) 
			{
				nTempPos_X--;
				nSquaresCounter++;
			}

			// Returning to the last spot on the board
			itnkCurrTank->xPos = nTempPos_X + 1;
			WRAPPER_BOARD[itnkCurrTank->xPos][itnkCurrTank->yPos] = TANK;

			break;
		// Right
		case (2):
			WRAPPER_BOARD[itnkCurrTank->xPos][itnkCurrTank->yPos] = EMPTY;
			nTempPos_Y++;
			while (WRAPPER_BOARD[nTempPos_X][nTempPos_Y] == EMPTY &&
				nSquaresCounter < nNumOfSquares + 1)
			{
				nTempPos_Y++;
				nSquaresCounter++;
			}
			itnkCurrTank->yPos = nTempPos_Y - 1;
			WRAPPER_BOARD[itnkCurrTank->xPos][itnkCurrTank->yPos] = TANK;
			break;
		// Down
		case (3):
			WRAPPER_BOARD[itnkCurrTank->xPos][itnkCurrTank->yPos] = EMPTY;
			nTempPos_X++;
			while (WRAPPER_BOARD[nTempPos_X][nTempPos_Y] == EMPTY &&
				nSquaresCounter < nNumOfSquares + 1)
			{
				nTempPos_X++;
				nSquaresCounter++;
			}
			itnkCurrTank->xPos = nTempPos_X - 1;
			WRAPPER_BOARD[itnkCurrTank->xPos][itnkCurrTank->yPos] = TANK;
			break;
		// Left
		case (4):
			WRAPPER_BOARD[itnkCurrTank->xPos][itnkCurrTank->yPos] = EMPTY;
			nTempPos_Y--;
			while (WRAPPER_BOARD[nTempPos_X][nTempPos_Y] == EMPTY &&
				nSquaresCounter < nNumOfSquares + 1)
				{
				nTempPos_Y--;
				nSquaresCounter++;
				}
			itnkCurrTank->yPos = nTempPos_Y + 1;
			WRAPPER_BOARD[itnkCurrTank->xPos][itnkCurrTank->yPos] = TANK;
			break;
		default:

			break;
	}
}

//---------------------------------------------------------------------
//                             Normal Shoot
//                            --------------
// 
// General		: The fuction shoots a bullet from tank1 that either
//				  destroys a wall or kills the other tank.
//
// Parameters	: 
//		itnkTank1		- an adress of the shooter's tank.
//		itnkTank2		- an adress of the other player's tank.
//
// Return Value : None.
//
//---------------------------------------------------------------------
void normalShoot(Tank* itnkTank1, Tank* itnkTank2)
{
	// Variable definition
	int nBulletX;
	int nBulletY;
	int nBulletDirection;

	// Code section
	printf("Enter shooting direction (1-up, 2-right, 3-down, 4-left): ");
	scanf("%d", &nBulletDirection);
	nBulletX = itnkTank1->xPos;
	nBulletY = itnkTank1->yPos;
	
	// Covering every direction
	switch (nBulletDirection)
	{
		// Up
		case (1):
			nBulletX--;
			while (WRAPPER_BOARD[nBulletX][nBulletY] == EMPTY)
			{
				nBulletX--;
			}
			
			if (WRAPPER_BOARD[nBulletX][nBulletY] == BREAKABLE_WALL) 
			{
				WRAPPER_BOARD[nBulletX][nBulletY] = EMPTY;
				NUMBER_OF_WALLS--;
			}
			if (WRAPPER_BOARD[nBulletX][nBulletY] == TANK) 
			{
				WRAPPER_BOARD[nBulletX][nBulletY] = EMPTY;
				itnkTank2->isDead = TRUE;
			}

			break;
		// Right
		case (2):
			nBulletY++;
			while (WRAPPER_BOARD[nBulletX][nBulletY] == EMPTY)
			{
				nBulletY++;
			}

			if (WRAPPER_BOARD[nBulletX][nBulletY] == BREAKABLE_WALL)
			{
				WRAPPER_BOARD[nBulletX][nBulletY] = EMPTY;
				NUMBER_OF_WALLS--;
			}
			if (WRAPPER_BOARD[nBulletX][nBulletY] == TANK)
			{
				WRAPPER_BOARD[nBulletX][nBulletY] = EMPTY;
				itnkTank2->isDead = TRUE;
			}
			
			break;
		// Down
		case (3):
			nBulletX++;
			while (WRAPPER_BOARD[nBulletX][nBulletY] == EMPTY)
			{
				nBulletX++;
			}

			if (WRAPPER_BOARD[nBulletX][nBulletY] == BREAKABLE_WALL)
			{
				WRAPPER_BOARD[nBulletX][nBulletY] = EMPTY;
				NUMBER_OF_WALLS--;
			}
			if (WRAPPER_BOARD[nBulletX][nBulletY] == TANK)
			{
				WRAPPER_BOARD[nBulletX][nBulletY] = EMPTY;
				itnkTank2->isDead = TRUE;
			}
			
			break;
			// Left
			case (4):
				nBulletY--;
				while (WRAPPER_BOARD[nBulletX][nBulletY] == EMPTY)
				{
					nBulletY--;
				}

				if (WRAPPER_BOARD[nBulletX][nBulletY] == BREAKABLE_WALL)
				{
					WRAPPER_BOARD[nBulletX][nBulletY] = EMPTY;
					NUMBER_OF_WALLS--;
				}
				if (WRAPPER_BOARD[nBulletX][nBulletY] == TANK)
				{
					WRAPPER_BOARD[nBulletX][nBulletY] = EMPTY;
					itnkTank2->isDead = TRUE;
				}
				
				break;
			default:

				break;
	}
}

//---------------------------------------------------------------------
//                             Switch Shoot
//                            --------------
// 
// General		: The fuction shoots a bullet that switches its 
//				  direction every time it reaches a board's border.
//				  It can break a wall or kill any of the player.
//
// Parameters	: 
//		itnkTank1		- an adress of the shooter's tank.
//		itnkTank2		- an adress of the other player's tank.
//
// Return Value : None.
//
//---------------------------------------------------------------------
void switchShoot(Tank* itnkTank1, Tank* itnkTank2)
{
	// Variable definition
	int nSwitchCounter;
	int nBulletDirection;
	int nBulletX;
	int nBulletY;

	// Code section
	printf("Enter start direction of bullet (1-up, 2-right, 3-down, 4-left): ");
	scanf("%d", &nBulletDirection);
	nBulletX = itnkTank1->xPos;
	nBulletY = itnkTank1->yPos;
	nSwitchCounter = 0;

	// Determining staring point of bullet
	switch (nBulletDirection) 
	{
			case (1): // Up
				nBulletX--;

				break;
			case (2): // Right
				nBulletY++;

				break;
			case (3): // Down
				nBulletX++;

				break;
			case (4): // Left
				nBulletY--;

				break;
			default:

				break;
	}
	
	// Keep moving as long current position is valid
	while (nSwitchCounter < 5 &&
		   WRAPPER_BOARD[nBulletX][nBulletY] != TANK &&
		   WRAPPER_BOARD[nBulletX][nBulletY] != BREAKABLE_WALL)
	{

		// If reached board border
		if (WRAPPER_BOARD[nBulletX][nBulletY] == UNBREAKABLE_WALL)
		{
			
			// Returning to the last valid spot
			switch (nBulletDirection)
			{
				case (1): // up
					nBulletX++;

					break;
				case (2): // right
					nBulletY--;

					break;
				case (3): // down
					nBulletX--;

					break;
				case (4): // left
					nBulletY++;

					break;
				default:

					break;
			}

			// Cycling the bullet directions
			if (nBulletDirection == 4) 
			{
				nBulletDirection = 1;
			}
			else 
			{
				nBulletDirection++;
			}
			nSwitchCounter++;
			continue;
		}

		// Moving towards the current direction
		switch (nBulletDirection)
		{
			case (1): // Up
				nBulletX--;

				break;
			case (2): // Right
				nBulletY++;

				break;
			case (3): // Down
				nBulletX++;

				break;
			case (4): // Left
				nBulletY--;

				break;
			default:

				break;
		}
	}

	// Determining which tank is dead
	if (WRAPPER_BOARD[nBulletX][nBulletY] == TANK) 
	{
		if (nBulletX == itnkTank1->xPos && nBulletY == itnkTank1->yPos) 
		{
			itnkTank1->isDead = TRUE;
		}
		else 
		{
			itnkTank2->isDead = TRUE;
		}
		WRAPPER_BOARD[nBulletX][nBulletY] = EMPTY;
	}

	if (WRAPPER_BOARD[nBulletX][nBulletY] == BREAKABLE_WALL) 
	{
		WRAPPER_BOARD[nBulletX][nBulletY] = EMPTY;
		NUMBER_OF_WALLS--;
	}
}

//---------------------------------------------------------------------
//                               Air Bomb
//                             ------------
// 
// General		: The fuction bombs the board in a 3x3 radius and 
//				  either kills a player or destroys walls.
//
// Parameters	: 
//		itnkTank1		- an adress of the shooter's tank.
//		itnkTank2		- an adress of the other player's tank.
//
// Return Value : None.
//
//---------------------------------------------------------------------
void airBomb(Tank* itnkTank1, Tank* itnkTank2)
{
	// Array declaration
	int arrnBombMatrix[3][3];

	// Variable definition
	int nRowsIndex;
	int nColumnsIndex;
	int nDirectionIndex;
	int nBombCenter_x;
	int nBombCenter_y;
	int nMatrixOffset_x;
	int nMatrixOffset_y;
	boardPiece bpCurrentCell;

	// Code section
	srand((unsigned)time(NULL));

	// Randomizing the values in the matrix
	for (nRowsIndex = 0; nRowsIndex < 3; nRowsIndex++)
	{
		for (nColumnsIndex = 0; nColumnsIndex < 3; nColumnsIndex++)
		{
			arrnBombMatrix[nRowsIndex][nColumnsIndex] = rand() % 2;
			printf("%d ", arrnBombMatrix[nRowsIndex][nColumnsIndex]);
		}
		printf("\n");
	}

	printf("Enter indexes of the air bomb: ");
	scanf("%d %d", &nBombCenter_x, &nBombCenter_y);

	// Bombing the area around bomb center
	for (nDirectionIndex = 0; nDirectionIndex < 9; nDirectionIndex++)
	{
		nMatrixOffset_x = nBombCenter_x + DIRECTION_X[nDirectionIndex];
		nMatrixOffset_y = nBombCenter_y + DIRECTION_Y[nDirectionIndex];
		
		// If indexes out of border
		if (nMatrixOffset_x < 0 ||
			nMatrixOffset_x >= WRAPPER_BOARD_SIZE ||
			nMatrixOffset_y < 0 ||
			nMatrixOffset_y >= WRAPPER_BOARD_SIZE)
		{
			continue;
		}
		bpCurrentCell = WRAPPER_BOARD[nMatrixOffset_x][nMatrixOffset_y];
		
		// If one of the 1's in the matrix is on a breakable wall
		if (bpCurrentCell == BREAKABLE_WALL &&
			arrnBombMatrix[1 + DIRECTION_X[nDirectionIndex]]
						  [1 + DIRECTION_Y[nDirectionIndex]]) 
		{
			WRAPPER_BOARD[nMatrixOffset_x][nMatrixOffset_y] = EMPTY;
			NUMBER_OF_WALLS--;
		}

		// If one of the 1's in the matrix is on a tank
		if (bpCurrentCell == TANK &&
			arrnBombMatrix[1 + DIRECTION_X[nDirectionIndex]]
						  [1 + DIRECTION_Y[nDirectionIndex]])
		{

			// Detemining which tank is dead
			if (nMatrixOffset_x == itnkTank1->xPos && 
				nMatrixOffset_y == itnkTank1->yPos) 
			{
				itnkTank1->isDead = TRUE;
			}
			else 
			{
				itnkTank2->isDead = TRUE;
			}
			WRAPPER_BOARD[nMatrixOffset_x][nMatrixOffset_y] = EMPTY;
		}
	}
}

//---------------------------------------------------------------------
//								   Menu
//                                ------
// 
// General		: The fuction manages a menu for the players 
//				  to play the game.
//
// Parameters	: 
//		None.
//
// Return Value : None.
//
//---------------------------------------------------------------------
void menu() 
{
	// Variable definition
	int nTurn;
	int nMoveOption;
	Tank tnkPlayer1;
	Tank tnkPlayer2;

	// Code section
	nTurn = 1;
	fillBoards(&tnkPlayer1, &tnkPlayer2);

	// Looping until user entered 999
	while (1)
	{

		// Covering each player's turn 
		switch (nTurn)
		{
			case (1):
				printf("Player 1's turn: ");
				scanf("%d", &nMoveOption);

				// Covering every possible move
				switch (nMoveOption)
				{
					case (1):
						moveTank(&tnkPlayer1);
						nTurn = 2;

						break;
					case (2):
						normalShoot(&tnkPlayer1, &tnkPlayer2);
						nTurn = 2;

						break;
					case (3):
						switchShoot(&tnkPlayer1, &tnkPlayer2);
						nTurn = 2;

						break;
					case (4):
						airBomb(&tnkPlayer1, &tnkPlayer2);
						nTurn = 2;

						break;
					case (999):
						printf("exiting...\n");
						exit(1);

						break;
					default:
						printf("invalid input!\n");
						nTurn = 1;

						break;
				}

				break;
			case (2):
				printf("player 2's turn: ");
				scanf("%d", &nMoveOption);

				// Covering every possible move
				switch (nMoveOption)
				{
					case (1):
						moveTank(&tnkPlayer2);
						nTurn = 1;

						break;
					case (2):
						normalShoot(&tnkPlayer2, &tnkPlayer1);
						nTurn = 1;

						break;
					case (3):
						switchShoot(&tnkPlayer2, &tnkPlayer1);
						nTurn = 1;

						break;
					case (4):
						airBomb(&tnkPlayer2, &tnkPlayer1);
						nTurn = 1;

						break;
					case (999):
						printf("exiting...\n");
						exit(1);

						break;
					default:
						printf("invalid input!\n");
						printf("final board:\n");
						nTurn = 2;

						break;
					}

				break;
		}
		printWrapperBoard();
		CheckEnding(&tnkPlayer1, &tnkPlayer2);
	} 
}