#include "tree_functions.h"

Tree BuildTreeFromArray(PlayerNode** arr, int size)
{
	Tree tr;

	tr.root = BuildTreeFromArrayRec(arr, 0, size - 1);

	return tr;
}

TreeNode* BuildTreeFromArrayRec(PlayerNode** arr, int leftInd, int rightInd)
{
	if (rightInd < leftInd)
		return NULL;
	else
	{
		TreeNode* left, * right, * root;
		int middle = (leftInd + rightInd) / 2;
		
		left = BuildTreeFromArrayRec(arr, leftInd, middle - 1);
		right = BuildTreeFromArrayRec(arr, middle + 1, rightInd);

		root = createNewTreeNode(&arr[middle], left, right);

		return root;
		
	}
}

TreeNode* createNewTreeNode(PlayerNode** data, TreeNode* left, TreeNode* right)
{
	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
	checkAllocation(node);

	node->data = data;
	node->left = left;
	node->right = right;

	return node;
}

void playSudokuTreeInorder(Tree tr, ActivePlayersList* activePlayersList, WinnersPlayersList* winList)
{
	while (!isEmptyActivePlayersList(*(activePlayersList)))
	{
		playSudokuTreeInorderRec(tr.root, activePlayersList, winList);
	}
}

void playSudokuTreeInorderRec(TreeNode* root, ActivePlayersList* activePlayersList, WinnersPlayersList* winList)
{
	if (root == NULL)
		return;
	else
	{
		int x, y, res;

		playSudokuTreeInorderRec(root->left, activePlayersList, winList); // go to left node

		if ((*root->data) != NULL) // found active player
		{
			res = OneStage((*root->data)->player.sudukoBoard, (*root->data)->player.possibilities, &x, &y);

			if (res == FINISH_FAILURE)
			{
				printf("%s selections led to duplications\n\n", (*root->data)->player.name);
				removePlayerNodeFromActivePlayersList(activePlayersList, (*root->data)); // remove player from active players List
				free((*root->data)); // free PlayerNode
				(*root->data) = NULL;

			}
			else if (res == FINISH_SUCCESS)
			{
				printf("%s's board filled succesfully\n\n", (*root->data)->player.name);
				removePlayerNodeFromActivePlayersList(activePlayersList, (*root->data)); // remove player from active players List
				insertNodeToEndWinList(winList, (*root->data)); // insert player to winners player list
				(*root->data) = NULL;
			}
			else // res == NOT_FINISH
			{
				printf("%s turn: \n", (*root->data)->player.name);
				sudokoPrintBoard((*root->data)->player.sudukoBoard);
				printf("Cell number [%d,%d] currently holds the minimum number of possible values, select one of the below:\n", x, y);
				printPossibilities((*root->data)->player.possibilities, x, y);
				scanf("%hd", &(*root->data)->player.sudukoBoard[x][y]); // insert value from the player and put it in the cell (x,y)
				freeArray((*root->data)->player.possibilities[x][y]);
				(*root->data)->player.possibilities[x][y] = NULL;
				printf("Updating cell %d with value %d\n\n", x * SIZE + y, (*root->data)->player.sudukoBoard[x][y]);
				updatePossibilities((*root->data)->player.sudukoBoard, (*root->data)->player.possibilities, x, y);
			}
		}

		playSudokuTreeInorderRec(root->right, activePlayersList, winList); // go to right node
	}
}
