#include "random_board_functions.h"

// This functions create random board
void pickRan(short board[][SIZE], Array*** possible_solutions)
{
	int i = 0, j = 0, num, max;
	DListNode* curr;
	DList corList;
	Cell c;
	
	max = rand() % 20 + 1; // get the random count of cell to fill
	makeEmptyDList(&corList);

	for (i = 0; i < SIZE; i++) // create DList with the coordinate(row,col) for every cell
	{
		c.x = i;
		for (j = 0; j < SIZE; j++)
		{
			c.y = j;
			insertDataToEndDList(&corList, c);
		}
	}

	for (j = 0; j < max; j++)
	{
		curr = corList.head;
		num = rand() % (81 - j) + 1; // rand cell 
		for (i = 1; i < num; i++) // search for the cell in DList
			curr = curr->next;
		c = curr->c;
		removeDListNode(&corList, curr);
		randomCell(board, possible_solutions, c);
	}

	freeDList(&corList);
}

// This function get cell and put random value in the cell
void randomCell(short board[][SIZE], Array*** possibilities, Cell cl)
{
	int size, randomInd;

	size = possibilities[cl.x][cl.y]->size;
	randomInd = rand() % size; // get random index 
	board[cl.x][cl.y] = possibilities[cl.x][cl.y]->arr[randomInd];
	freeArray(possibilities[cl.x][cl.y]);
	possibilities[cl.x][cl.y] = NULL;
	updatePossibilities(board, possibilities, cl.x, cl.y);
}
