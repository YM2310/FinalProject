#pragma once
#define M 5
#define N 4
#include <stdbool.h>
typedef char BYTE;
typedef char boardPos[2];

/*Part 1 structs*/

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

/*Part 2 structs*/

typedef struct _moveCell {
	Move move;
	struct _moveCell* next, * prev;
} moveCell;
typedef struct _movesList {
	moveCell* head;
	moveCell* tail;
} movesList;


/*Part 3 structs*/
typedef struct _treeNode treeNode;
typedef struct _pathTree pathTree;
typedef struct _treeNodeListCell treeNodeListCell;

typedef struct _treeNode {
	boardPos position;
	treeNodeListCell* next_possible_positions;
} treeNode;

typedef struct _pathTree {
	treeNode* head;
} pathTree;

typedef struct _treeNodeListCell {
	treeNode* node;
	struct _treeNodeListCell* next;
} treeNodeListCell;

/*part 4 structs*/

typedef struct _posCell {
	boardPos pos;
	struct _posCell* next;
} posCell;
typedef struct _posList {
	posCell* head;
} posList;


/*Part 1 declrations*/
boardPosArray** validMoves(movesArray** moves, char** board); //removes illegal moves

bool isLegal(boardPos origin, Move move, char** board);// checks if move is legal, return TRUE if legal False if illegal

void removeCells(Move** moves, unsigned int* size, int* remove, int howmany);// removes the move and reallocates the array

boardPos* legalMovesFrom(Move* moves, int movesSize, int row, int col);

/*Part 4 declrations*/
movesList* findPathCoveringAllBoard(boardPos start, movesArray** moves, char** board);
int howManyIlegal(char** board);

/**/
pathTree findAllPossiblePaths(boardPos start, movesArray** moves, char** board);
/**/

/*part 5 declatationes*/
void saveListToBinFile(char* file_name, boardPosArray* pos_arr);
BYTE setBit(BYTE destination, int bit);
BYTE* createBitArray(int* arr, int size, int bit_arr_size);
int* createBitMap(boardPosArray* pos_arr, int* bitmap_size);
bool isBitOn(char check, int bit);
void bitarraytest(BYTE* bit_arr, int size);