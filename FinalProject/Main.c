
#include "FullHeader.h"
void printlist(movesList* list);
movesArray** createMovesArraytest();
void part4test1();
char** createBoardtest();
int part1test();


int main() {
	part1test();

}

void part4test1() {
	boardPos pos;
	pos[0] = 'A';
	pos[1] = '1';
	char** board = createBoardtest();
	movesArray** moves = createMovesArraytest();
	printlist(findPathCoveringAllBoard(pos,moves,board));
}
movesArray** createMovesArraytest(){
		movesArray** moves = (movesArray**)malloc(sizeof(movesArray*) * N);
	for (int i = 0; i < N; i++)
		moves[i] = (movesArray*)calloc(sizeof(movesArray) , M);

	moves[0][0].moves = (Move*)malloc(sizeof(Move) * 2); 
	moves[0][0].moves[0].rows = 0;
	moves[0][0].moves[0].cols = 4;
	moves[0][0].moves[1].rows = 1;
	moves[0][0].moves[1].cols = 1;
	moves[0][0].size = 2;


	moves[0][4].moves = (Move*)malloc(sizeof(Move) * 2);
	moves[0][4].moves[0].rows = 0;
	moves[0][4].moves[0].cols = -3;
	moves[0][4].moves[1].rows = 2;
	moves[0][4].moves[1].cols = -4;
	moves[0][4].size = 2;

	moves[1][1].moves = (Move*)malloc(sizeof(Move) * 1);
	moves[1][1].moves[0].rows = -1;
	moves[1][1].moves[0].cols = 0;
	moves[1][1].size = 1;

	moves[2][0].moves = (Move*)malloc(sizeof(Move) * 1);
	moves[2][0].moves[0].rows = -1;
	moves[2][0].moves[0].cols = 1;
	moves[2][0].size = 1;

	return moves;
}

char** createBoardtest(){
	char** board = (char**)malloc(sizeof(char*) * N);
	int count = 0;

	for (int i = 0; i < N; i++)
		board[i] = (char*)malloc(sizeof(char) * M);


	board[0][0] = "";
	board[0][1] = "";
	board[0][2] = '*';
	board[0][3] = '*';
	board[0][4] = "";

	board[1][0] = '*';
	board[1][1] = "";
	board[1][2] = '*';
	board[1][3] = '*';
	board[1][4] = '*';

	board[2][0] = "";
	board[2][1] = '*';
	board[2][2] = '*';
	board[2][3] = '*';
	board[2][4] = '*';

	board[3][0] = '*';
	board[3][1] = '*';
	board[3][2] = '*';
	board[3][3] = '*';
	board[3][4] = '*';
	return board;

}


void printlist(movesList* list) {
	if (list == NULL) {
		printf("NULL");
	}
	moveCell* print = list->head;

	while (print != NULL) {
		printf("(%d,%d)-->", print->move.rows, print->move.cols);
		print = print->next;
	}
}

int part1test() {
	char** board = (char**)malloc(sizeof(char*) * N);
	int count = 0;

	for (int i = 0; i < N; i++)
		board[i] = (char*)malloc(sizeof(char) * M);
	movesArray** moves = (movesArray**)malloc(sizeof(movesArray*) * N);
	for (int i = 0; i < N; i++)
		moves[i] = (movesArray*)malloc(sizeof(movesArray) * M);


	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (j == i) {
				board[i][j] = '*';
			}
			else
				board[i][j] = ' ';
		}
	}


	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			moves[i][j].moves = (Move*)malloc(sizeof(Move) * 4);

			moves[i][j].moves[0].rows = 1;
			moves[i][j].moves[0].cols = 1;

			moves[i][j].moves[1].rows = 5;
			moves[i][j].moves[1].cols = 6;

			moves[i][j].moves[2].rows = 3;
			moves[i][j].moves[2].cols = 0;

			moves[i][j].moves[3].rows = -2;
			moves[i][j].moves[3].cols = -3;
			moves[i][j].size = 4;
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			printf("|%c|", board[i][j]);
		}
		printf("\n");
	}

	boardPosArray** newBoard = validMoves(moves, board);


	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			printf("(%d,%d):", i, j);
			for (int k = 0; k < newBoard[i][j].size; k++) {
				printf("(%c,%c)", newBoard[i][j].positions[k][0], newBoard[i][j].positions[k][1]);
			}
			printf("\n");
		}
		printf("\n");
	}
}

int part5test() {

	char** board = (char**)malloc(sizeof(char*) * N);
	int count = 0;

	for (int i = 0; i < N; i++)
		board[i] = (char*)malloc(sizeof(char) * M);

	boardPosArray* pos_arr = (boardPosArray*)malloc(sizeof(boardPosArray));
	pos_arr->size = 5;
	pos_arr->positions = (boardPos*)malloc(sizeof(boardPos) * pos_arr->size);
	pos_arr->positions[0][0] = 3;
	pos_arr->positions[0][1] = 5;
	pos_arr->positions[1][0] = 1;
	pos_arr->positions[1][1] = 4;
	pos_arr->positions[2][0] = 2;
	pos_arr->positions[2][1] = 3;
	pos_arr->positions[3][0] = 4;
	pos_arr->positions[3][1] = 1;
	pos_arr->positions[4][0] = 5;
	pos_arr->positions[4][1] = 3;

	saveListToBinFile("LIE.bin", pos_arr);
	FILE* f = fopen("LIE.bin", "rb");
	int size;

	fread(&size, sizeof(int), 1, f);
	BYTE* bit_arr = (BYTE*)malloc((size * 6 / 8) + 1);
	fread(bit_arr, 1, (size * 6 / 8) + 1, f);

	bitarraytest(bit_arr, (size * 6 / 8) + 1);



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
