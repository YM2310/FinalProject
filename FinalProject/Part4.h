#pragma once
#include "Structs.h"


movesList* findPathCoveringAllBoard(boardPos start, movesArray** moves, char** board);
int howManyIlegal(char** board);
posCell* createPosCell(boardPos pos);
posCell* longestPathRec(treeNode* head, int moves_left);
movesList* PosListToMoveList(posList pos_list);