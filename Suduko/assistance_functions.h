#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs_and_const.h"

void mergeSort(PlayerNode* arr[], int size);
PlayerNode** merge(PlayerNode* a1[], int size1, PlayerNode* a2[], int size2);
void copyPlayersArr(PlayerNode* dest[], PlayerNode* src[], int size);
int countFullCells(short board[][SIZE]);
void copyBoard(short dest[][SIZE], short src[][SIZE]);
void sudokoPrintBoard(short board[][SIZE]);
void printPossibilities(Array*** PossibleDigits, int x, int y);
void printWinners(WinnersPlayersList winList);
int binarySearch(short arr[], unsigned short size, int item);
void checkAllocation(void* ptr);