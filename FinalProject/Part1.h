#pragma once
#include "Structs.h"


boardPosArray** validMoves(movesArray** moves, char** board); //removes illegal moves

bool isLegal(boardPos origin, Move move, char** board);// checks if move is legal, return TRUE if legal False if illegal

void removeCells(Move** moves, unsigned int* size, int* remove, int howmany);// removes the move and reallocates the array

boardPos* legalMovesFrom(Move* moves, int movesSize, int row, int col);