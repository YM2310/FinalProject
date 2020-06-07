#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"
#include <stdio.h>
#include <stdlib.h>


int main() {


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
				printf("(%d,%d)", newBoard[i][j].positions[k][0], newBoard[i][j].positions[k][1]);
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