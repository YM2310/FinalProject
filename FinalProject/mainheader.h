#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#define ASTERISK 100
#define HASH 101
#define SPACE 102
#define N 8
#define M 8 
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

typedef char boardPos[2];
typedef struct _move
{
	char rows, cols;
} Move;
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


boardPosArray** validMoves(movesArray** moves, char** board);
void swap(Move* x, Move* y);
void sortToEndArr(Move* arr, int location, unsigned int size);

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


int checkAndDisplayPathFromFile(char* file_name, movesArray** moves, char** board);
void getPos(boardPos* toChange, boardPos current, Move UpdateCurrent);
void insertMovetoEndList(movesList* p_list, Move move_current);
bool isValidpath(boardPosArray* boardPosarray, char** board, movesArray** moves, movesList* plist);
int countspaces(char** theBoard);
moveCell* createCell(char row, char col);
void boardCopy(char** board, char** dest, boardPos start);
int display(movesList* moves_list, boardPos start, char** board);
void free_list(moveCell* head);
movesList makeEmptyList();
moveCell* createmoveCell(char row, char col, moveCell* next, moveCell* prev);
void addMovesToMirrorBoard(movesList* moves_list, char** mirror, boardPos start, int* erasedMoves);
void RemoveMoveFromList(moveCell* curr);
pathTree findAllPossiblePaths(boardPos start, movesArray** moves, char** board);
treeNode* findAllPossiblePaths_REC(int curr_row, int curr_col, movesArray** moves, char** board);
void insertNodeToEndList(treeNodeListCell* lst_cell, treeNodeListCell* new_node_list);
treeNode* createTreeNode(int row, int col);
treeNodeListCell* createTreeNodeList();
bool Check_Move(int row, int col, char** board);
void Convert_boardpos(boardPos pos, int* row, int* col);
void Free_list(movesList l);
void free_mirror(char** mirror);
void saveListToBinFile(char* file_name, boardPosArray* pos_arr);
void printWholes(FILE* file, boardPosArray* pos_arr, int size);
void printRemain(FILE* file, boardPosArray* pos_arr, int size);
unsigned int binaryPos(boardPos* pos);
boardPosArray* readPositions(FILE* file);
boardPos* binaryToPos(char binPos);
boardPosArray* readListfromBinFile(char* file_name);

