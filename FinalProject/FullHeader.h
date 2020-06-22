#define _CRT_NONTDC_NO_DEPRECAET
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#define ASTERISK 100
#define HASH 101
#define SPACE 102
#define N 4
#define M 5 
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



/*-----------------------types-----------------------*/
typedef char boardPos[2];
typedef char BYTE;

typedef struct _move
{
	char rows, cols;
} Move;

/*-----------------------Arrays-----------------------*/
typedef struct _movesArray
{
	unsigned int size;
	Move* moves;
} movesArray;
typedef struct _boardPosArray
{
	unsigned int size;
	boardPos* positions;
} boardPosArray;
/*-----------------------Lists-----------------------*/
typedef struct _moveCell
{
	Move move;
	struct _moveCell* next, * prev;
} moveCell;
typedef struct _movesList
{
	moveCell* head;
	moveCell* tail;
} movesList;

typedef struct _posCell {
	boardPos pos;
	struct _posCell* next;
} posCell;
typedef struct _posList {
	posCell* head;
} posList;
/*-----------------------Trees-----------------------*/
typedef struct  _treeNodeListCell treeNodeListCell;
typedef struct _treeNode {
	boardPos position;
	treeNodeListCell* next_possible_positions;
} treeNode;
typedef struct _treeNodeListCell {
	treeNode* node;
	struct _treeNodeListCell* next;
} treeNodeListCell;
typedef struct _pathTree {
	treeNode* head;
} pathTree;




/*-------Part 1 declrations-------*/
boardPosArray** validMoves(movesArray** moves, char** board); //removes illegal moves

bool isLegal(boardPos origin, Move move, char** board);// checks if move is legal, return TRUE if legal False if illegal

void removeCells(Move** moves, unsigned int* size, int* remove, int howmany);// removes the move and reallocates the array

boardPos* legalMovesFrom(Move* moves, int movesSize, int row, int col);

/*-------Part 2 declrations-------*/
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

/*-------Part 3 declrations-------*/
treeNode* createTreeNode(boardPos pos);

treeNodeListCell* createListCell(treeNode* node);

pathTree findAllPossiblePaths(boardPos start, movesArray** moves, char** board);

void createsMoves(treeNode* node, movesArray** movesA);

bool checkiffair(Move moves, char** board, int row, int col);

void deleteunfairStep(movesArray** arr, int row, int col, int index);

void checkMemoryAllocation(void* ptr);

void createsMovesRec(treeNode* node, movesArray** movesA, char* string);

void Test();

movesArray** createsMovesArray();

char** createsGameBoard();

void PrintMove(pathTree tree);

void freeGameBoardAlocc(char** gameBoard);

void freeMovesAlocc(movesArray** arr);

void PrintMoveRec(treeNode* node);


/*-------Part 4 declrations-------*/
movesList* findPathCoveringAllBoard(boardPos start, movesArray** moves, char** board);
int howManyIlegal(char** board);
posCell* createPosCell(boardPos pos);
posCell* longestPathRec(treeNode* head, int moves_left);
movesList* PosListToMoveList(posList pos_list);



/*-------part 5 declatationes-------*/
void saveListToBinFile(char* file_name, boardPosArray* pos_arr);
BYTE setBit(BYTE destination, int bit);
BYTE* createBitArray(int* arr, int size, int bit_arr_size);
int* createBitMap(boardPosArray* pos_arr, int* bitmap_size);
bool isBitOn(unsigned char check, int bit);
void bitarraytest(BYTE* bit_arr, int size);

/*-------part 6 declatationes-------*/
int checkAndDisplayPathFromFile(char* file_name, movesArray** moves, char** board);
int countspaces(char** theBoard);
boardPosArray* readListfromBinFile(char* file_name);
boardPosArray* readPositions(FILE* file);
boardPos* binaryToPos(char binPos);
bool isValidpath(boardPosArray* boardPosarray, char** board, movesArray** moves, movesList* p_list);
void getPos(boardPos* toChange, boardPos current, Move UpdateCurrent);
void insertMovetoEndList(movesList* p_list, Move move_current);
moveCell* createCell(char row, char col);