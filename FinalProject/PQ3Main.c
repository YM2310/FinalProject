#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "PQ3Header.h"


void main()
{
	Test();
}

void Test()
{
	char** gameBoard = createsGameBoard();
	movesArray** movesA = createsMovesArray();
	char str[] = "A2";

	pathTree tree = findAllPossiblePaths(str, movesA, gameBoard);
	PrintMove(tree);

	freeGameBoardAlocc(gameBoard);
	freeMovesAlocc(movesA);
}

char** createsGameBoard()
{
	char** gameBoard = (char**)malloc(N * sizeof(char*));
	checkMemoryAllocation(gameBoard);
	for (int i = 0; i < N; i++)
	{
		gameBoard[i] = (char*)malloc(M * sizeof(char));
		checkMemoryAllocation(gameBoard[i]);
	}

	for (unsigned int row = 0; row < N; row++)
	{
		for (unsigned int col = 0; col < M; col++)
		{
			if ((row == 4 && col == 0) || (row == 0 && col == 3) || (row == 3 && col == 5) || (row == 1 && col == 7))
				gameBoard[row][col] = '*';
			else
				gameBoard[row][col] = ' ';
			printf(" %c ", gameBoard[row][col]);
		}
		printf("\n");
	}
	return gameBoard;
}

movesArray** createsMovesArray()
{
	movesArray** movesA = (movesArray**)malloc(N * sizeof(movesArray*));
	checkMemoryAllocation(movesA);
	for (int i = 0; i < N; i++)
	{
		movesA[i] = (movesArray*)malloc(M * sizeof(movesArray));
		checkMemoryAllocation(movesA[i]);
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			movesA[i][j].size = 0;
			printf("(%c, %c): ", i + 65, j + 49);
			if (i == 0 && j == 1)
			{
				movesA[i][j].size = 4;
				movesA[i][j].moves = (Move*)malloc(movesA[i][j].size * sizeof(Move));
				checkMemoryAllocation(movesA[i][j].moves);
				movesA[i][j].moves[0].rows = 2;
				movesA[i][j].moves[0].cols = -1;
				movesA[i][j].moves[1].rows = 2;
				movesA[i][j].moves[1].cols = 1;
				movesA[i][j].moves[2].rows = 1;
				movesA[i][j].moves[2].cols = 2;
				movesA[i][j].moves[3].rows = 4;
				movesA[i][j].moves[3].cols = -1;
			}
			if (i == 2 && j == 2)
			{
				movesA[i][j].size = 3;
				movesA[i][j].moves = (Move*)malloc(movesA[i][j].size * sizeof(Move));
				checkMemoryAllocation(movesA[i][j].moves);
				movesA[i][j].moves[0].rows = -2;
				movesA[i][j].moves[0].cols = -1;
				movesA[i][j].moves[1].rows = -1;
				movesA[i][j].moves[1].cols = 5;
				movesA[i][j].moves[2].rows = 1;
				movesA[i][j].moves[2].cols = 3;
			}
			if (i == 1 && j == 3)
			{
				movesA[i][j].size = 6;
				movesA[i][j].moves = (Move*)malloc(movesA[i][j].size * sizeof(Move));
				checkMemoryAllocation(movesA[i][j].moves);
				movesA[i][j].moves[0].rows = 1;
				movesA[i][j].moves[0].cols = -2;
				movesA[i][j].moves[1].rows = 2;
				movesA[i][j].moves[1].cols = -1;
				movesA[i][j].moves[2].rows = 2;
				movesA[i][j].moves[2].cols = 1;
				movesA[i][j].moves[3].rows = 1;
				movesA[i][j].moves[3].cols = 2;
				movesA[i][j].moves[4].rows = -1;
				movesA[i][j].moves[4].cols = 2;
				movesA[i][j].moves[5].rows = 3;
				movesA[i][j].moves[5].cols = -3;
			}
			if (i == 2 && j == 0)
			{
				movesA[i][j].size = 5;
				movesA[i][j].moves = (Move*)malloc(movesA[i][j].size * sizeof(Move));
				checkMemoryAllocation(movesA[i][j].moves);
				movesA[i][j].moves[0].rows = 2;
				movesA[i][j].moves[0].cols = 1;
				movesA[i][j].moves[1].rows = 1;
				movesA[i][j].moves[1].cols = 2;
				movesA[i][j].moves[2].rows = -1;
				movesA[i][j].moves[2].cols = 2;
				movesA[i][j].moves[3].rows = 0;
				movesA[i][j].moves[3].cols = 0;
				movesA[i][j].moves[4].rows = 1;
				movesA[i][j].moves[4].cols = 5;
			}
			if (i == 2 && j == 5)
			{
				movesA[i][j].size = 3;
				movesA[i][j].moves = (Move*)malloc(movesA[i][j].size * sizeof(Move));
				checkMemoryAllocation(movesA[i][j].moves);
				movesA[i][j].moves[0].rows = -1;
				movesA[i][j].moves[0].cols = -2;
				movesA[i][j].moves[1].rows = -2;
				movesA[i][j].moves[1].cols = -2;
				movesA[i][j].moves[2].rows = 0;
				movesA[i][j].moves[2].cols = 2;
			}
			for (int k = 0; k < movesA[i][j].size; k++)
			{
				printf("(%c, %c) ", movesA[i][j].moves[k].rows + 65 + i, movesA[i][j].moves[k].cols + 49 + j);
			}
			printf("   ");
		}
		printf("\n");
	}
	return movesA;
}

void PrintMove(pathTree tree)
{
	treeNode* node = tree.head;
	printf("start (%s): moves : \n", node->position);
	PrintMoveRec(node);
}

void PrintMoveRec(treeNode* node)
{
	treeNodeListCell *ptr = node->next_possible_positions;
	treeNodeListCell *ptr2 = NULL;
	while (ptr != NULL)
	{
		printf(" parent (%s) pos (%s): moves :\n", node->position, ptr->node->position);
		ptr2 = ptr->node->next_possible_positions;
		while (ptr2 != NULL)
		{
			if (ptr2->node->next_possible_positions == NULL)
				printf(" %s \n", ptr2->node);
			else
			{
				printf(" %s \n", ptr2->node);
				PrintMoveRec(ptr2->node);
			}
			ptr2 = ptr2->next;
		}
		ptr = ptr->next;
	}
}

void freeGameBoardAlocc(char** gameBoard)
{
	for (int i = 0; i < N; i++)
	{
		free(gameBoard[i]);
	}
	free(gameBoard);
}

void freeMovesAlocc(movesArray** arr)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (arr[i][j].size < 0)
				free(arr[i][j].moves);
		}
		free(arr[i]);
	}
	free(arr);
}
