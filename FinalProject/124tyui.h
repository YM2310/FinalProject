#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ROWS 4
#define COLS 5
#define ASTERISK 100
#define HASH 101
#define SPACE 102

typedef char boardPos[2];

typedef struct _move {
	char rows, cols;
} Move;

typedef struct _movesArray {
	unsigned int size;
	Move *moves;
} movesArray;

typedef struct _boardPosArray {
	unsigned int size;
	boardPos *positions;
} boardPosArray;

typedef struct _moveCell {
	Move move;
	struct _moveCell *next, *prev;
} moveCell;

typedef struct _movesList {
	moveCell * head;
	moveCell * tail;
} movesList;

movesList makeEmptyList();
moveCell* createsmoveCell(char row, char col, moveCell* next, moveCell* prev);
void free_list(moveCell *head);
void Free_list(movesList l);
void RemoveFromList(moveCell* after);
void swapMove(Move* a, Move* b);
void boardCopy(char** board, char** dest, boardPos start);

void addMoves(movesList *moves_list, char** mirror, boardPos start, int* erasedMoves);
///shows the board with the steps.
///sends incorrect moveCell to delition

int reveal(movesList *moves_list, boardPos start, char **board);
///remove incorrect moves from the list, prints the board after values insert

boardPosArray** PossibleValidMoves(movesArray **moves, char **board);
///returns a matriza of the valid moves array for each cell

void convertToPosition(int i, int j, movesArray** moves, boardPos* position);
///inserts values to positions allowed to move from 

void validMovesByCell(movesArray **moves, char **board, int i, int j, int* countWrong);
///checks the array inside a specific cell in 'moves' and puts the invalid moves at the end of the array

boardPosArray** movesToBoardPos(movesArray** moves);
///creats and returns a-'boardPosArray**' with values.



