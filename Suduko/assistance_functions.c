#include "assistance_functions.h"

void mergeSort(PlayerNode* arr[], int size)
{
	PlayerNode** tmpArr = NULL;
	if (size <= 1)
		return;

	mergeSort(arr, size / 2);
	mergeSort(arr + size / 2, size - size / 2);
	tmpArr = merge(arr, size / 2, arr + size / 2, size - size / 2);
	if (tmpArr)
	{
		copyPlayersArr(arr, tmpArr, size); // copy values from tmpArr to arr
		free(tmpArr);
	}
	else
	{
		printf("Memory allocation failure!!!\n");
		exit(1);	// end program immediately with code 1 (indicating an error)
	}
}

PlayerNode** merge(PlayerNode* a1[], int size1, PlayerNode* a2[], int size2) {
	int ind1, ind2, resInd;
	PlayerNode** res = (PlayerNode**)malloc((size1 + size2) * sizeof(PlayerNode*));
	checkAllocation(res);

	if (res)
	{
		ind1 = ind2 = resInd = 0;

		while ((ind1 < size1) && (ind2 < size2)) {
			if (countFullCells(a1[ind1]->player.sudukoBoard) < countFullCells(a2[ind2]->player.sudukoBoard))
			{
				res[resInd] = a1[ind1];
				ind1++;
			}
			else if (countFullCells(a1[ind1]->player.sudukoBoard) > countFullCells(a2[ind2]->player.sudukoBoard))
			{
				res[resInd] = a2[ind2];
				ind2++;
			}
			else // Secondary sorting, the countFullSquares is equal
			{
				if (strcmp(a1[ind1]->player.name, a2[ind2]->player.name) <= 0)
				{
					res[resInd] = a1[ind1];
					ind1++;
				}
				else
				{
					res[resInd] = a2[ind2];
					ind2++;
				}
			}
			resInd++;
		}

		while (ind1 < size1) {
			res[resInd] = a1[ind1];
			ind1++;
			resInd++;
		}
		while (ind2 < size2) {
			res[resInd] = a2[ind2];
			ind2++;
			resInd++;
		}
	}
	return res;
}

void copyPlayersArr(PlayerNode* dest[], PlayerNode* src[], int size)
{
	int i;

	for (i = 0; i < size; i++)
		dest[i] = src[i];
}

int countFullCells(short board[][SIZE])
{
	int i, j, count = 0;

	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			if (board[i][j] != -1)
				count++;
		}
	}

	return count;
}

void copyBoard(short dest[][SIZE], short src[][SIZE])
{
	int i, j;

	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
			dest[i][j] = src[i][j];
	}
}

void printPossibilities(Array*** PossibleDigits, int x, int y)
{
	int i, size = PossibleDigits[x][y]->size;

	for (i = 0; i < size; i++)
	{
		printf("%d. %d\n", i + 1, PossibleDigits[x][y]->arr[i]);
	}
}

void printWinners(WinnersPlayersList winList)
{
	PlayerNode* curr = winList.head;
	int count = 0;

	printf("/*********************************/\n\n");
	printf("The winners are: \n\n");

	while (curr != NULL)
	{
		printf("%s's board: \n", curr->player.name);
		sudokoPrintBoard(curr->player.sudukoBoard);
		curr = curr->next;
		count++;
	}

	if (count == 0)
		printf("There are no winners!!!\n");
}

void sudokoPrintBoard(short board[][SIZE])
{
	int i, j;

	printf("\n\n  |");

	for (i = 0; i < SIZE; i++)
	{
		if ((i + 1) % 3 == 0 && i != SIZE - 1)
			printf("%2d|", i);
		else
			printf("%2d", i);
	}

	printf("\n");

	for (i = 0; i < SIZE; i++)
	{
		if (i % 3 == 0)
		{
			printf("-----------------------\n");
		}

		for (j = 0; j < SIZE + 1; j++)
		{
			if (j == 0)
				printf("%2d|", i);
			else if (board[i][j - 1] == -1)
			{
				if (j % 3 == 0 && j != SIZE)
					printf("  |");
				else
					printf("  ");
			}
			else
			{
				if (j % 3 == 0 && j != SIZE)
					printf("%2d|", board[i][j - 1]);
				else
					printf("%2d", board[i][j - 1]);
			}
		}
		printf("\n");
	}

	printf("-----------------------\n\n\n");
}

int binarySearch(short arr[], unsigned short size, int item)
{
	int ind, left, right, mid;

	left = 0;
	right = size - 1;
	ind = NOT_FOUND;

	while (ind == NOT_FOUND && (left <= right))
	{
		mid = (left + right) / 2;
		if (arr[mid] == item)
			ind = mid;	// found
		else if (arr[mid] < item)
			left = mid + 1;	// search left half
		else
			right = mid - 1; // search right half
	}
	return ind;
}

void checkAllocation(void* ptr)
{
	if (ptr == NULL)
	{
		printf("Allocation error\n");
		exit(-1);
	}
}
