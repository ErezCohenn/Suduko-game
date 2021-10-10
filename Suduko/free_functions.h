#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "structs_and_const.h"

//free functions
void freeProject(WinnersPlayersList* winList, Tree tr, PlayerNode** pArr);
void freeWinnersPlayersList(WinnersPlayersList* lst);
void freeDList(DList* dList);
void freePossibilityBoard(Array*** PossibleDigits);
void freeArray(Array* cell);
void freeTree(Tree tr);
void freeTreeRec(TreeNode* root);
