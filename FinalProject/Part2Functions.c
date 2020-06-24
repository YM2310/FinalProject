#include "Part2.h"

void Free_list(movesList l)
{
	free_list(l.head);
}

void free_list(moveCell *head)
{
	moveCell *currCell = head;
	moveCell *temp = NULL;
	while (currCell!= NULL)
	{
		temp = currCell;
		currCell = currCell->next;
		free(temp);
	}
}

movesList makeEmptyList()
{
	movesList result;
	result.head = createsmoveCell(0, 0, NULL, NULL);
	return result;
}

void RemoveFromList(moveCell* after)
{
	moveCell* toDelete;
	toDelete = after->next;
	after->next = toDelete->next;
	free(toDelete);
}

moveCell* createsmoveCell(char row, char col , moveCell* next, moveCell* prev)
{
	moveCell *result;
	result = (moveCell*)malloc(sizeof(moveCell));
	result->move.rows = row;
	result->move.cols = col;
	result->next = next;
	result->prev = prev;
	return result;
}

void addMoves(movesList* moves_list, char** mirror, boardPos start, int* erasedMoves)
{
	moveCell* currNode = moves_list->head->next;
	char currMove = 1; 
	int currRow = start[0] - 'A';
	int currCol = start[1] - '0';
	int calRow = 0, calCol = 0;
	while (currNode != moves_list->tail)
	{
		calRow = currRow + (currNode->move.rows - 'A');
		calCol = currCol + (currNode->move.cols - '0');
		if (mirror[calRow][calCol] != SPACE)
		{
			RemoveFromList(currNode->prev);
			*erasedMoves += 1;
		}
		else
		{
			mirror[calRow][calCol] = currMove;
			currRow = calRow;
			currCol = calCol;
			currMove++;
		}
		currNode = currNode->next;
	}
}


void boardCopy(char** board, char** dest, boardPos start) {
	int i = 0, j = 0;
	for (i = 0; i < N + 1; i++)
		for (j = 0; j < M + 1; j++)
		{
			if (i == 0)
				if (j == 0)
					dest[i][j] = SPACE;
				else
					dest[i][j] = ('1' + j);
			else
			{
				if (j == 0)
					dest[i][j] = 'A' + i;
				else
				{
					if (board[i][j] == '*')
						dest[i][j] = ASTERISK;
					else if (start[0] - '0' == i && start[1] - 'A' == j)
						dest[i][j] = HASH;
					else
						dest[i][j] = SPACE;
				}
			}
		}
}

void swapMove(Move* a, Move* b)
{
	Move temp = *a;
	*a = *b;
	*b = temp;
}

int display(movesList *moves_list, boardPos start, char **board)
{
	int erasedMoves = 0;
	int i = 0, j = 0;
	char mirror[N + 1][M + 1];
	boardCopy(board, mirror, start);
	addMoves(moves_list, mirror, start,&erasedMoves);
	for ( i = 0; i < N + 1; i++)
		for (j = 0; j < M + 1; j++)
		{
			if (mirror[i][j] == HASH)
				printf("#\t");
			else if (mirror[i][j] == ASTERISK)
				printf("*\t");
			else if (mirror[i][j] == SPACE)
				printf(" \t");
			else
				printf("%d", mirror[i][j]);
		}
	return erasedMoves;
}

boardPosArray** movesToBoardPos(movesArray** moves)
{
	int i, j;
	boardPosArray** pos = (boardPosArray**)malloc(sizeof(boardPosArray*) * N * M);
	for (i = 0; i < N; i++)
		pos[i] = (boardPosArray*)malloc(sizeof(boardPosArray) * M);
	for (i = 0; i < N; i++)
		for (j = 0; j < M; j++)
		{
			pos[i][j].positions = (boardPos*)malloc(sizeof(boardPos) * (moves[i][j].size));
			pos[i][j].size = moves[i][j].size;
			convertToPosition(i, j, moves, pos[i][j].positions);
		}
	return pos;
}


void convertToPosition(int i, int j, movesArray** moves, boardPos* position)
{
	int sumCol = 0, sumRow = 0;
	int k;
	for ( k = 0;  k < moves[i][j].size;  k++)
	{
		sumCol = j + moves[i][j].moves[k].cols;
		sumRow = i + moves[i][j].moves[k].rows;
		position[k][0] = 'A' + sumRow;
		position[k][1] = '1' + sumCol;
	}
}

boardPosArray** PossibleValidMoves(movesArray** moves, char** board)
{
	int i, j, sumRow = 0, sumCol = 0, countWrong = 0;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
		{
			countWrong = 0;
			int currSize = moves[i][j].size;
			validMovesByCell(moves, board, i, j, &countWrong);
			if (countWrong != currSize - 1)
			{
				moves[i][j].moves = realloc(moves[i][j].moves, sizeof(Move) * (currSize - countWrong));
				moves[i][j].size = currSize - countWrong;
			}
		}
	}
	return movesToBoardPos(moves);
}

void validMovesByCell(movesArray **moves, char **board, int i, int j, int* countWrong)
{
	int k, sumCol = 0, sumRow = 0;
	int currSize = moves[i][j].size;
	for (k = 0; k < currSize; k++)
	{
		sumCol = j + moves[i][j].moves[k].cols;
		sumRow = i + moves[i][j].moves[k].rows;
		if (sumRow >= N || sumRow < 0 || sumCol >= M || sumCol < 0)
		{
			swapMove(&(moves[i][j].moves[k]), &(moves[i][j].moves[currSize - 1 - (*countWrong)]));
			k--;
			(*countWrong)++;
		}
		else if (board[sumRow][sumCol] == '*')
		{
			swapMove(&(moves[i][j].moves[k]), &(moves[i][j].moves[currSize - 1 - (*countWrong)]));
			k--;
			(*countWrong)++;
		}
		if ((*countWrong) == currSize - 1)
		{
			free(moves[i][j].moves);
			moves[i][j].moves = NULL;
			moves[i][j].size = 0;
			break;
		}
	}
}


