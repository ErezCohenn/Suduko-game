#pragma once

#include "assistance_functions.h"
#include "structs_and_const.h"
#include "free_functions.h"
#include <stdbool.h>

void makeEmptyDList(DList* dlst);
void insertNodeToEndDList(DList* dlst, DListNode* newTail);
void insertDataToEndDList(DList* lst, Cell c);
void removeDListNode(DList* corList, DListNode* toRemove);
DListNode* createNewDListNode(Cell c, DListNode* next, DListNode* prev);
bool isEmptyDList(DList lst);
