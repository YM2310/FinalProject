#pragma once
#include "Structs.h"


void Free_list(movesList l);
void free_list(moveCell* head);
movesList makeEmptyList();
void RemoveFromList(moveCell* after);
moveCell* createsmoveCell(char row, char col, moveCell* next, moveCell* prev);

void addMoves(movesList* moves_list, char** mirror, boardPos start, int* erasedMoves);
///shows the board with the steps.
///sends incorrect moveCell to delition

void boardCopy(char** board, char** dest, boardPos start);
void swapMove(Move* a, Move* b);

int display(movesList* moves_list, boardPos start, char** board);
///remove incorrect moves from the list, prints the board after values insert

boardPosArray** movesToBoardPos(movesArray** moves);
///creats and returns a-'boardPosArray**' with values.

void convertToPosition(int i, int j, movesArray** moves, boardPos* position);
///inserts values to positions allowed to move from 

boardPosArray** PossibleValidMoves(movesArray** moves, char** board);
///returns a matrix of the valid moves array for each cell

void validMovesByCell(movesArray** moves, char** board, int i, int j, int* countWrong);
///checks the array inside a specific cell in 'moves' and puts the invalid moves at the end of the array