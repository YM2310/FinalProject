#pragma once
#define M 5
#define N 4
#include <stdbool.h>

typedef char boardPos[2];

typedef struct _move {
	char rows, cols;
} Move;

typedef struct _movesArray {
	unsigned int size;
	Move* moves;
} movesArray;

typedef struct _boardPosArray {
	unsigned int size;
	boardPos* positions;
} boardPosArray;

boardPosArray** validMoves(movesArray** moves, char** board); //removes illegal moves
bool isLegal(boardPos origin, Move move, char** board);// checks if move is legal, return TRUE if legal False if illegal
void removeCells(Move** moves, unsigned int* size, int* remove, int howmany);// removes the move and reallocates the array
boardPos* legalMovesFrom(Move* moves, int movesSize, int row, int col);



