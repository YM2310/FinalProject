#include "Part6.h"
#include "Part2.h"


int checkAndDisplayPathFromFile(char* file_name, movesArray** moves, char** board)
{
	FILE* CHECK = fopen(file_name, "rb");
	if (CHECK == NULL)
		return -1;
	boardPosArray* boardposArr;
	boardposArr = readListfromBinFile(file_name);
	fclose(CHECK);
	movesList pathMoves = makeEmptyList();
	bool validpath = isValidpath(boardposArr, board, moves, &pathMoves);
	int len = boardposArr->size;
	if (validpath)
		display(&pathMoves,boardposArr->positions[0] , board);
	free(boardposArr->positions);
	free(boardposArr);
	free(&pathMoves);
	
	if (!validpath)
		return 1;
	if (countspaces(board) == len)
		return 2;
	else return 3;
}
int countspaces(char** theBoard)
{
	int res = 0;
	for( int i=0;i<N;i++)
	{
		for (int j = 0; j < M; j++)
			if (theBoard[i][j] == SPACE)
				res++;
	}
	return res;
}

boardPosArray* readListfromBinFile(char* file_name)
{
	FILE* file;
	boardPosArray* boardPosArr;
	file = fopen(file_name, "rb");
	assert(file != NULL);
	boardPosArr = readPositions(file);
	fclose(file);
	return boardPosArr;
}

