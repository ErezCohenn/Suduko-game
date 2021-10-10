/*
sudoku.c
Erez Cohen - 316098219
Dor Raba - 208851741
DATE : 28/08/2021
This project simulates the game Sudoku
*/

#include "structs_and_const.h"
#include "tree_functions.h"
#include"free_functions.h"
#include "main_functions.h"

void main()
{
	int size;
	srand(12345);

	ActivePlayersList activePlayersList = makeActivePlayersList(&size);
	PlayerNode** pArr = makePointersArrToList(&activePlayersList, &size);
	Tree tr = BuildTreeFromArray(pArr, size);
	WinnersPlayersList winList;

	makeEmptyWinList(&winList);

	playSudokuTreeInorder(tr, &activePlayersList, &winList);
	
	printWinners(winList);
	
	freeProject(&winList, tr, pArr);
}
