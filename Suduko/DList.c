#include "DList.h"

void insertNodeToEndDList(DList* dlst, DListNode* newTail)
{
	if (isEmptyDList(*dlst))
		dlst->head = dlst->tail = newTail;
	else
	{
		newTail->prev = dlst->tail;
		newTail->next = NULL;
		dlst->tail->next = newTail;
		dlst->tail = newTail;
	}
}

DListNode* createNewDListNode(Cell c, DListNode* next, DListNode* prev)
{
	DListNode* node = (DListNode*)malloc(sizeof(DListNode));
	checkAllocation(node);

	node->c = c;
	node->next = next;
	node->prev = prev;

	return node;
}

void insertDataToEndDList(DList* lst, Cell c)
{
	DListNode* newTail;
	newTail = createNewDListNode(c, NULL, NULL);
	insertNodeToEndDList(lst, newTail);
}

void removeDListNode(DList* corList, DListNode* toRemove)
{
	DListNode* temp;
	if (corList->head == corList->tail) // remove the only one node in lst
	{
		free(corList->head);
		corList->head = corList->tail = NULL;
	}
	else if (toRemove->prev == NULL) // remove first node
	{
		corList->head = corList->head->next;
		free(corList->head->prev);
		corList->head->prev = NULL;
	}
	else if (toRemove == corList->tail) // remove last node
	{
		corList->tail = toRemove->prev;
		free(toRemove);
		corList->tail->next = NULL;
	}
	else // remove middle node
	{
		temp = toRemove->prev;
		temp->next = toRemove->next;
		temp = toRemove->next;
		temp->prev = toRemove->prev;
		free(toRemove);
	}
}

void makeEmptyDList(DList* dlst)
{
	dlst->head = dlst->tail = NULL;
}

bool isEmptyDList(DList lst)
{
	return (lst.head == NULL);
}
