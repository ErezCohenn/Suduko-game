#include "main_functions.h"

int OneStage(short board[][SIZE], Array*** possibilities, int* x, int* y)
{
	int i, j, countUnEmptyCell = 0, minPossibilities = SIZE + 1; // minPosibillities > max(possibilities[i][j]->size)
	bool filled_at_least_one_Cell = false;
	Cell tmpCell;

	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			if (board[i][j] == -1) // found empty cell
			{
				if (possibilities[i][j] == NULL) // empty cell that dont have any possibilities left
				{
					return FINISH_FAILURE;
				}
				else if (possibilities[i][j]->size == 1) // found cell that have only one possibility
				{
					board[i][j] = possibilities[i][j]->arr[0];
					possibilities[i][j]->arr[0] = 0; // init possibility for removing
					removePossibility(&possibilities[i][j]);
					updatePossibilities(board, possibilities, i, j);
					filled_at_least_one_Cell = true;
					countUnEmptyCell++;
				}
				else if (possibilities[i][j]->size < minPossibilities) // get the Cell with the minimum possibilities for case filled_at_least_one_Cell = false
				{
					minPossibilities = possibilities[i][j]->size;
					tmpCell.x = i;
					tmpCell.y = j;
				}
			}
			else
				countUnEmptyCell++;
		}
	}

	if (countUnEmptyCell == SIZE * SIZE) // the board is full and valid
		return FINISH_SUCCESS;
	else if (filled_at_least_one_Cell) // the board is not full, then scan again for Cell with only one possibility
	{
		return OneStage(board, possibilities, x, y);
	}
	else // there is no Cell with only one possibility and the board is not full
	{
		*x = tmpCell.x;
		*y = tmpCell.y;
		return NOT_FINISH;
	}
}
// This function updates the row, col and square that in the same Cell with (row,col)
void updatePossibilities(short board[][SIZE], Array*** possibilities, int row, int col)
{
	int i, j, delPossibility = board[row][col];

	for (i = 0; i < SIZE; i++) // update possibilities in the same Row
	{
		updateCellPossibilities(board, possibilities, row, i, delPossibility);
	}

	for (i = 0; i < SIZE; i++) // update possibilities in the same Col
	{
		updateCellPossibilities(board, possibilities, i, col, delPossibility);
	}

	// initialize row + col in order to update from the first cell in the Square 3X3
	row = row - (row % 3);
	col = col - (col % 3);

	for (i = row; i < row + 3; i++) //update possibilities that in the same Square 3X3
	{
		for (j = col; j < col + 3; j++)
		{
			updateCellPossibilities(board, possibilities, i, j, delPossibility);
		}
	}
}

void updateCellPossibilities(short board[][SIZE], Array*** possibilities, int row, int col, int delPossibility)
{
	int ind;

	if (board[row][col] == -1 && possibilities[row][col] != NULL)
	{
		ind = binarySearch(possibilities[row][col]->arr, possibilities[row][col]->size, delPossibility); // find the index of delPossibility in arr

		if (ind != NOT_FOUND)
		{
			possibilities[row][col]->arr[ind] = 0;
			removePossibility(&(possibilities[row][col]));
		}
	}
}

Array*** PossibleDigits(short sudokuBoard[][9])
{
	Array*** arr = (Array***)malloc(sizeof(Array**) * SIZE);
	checkAllocation(arr);

	int i = 0, j;
	for (i = 0; i < SIZE; i++) // malloc memory for possibility board 9X9
	{
		arr[i] = (Array**)malloc(sizeof(Array*) * SIZE);
		checkAllocation(arr[i]);
	}

	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			if (sudokuBoard[i][j] == -1) // found empty cell
				creatArrayP(&arr[i][j]);
			else
				arr[i][j] = NULL;
		}
	}

	//create random board
	pickRan(sudokuBoard, arr);

	return arr;
}

// This function creats pointer to new Array struct for cell
void creatArrayP(Array** array)
{
	int i;
	*array = (Array*)malloc(sizeof(Array));
	checkAllocation(*array);

	(*array)->arr = (short*)malloc(sizeof(short) * SIZE);
	checkAllocation((*array)->arr);

	for (i = 0; i < SIZE; i++) //create an array with all the digits (1 - 9)
		(*array)->arr[i] = i + 1;
	(*array)->size = SIZE;

}

//remove all the emptey slot(contains zero)
void removePossibility(Array** array)
{
	int i, k = 0;
	for (i = 0; i + k < (*array)->size; i++)
	{
		while (i + k < (*array)->size && ((*array)->arr)[i + k] == 0) //if found zero advance k by one
			k++;
		if (k > 0 && i + k < (*array)->size)
			((*array)->arr)[i] = ((*array)->arr)[i + k];
	}

	if (k > 0 && k < (*array)->size)
		(*array)->arr = (short*)realloc((*array)->arr, ((*array)->size - k) * sizeof(short));

	(*array)->size = (*array)->size - k;

	if ((*array)->size == 0)
	{
		freeArray(*(array));
		*array = NULL;
	}
}

ActivePlayersList makeActivePlayersList(int* size)
{
	ActivePlayersList lst;
	Array*** possibilities;
	int numOfPlayers, i;
	char name[MAX_LEN_NAME];
	short board[SIZE][SIZE];

	makeEmptyActivePlayersList(&lst);

	printf("Please enter the number of players: ");
	scanf("%d", &numOfPlayers);
	getchar();

	for (i = 0; i < numOfPlayers; i++)
	{
		printf("\nPlayer %d, please enter your first name: ", i + 1);
		scanf("%s", name);

		initsudokuBoard(board);
		possibilities = PossibleDigits(board);

		insertDataToEndActivePlayersList(&lst, name, board, possibilities);
	}

	*size = numOfPlayers;

	return lst;
}

// This function creats empty sudoku board
void initsudokuBoard(short board[][SIZE])
{
	int i, j;

	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			board[i][j] = -1;
		}
	}
}

//This function creats pointers Arr to Active players List
PlayerNode** makePointersArrToList(ActivePlayersList* lst, int* size)
{
	int i, newSize;
	PlayerNode* curr = lst->head;
	PlayerNode** playersArr = (PlayerNode**)malloc(sizeof(PlayerNode*) * (*size));
	checkAllocation(playersArr);

	for (i = 0; i < (*size); i++)
	{
		playersArr[i] = curr;
		curr = curr->next;
	}

	mergeSort(playersArr, (*size));

	newSize = pow(2, ceil(log((*size) + 1.0) / log(2))) - 1; // new size for tree players
	playersArr = realloc(playersArr, newSize * sizeof(Player));

	for (i = (*size); i < newSize; i++) 
		playersArr[i] = NULL;

	*size = newSize;

	return playersArr;
}