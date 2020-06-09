#include "Header.h"
#include <stdlib.h>


movesList* findPathCoveringAllBoard(boardPos start, movesArray** moves, char** board) {
	int max_route_length = N * M - howManyIlegal(board);
	pathTree path_tree = findAllPossiblePaths(start, moves, board);
	posList full_board;
	full_board.head = longestPathRec(path_tree.head, max_route_length - 1);
	if (full_board.head != NULL)
		return PosListToMoveList(full_board);
	else
		return NULL;
	
	


	/*
	turn to tree using part 3 function
	save route
	check next route
	if longer release old one save new one
	else release new one
	if route == N*M-numof(*) return route
	*/



}

movesList* PosListToMoveList(posList pos_list) {
	movesList* moves_list= (movesList*)malloc(sizeof(movesList));
	posCell* pos_temp = pos_list.head;

	char row = pos_temp->next->pos[0] -pos_temp->pos[0];
	char col = pos_temp->next->pos[1] - pos_temp->pos[1];
	pos_temp = pos_temp->next;
	moves_list->head = createsmoveCell(row, col,NULL,NULL);//change to real function later
	moveCell* temp = moves_list->head;


	while (pos_temp->next != NULL) {
		
		row = pos_temp->next->pos[0] - pos_temp->pos[0];
		col = pos_temp->next->pos[1] - pos_temp->pos[1];
		pos_temp = pos_temp->next;
		temp->next = createsmoveCell(row, col, NULL, NULL);
		temp->next->prev = temp;
		temp = temp->next;


	}
	moves_list->tail = temp;
	return moves_list;
}
/*recursive function. goes thru the tree until it reaches the level inputed in moves_left. returns the first path with that many moves*/
posCell* longestPathRec(treeNode* head, int moves_left) {

	posCell* longest = createPosCell(head->position);
	treeNodeListCell* current= head->next_possible_positions;

	if (moves_left == 0) {
		return longest;
	}

	if (current == NULL) {
		free(longest);
		return NULL;
	}

	while (current != NULL) {
		longest->next = longestPathRec(current->node, moves_left - 1);
		if (longest->next != NULL) {
			return longest;
		}
		current = current->next;
	}
	free(longest);
	return NULL;
	
}

posCell* createPosCell(boardPos pos) {
	posCell* new_pos_cell = (posCell*)malloc(sizeof(posCell));
	new_pos_cell->pos[0] = pos[0];
	new_pos_cell->pos[1] = pos[1];
	new_pos_cell->next = NULL;
	return new_pos_cell;
}


int howManyIlegal(char** board) {
	int count = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (board[i][j] == '*')
				count++;
		}
	}
	return count;
}