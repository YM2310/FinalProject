#pragma once
#include "Structs.h"
#define remain1 (size % 4 == 1)
#define remain2 (size % 4 == 2)
#define remain3 (size % 4 == 3)
#define MASK1 0x00FC0000
#define MASK2 0x0003F000
#define MASK3 0x00000FC0
#define isremain size%4!=0
#define MASK4 0x0000003F
#define MASK1SHORT 0xFC00
#define MASK2SHORT 0x03F0

int checkAndDisplayPathFromFile(char* file_name, movesArray** moves, char** board);
int countspaces(char** theBoard);
boardPosArray* readListfromBinFile(char* file_name);
boardPosArray* readPositions(FILE* file);
boardPos* binaryToPos(char binPos);
bool isValidpath(boardPosArray* boardPosarray, char** board, movesArray** moves, movesList* p_list);
void getPos(boardPos* toChange, boardPos current, Move UpdateCurrent);
void insertMovetoEndList(movesList* p_list, Move move_current);
moveCell* createCell(char row, char col);