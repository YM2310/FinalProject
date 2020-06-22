#include "HeaderFile.h"

void main()
{
	char board[ROWS][COLS] = {  {' ',' ','*', ' ',' '},
								{' ',' ',' ', ' ',' '},
								{' ',' ',' ', ' ',' '},
								{' ',' ',' ', ' ',' '}};
	char start_position[2] = { 'B','2' };
	movesList templist = makeEmptyList();
	moveCell* a = createsmoveCell(1, 0, NULL,NULL);
	moveCell* b = createsmoveCell(1, 0, NULL, NULL);
	moveCell* c = createsmoveCell(1, 0, NULL, NULL);
	moveCell* d = createsmoveCell(1, 0, NULL, NULL);
	a->next = b;
	b->next = c;
	c->next = d;
	d->next = NULL;
	d->prev = c;
	c->prev = b;
	b->prev = a;
	a->prev = NULL;
	templist.head = createsmoveCell(0, 0, a, NULL);
	templist.head = createsmoveCell(0, 0, NULL, d);



	reveal(&templist, start_position, board);
}