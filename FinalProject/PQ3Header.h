#define _CRT_NONTDC_NO_DEPRECAET
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include "Header.h"

treeNode* createTreeNode(boardPos pos);

treeNodeListCell* createListCell(treeNode* node);

pathTree findAllPossiblePaths(boardPos start, movesArray** moves, char** board);

void createsMoves(treeNode* node, movesArray** movesA);

bool checkiffair(Move moves, char** board, int row, int col);

void deleteunfairStep(movesArray** arr, int row, int col, int index);

void checkMemoryAllocation(void* ptr);

void createsMovesRec(treeNode* node, movesArray** movesA, char* string);

boardPosArray** fairMoves(movesArray** moves, char** board);

void Test();

movesArray** createsMovesArray();

char** createsGameBoard();

void PrintMove(pathTree tree);

void freeGameBoardAlocc(char** gameBoard);

void freeMovesAlocc(movesArray** arr);

void PrintMoveRec(treeNode* node);

