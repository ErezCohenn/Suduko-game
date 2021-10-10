#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "assistance_functions.h"
#include "free_functions.h"
#include "structs_and_const.h"


//Active players List functions
void insertDataToEndActivePlayersList(ActivePlayersList* lst, char name[], short board[][SIZE], Array*** possibilities);
PlayerNode* createNewActivePlayersListNode(char name[], short board[][SIZE], Array*** possibilities, PlayerNode* prev, PlayerNode* next);
void insertNodeToEndActivePlayersList(ActivePlayersList* lst, PlayerNode* newTail);
void removePlayerNodeFromActivePlayersList(ActivePlayersList* corList, PlayerNode* toRemove);
void makeEmptyActivePlayersList(ActivePlayersList* lst);
bool isEmptyActivePlayersList(ActivePlayersList lst);

//Winners players List functions
bool isEmptyWinList(WinnersPlayersList lst);
void insertNodeToEndWinList(WinnersPlayersList* lst, PlayerNode* newTail);
void makeEmptyWinList(WinnersPlayersList* lst);
