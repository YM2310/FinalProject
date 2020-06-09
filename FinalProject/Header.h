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


/*-------Part 1 declrations-------*/
boardPosArray** validMoves(movesArray** moves, char** board); //removes illegal moves

bool isLegal(boardPos origin, Move move, char** board);// checks if move is legal, return TRUE if legal False if illegal

void removeCells(Move** moves, unsigned int* size, int* remove, int howmany);// removes the move and reallocates the array

boardPos* legalMovesFrom(Move* moves, int movesSize, int row, int col);

/*-------Part 2 declrations-------*/
movesList makeEmptyList();
moveCell* createsmoveCell(char row, char col, moveCell* next, moveCell* prev);
void free_list(moveCell* head);
void Free_list(movesList l);
void RemoveFromList(moveCell* after);
void swapMove(Move* a, Move* b);
void boardCopy(char** board, char** dest, boardPos start);

void addMoves(movesList* moves_list, char** mirror, boardPos start, int* erasedMoves);
///shows the board with the steps.
///sends incorrect moveCell to delition

int reveal(movesList* moves_list, boardPos start, char** board);
///remove incorrect moves from the list, prints the board after values insert

boardPosArray** PossibleValidMoves(movesArray** moves, char** board);
///returns a matriza of the valid moves array for each cell

void convertToPosition(int i, int j, movesArray** moves, boardPos* position);
///inserts values to positions allowed to move from 

void validMovesByCell(movesArray** moves, char** board, int i, int j, int* countWrong);
///checks the array inside a specific cell in 'moves' and puts the invalid moves at the end of the array

boardPosArray** movesToBoardPos(movesArray** moves);
///creats and returns a-'boardPosArray**' with values.

/*-------Part 4 declrations-------*/
movesList* findPathCoveringAllBoard(boardPos start, movesArray** moves, char** board);
int howManyIlegal(char** board);
posCell* createPosCell(boardPos pos);
posCell* longestPathRec(treeNode* head, int moves_left);
movesList* PosListToMoveList(posList pos_list);

/*-------Part 3 declrations-------*/
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
/**/

/*-------part 5 declatationes-------*/
void saveListToBinFile(char* file_name, boardPosArray* pos_arr);
BYTE setBit(BYTE destination, int bit);
BYTE* createBitArray(int* arr, int size, int bit_arr_size);
int* createBitMap(boardPosArray* pos_arr, int* bitmap_size);
bool isBitOn(unsigned char check, int bit);
void bitarraytest(BYTE* bit_arr, int size);