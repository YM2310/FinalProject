#include "Part3.h"


pathTree findAllPossiblePaths(boardPos start, movesArray **moves, char **board)
{
	int moveCounter = 0;
	pathTree tree;
	treeNode* node = createTreeNode(start);
	treeNodeListCell* list = createListCell(NULL);
	for (int row = 0; row < N; row++)
	{
		for (int col = 0; col < M; col++)
		{
			while (moveCounter < moves[row][col].size)
			{
				if (checkiffair(moves[row][col].moves[moveCounter], board, row, col))
					deleteunfairStep(moves, row, col, moveCounter);
				else
					moveCounter++;
			}
			moveCounter = 0;
		}
	}
	tree.head = node;
	createsMoves(node, moves);
	return tree;
}

void createsMoves(treeNode* node ,movesArray** movesA)
{
	createsMovesRec(node, movesA, node->position);
}

void createsMovesRec(treeNode* node, movesArray** movesA, char* string)
{
	int row = node->position[0] - 65, col = node->position[1] - 49, k;
	if (movesA[row][col].size > 0)
	{
		char str[] = "A1";
		node->next_possible_positions = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
		checkMemoryAllocation(node->next_possible_positions);
		node->next_possible_positions = NULL;
		treeNodeListCell *ptr = NULL, *ptrPrev = NULL;
		for (k = 0; k < movesA[row][col].size; k++)
		{
			str[0] = movesA[row][col].moves[k].rows + 65 + row;
			str[1] = movesA[row][col].moves[k].cols + 49 + col;
			if (strcmp(str, string) != 0)
			{
				ptrPrev = ptr;
				ptr = createListCell(createTreeNode(str));
				if (node->next_possible_positions == NULL)
					node->next_possible_positions = ptr;
				else
					ptrPrev->next = ptr;
				ptr->next = NULL;
			}
		}
		ptr = node->next_possible_positions;
		movesA[row][col].size = 0;
		while (ptr != NULL)
		{
			createsMovesRec(ptr->node, movesA, node->position);
			ptr = ptr->next;
		}
	}
	else
	{
		node->next_possible_positions = NULL;
	}
}

void deleteunfairStep(movesArray** arr, int row, int col, int index)
{
	arr[row][col].moves[index].cols = arr[row][col].moves[arr[row][col].size - 1].cols;
	arr[row][col].moves[index].rows = arr[row][col].moves[arr[row][col].size - 1].rows; 
	arr[row][col].size--;
	arr[row][col].moves = (Move*)realloc(arr[row][col].moves, arr[row][col].size * sizeof(Move)); 
	checkMemoryAllocation(arr[row][col].moves);
}

bool checkiffair(Move moves, char** board, int row, int col)
{
	int column = moves.cols + col, rows = moves.rows + row;
	if (column >= M || column < 0 || rows >= N || rows < 0) 
		return true;
	else if (board[rows][column] == '*') 
		return true;
	else if (row == rows && col == column)
		return true;
	return false;
}

treeNode* createTreeNode(boardPos pos)
{
	treeNode* node = (treeNode*)malloc(sizeof(treeNode));
	checkMemoryAllocation(node);
	strcpy(node->position, pos);
	node->next_possible_positions = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
	checkMemoryAllocation(node->next_possible_positions);
	return node;
}

treeNodeListCell* createListCell(treeNode* node)
{
	treeNodeListCell* list = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
	checkMemoryAllocation(list);
	list->node = node;
	return list;
}

void checkMemoryAllocation(void* ptr)
{
	if (ptr == NULL)
	{
		puts("Memory allocation error");
		exit(1);
	}
}

