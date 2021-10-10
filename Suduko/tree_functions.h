#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "players_list.h"
#include "free_functions.h"
#include "main_functions.h"
#include "structs_and_const.h"

// Tree functions
Tree BuildTreeFromArray(PlayerNode** arr, int size);
TreeNode* BuildTreeFromArrayRec(PlayerNode** arr, int leftInd, int rightInd);
TreeNode* createNewTreeNode(PlayerNode** data, TreeNode* left, TreeNode* right);
void playSudokuTreeInorder(Tree tr, ActivePlayersList* activePlayersList, WinnersPlayersList* winList);
void playSudokuTreeInorderRec(TreeNode* root, ActivePlayersList* activePlayersList, WinnersPlayersList* winList);
void freeTree(Tree tr);
void freeTreeRec(TreeNode* root);
