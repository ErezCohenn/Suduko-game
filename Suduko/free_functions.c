#include "free_functions.h"

void freeProject(WinnersPlayersList* winList, Tree tr, PlayerNode** pArr)
{
	freeWinnersPlayersList(winList);
	free(pArr);
	freeTree(tr);
}

void freeWinnersPlayersList(WinnersPlayersList* lst)
{
	PlayerNode* curr = lst->head, * next;

	while (curr != NULL)
	{
		next = curr->next;
		free(curr);
		curr = next;
		// we already free the possibility board of the player in playSudokuTreeInorderRec function
	}
}

void freeDList(DList* dList)
{
	DListNode* curr = dList->head, * next;

	while (curr != NULL)
	{
		next = curr->next;
		free(curr);
		curr = next;
	}
}

void freePossibilityBoard(Array*** PossibleDigits)
{
	int i, j;

	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
			freeArray(PossibleDigits[i][j]);
	}

	for (i = 0; i < SIZE; i++)
		free(PossibleDigits[i]);

	free(PossibleDigits);
}

void freeArray(Array* cell)
{
	if (cell != NULL)
	{
		free(cell->arr);
	}

	free(cell);
}

void freeTree(Tree tr)
{
	freeTreeRec(tr.root);
}

void freeTreeRec(TreeNode* root)
{
	if (root == NULL)
		return;
	else
	{
		freeTreeRec(root->left);
		freeTreeRec(root->right);
		free(root);
	}
}