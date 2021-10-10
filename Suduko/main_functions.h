#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include "free_functions.h"
#include "assistance_functions.h"
#include "players_list.h"
#include "random_board_functions.h"
#include "structs_and_const.h"

Array*** PossibleDigits(short sudokuBoard[][9]);
void creatArrayP(Array** array);
void removePossibility(Array** array);
int OneStage(short board[][SIZE], Array*** possibilities, int* x, int* y);
void updatePossibilities(short board[][SIZE], Array*** possibilities, int row, int col);
void updateCellPossibilities(short board[][SIZE], Array*** possibilities, int row, int col, int delPossibility);
void initsudokuBoard(short board[][SIZE]);
ActivePlayersList makeActivePlayersList(int* size);
PlayerNode** makePointersArrToList(ActivePlayersList* lst, int* size);
