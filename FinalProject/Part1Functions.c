#include "Types.h"
#include <stdio.h>
#include <stdlib.h>




boardPosArray** validMoves(movesArray** moves, char** board) {

	boardPos origin;

	int i = 0;

	
	for (int row = 0; row < N; row++) {
		for (int col = 0; col < M; col++){

		origin[0] = row;
		origin[1] = col;
		int* remove = (int*)malloc(sizeof(int) * moves[row][col].size); //create array with cells to remove
		int removeIndex = 0;

		for (int i = 0; i < moves[row][col].size; i++) {				// check moves array for illegal moves
			if (isLegal(origin, moves[row][col].moves[i], board) == false) {
				remove[removeIndex] = i;
				removeIndex++;
			}
		}

			removeCells(&moves[row][col].moves, &moves[row][col].size, remove, removeIndex); //remvoe all illegal moves
			/*
			for (int k = 0; k < moves[row][col].size; k++) {
				printf("(%d,%d)", moves[row][col].moves[k].rows, moves[row][col].moves[k].cols);
			}
			*/
			free(remove);
		
		}
	}

	boardPosArray** newBoard=(boardPosArray**)malloc(sizeof(boardPosArray*)*N);
	for (int i = 0; i < N; i++) {
		newBoard[i] = (boardPosArray*)malloc(sizeof(boardPosArray) * M);
		for (int j = 0; j < M; j++) {

			newBoard[i][j].size = moves[i][j].size;
			newBoard[i][j].positions = legalMovesFrom(moves[i][j].moves, moves[i][j].size, i, j);
		}
	}

	return newBoard;


	
}

boardPos* legalMovesFrom(Move* moves, int movesSize, int row, int col) {
	boardPos* positions = (boardPos*)malloc(sizeof(boardPos) * movesSize);
	for (int i = 0; i < movesSize; i++) {
		positions[i][0] = row+moves[i].rows;
		positions[i][1] = col+moves[i].cols;
	}
	return positions;


}

void removeCells(Move** moves, unsigned int* size, int* remove, int howmany) {
	Move* newMoves = (Move*)malloc(sizeof(Move) * (*size - howmany));
	int removeIndex = 0;
	int i = 0;
	int j = 0;



	while(i<*size) {
		if (i != remove[removeIndex]) {
			newMoves[j] = (*moves)[i];
			j++;
			i++;
		}
		else {
			removeIndex++;
			i++;
		}
	}


	free(*moves);
	*size -= howmany;
	*moves = newMoves;



}

bool isLegal(boardPos origin, Move move, char** board) {//checks if the move is legal
	boardPos toCheck;
	toCheck[0] = origin[0] + move.rows;
	toCheck[1] = origin[1] + move.cols;

	if (toCheck[0] > 3 || toCheck[0] < 0 || toCheck[1] > 4 || toCheck[1] < 0)
		return false;
	else {

		if (board[toCheck[0]][toCheck[1]] == '*')
			return false;
		else
			return true;
	}
}