#ifndef FILE_SEEN
#define FILE_SEEN


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

#endif