boardPosArray* readPositions(FILE* file)
{
	short int size;
	short int i, j;
	unsigned int mask1 = MASK1, mask2 = MASK2, mask3 = MASK3, mask4 = MASK4;
	unsigned int firstPosbin, secondPosbin, thirdPosbin, fourthPosbin, current4Pos;
	fread(&size, sizeof(short int), 1, file);
	boardPosArray* boardposArr = (boardPosArray*)malloc(sizeof(boardPosArray));
	boardposArr->size = size;
	(boardposArr->positions) = (boardPos*)calloc(size, sizeof(boardPos));
	for (i = 0; i < size / 4; i++)
	{
		j = i * 4;
		current4Pos = 0;
		fread(&current4Pos, sizeof(char), 3, file);
		firstPosbin = (current4Pos & mask1) >> 18;
		boardPos* firstPos = binaryToPos((char)firstPosbin);
		boardposArr->positions[j][0] = (*firstPos)[0];
		boardposArr->positions[j][1] = (*firstPos)[1];
		secondPosbin = (current4Pos & mask2) >> 12;
		boardPos* secondPos = binaryToPos((char)secondPosbin);
		boardposArr->positions[j + 1][0] = (*secondPos)[0];
		boardposArr->positions[j + 1][1] = (*secondPos)[1];
		thirdPosbin = (current4Pos & mask3) >> 6;
		boardPos* thirdPos = binaryToPos((char)thirdPosbin);
		boardposArr->positions[j + 2][0] = (*thirdPos)[0];
		boardposArr->positions[j + 2][1] = (*thirdPos)[1];
		fourthPosbin = current4Pos & mask4;
		boardPos* fourthPos = binaryToPos((char)fourthPosbin);
		boardposArr->positions[j + 3][0] = (*fourthPos)[0];
		boardposArr->positions[j + 3][1] = (*fourthPos)[1];
	}

	j = size - (size % 4);
	if (remain1)
	{
		unsigned char current1Pos = 0;
		fread(&current1Pos, sizeof(char), 1, file);
		firstPosbin = current1Pos >> 2;
		boardPos* firstPos = binaryToPos((char)firstPosbin);
		boardposArr->positions[j][0] = (*firstPos)[0];
		boardposArr->positions[j][1] = (*firstPos)[1];
	}
	if (remain2)
	{
		short int current2Pos = 0;
		short int mask1short = MASK1SHORT;
		short int mask2short = MASK2SHORT;
		fread(&current2Pos, sizeof(char), 2, file);
		firstPosbin = (current2Pos & mask1short) >> 10;
		boardPos* firstPos = binaryToPos((char)firstPosbin);
		boardposArr->positions[j][0] = (*firstPos)[0];
		boardposArr->positions[j][1] = (*firstPos)[1];
		secondPosbin = (current2Pos & mask2short) >> 4;
		boardPos* secondPos = binaryToPos((char)secondPosbin);
		boardposArr->positions[j + 1][0] = (*secondPos)[0];
		boardposArr->positions[j + 1][1] = (*secondPos)[1];
	}

	if (remain3)
	{
		unsigned int current3Pos = 0;
		fread(&current3Pos, sizeof(char), 3, file);
		firstPosbin = (current3Pos & mask1) >> 18;
		boardPos* firstPos = binaryToPos((char)firstPosbin);
		boardposArr->positions[j][0] = (*firstPos)[0];
		boardposArr->positions[j][1] = (*firstPos)[1];
		secondPosbin = (current3Pos & mask2) >> 12;
		boardPos* secondPos = binaryToPos((char)secondPosbin);
		boardposArr->positions[j + 1][0] = (*secondPos)[0];
		boardposArr->positions[j + 1][1] = (*secondPos)[1];
		thirdPosbin = (current3Pos & mask3) >> 6;
		boardPos* thirdPos = binaryToPos((char)thirdPosbin);
		boardposArr->positions[j + 2][0] = (*thirdPos)[0];
		boardposArr->positions[j + 2][1] = (*thirdPos)[1];
	}
	return boardposArr;
}
boardPos* binaryToPos(char binPos)
{
	boardPos* pos = (boardPos*)malloc(sizeof(boardPos));
	char letter, digit, maskletter = 0x38, maskdigit = 0x07;
	letter = (binPos & maskletter) >> 3;
	digit = (binPos & maskdigit);
	(*pos)[0] = (letter + 'A');
	(*pos)[1] = (digit + 1);
	return pos;
}
bool isValidpath(boardPosArray* boardPosarray, char** board, movesArray** moves, movesList* p_list)
{
	bool flag = true;
	boardPos current, next;
	current[0] = boardPosarray->positions[0][0]-'A';
	current[1] = boardPosarray->positions[0][1] -1;
	if (board[current[0]][current[1]] != SPACE)
		flag = false;
	for (unsigned int i = 0; (i < boardPosarray->size) - 1 && flag; i++)
	{
		next[0] = boardPosarray->positions[i + 1][0] - 'A';
		next[1] = boardPosarray->positions[i + 1][1] - 1;
		if (next[0] >= N || next[1] >= M || board[next[0]][next[1]] != SPACE)
			flag = false;
		bool foundMatch = false;
		for (unsigned int j = 0; j < moves[current[0]][current[1]].size && flag && !foundMatch; j++)
		{
			boardPos tempNext;
			getPos(&tempNext, current, moves[current[0]][current[1]].moves[j]);
			if (tempNext[0] == next[0] && tempNext[1] == next[1])
			{
				foundMatch = true;
				insertMovetoEndList(p_list, moves[current[0]][current[1]].moves[j]);
			}

		}
		if (!foundMatch)
			flag = false;
		current[0] = next[0];
		current[1] = next[1];
	}
	return flag;
}
void getPos(boardPos* toChange, boardPos current, Move UpdateCurrent)
{
	(*toChange)[0] = current[0]+UpdateCurrent.rows;
	(*toChange)[1] = current[1] + UpdateCurrent.cols;
}
void insertMovetoEndList(movesList* p_list, Move move_current)
{
	if (p_list->head == NULL && p_list->tail == NULL)
		p_list->head = p_list->tail=createCell(move_current.rows,move_current.cols);
	p_list->tail->next = createCell(move_current.rows, move_current.cols);
	p_list->tail->prev = p_list->tail;
	p_list->tail = p_list->tail->next;
}
moveCell* createCell(char row, char col)
{
	moveCell* res=(moveCell*)calloc(1,sizeof(moveCell));
	assert(res != NULL);
	res->next = res->prev = NULL;
	(res->move).rows = row;
	(res->move).cols = col;
	return res;
}