#include "players_list.h"

void insertDataToEndActivePlayersList(ActivePlayersList* lst, char name[], short board[][SIZE], Array*** possibilities)
{
	PlayerNode* res = createNewActivePlayersListNode(name, board, possibilities, NULL, NULL);
	insertNodeToEndActivePlayersList(lst, res);
}

PlayerNode* createNewActivePlayersListNode(char name[], short board[][SIZE], Array*** possibilities, PlayerNode* prev, PlayerNode* next)
{
	PlayerNode* pl = (PlayerNode*)malloc(sizeof(PlayerNode));
	checkAllocation(pl);

	pl->player.name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
	checkAllocation(pl->player.name);

	strcpy(pl->player.name, name);
	copyBoard(pl->player.sudukoBoard, board);

	pl->player.possibilities = possibilities;
	pl->next = next;
	pl->prev = prev;

	return pl;
}

void insertNodeToEndActivePlayersList(ActivePlayersList* lst, PlayerNode* newTail)
{
	if (isEmptyActivePlayersList(*lst))
	{
		lst->head = lst->tail = newTail;
	}
	else
	{
		newTail->prev = lst->tail;
		lst->tail->next = newTail;
		lst->tail = newTail;
	}
}

void removePlayerNodeFromActivePlayersList(ActivePlayersList* corList, PlayerNode* toRemove)
{
	PlayerNode* temp;

	if (corList->head == corList->tail) // remove the only one node in lst
	{
		freePossibilityBoard(toRemove->player.possibilities);
		corList->head = corList->tail = NULL;
	}
	else if (toRemove->prev == NULL) // remove first node
	{
		corList->head = corList->head->next;
		freePossibilityBoard(toRemove->player.possibilities);
		corList->head->prev = NULL;
	}
	else if (toRemove == corList->tail) // remove last node
	{
		corList->tail = toRemove->prev;
		freePossibilityBoard(toRemove->player.possibilities);
		corList->tail->next = NULL;
	}
	else // remove middle node
	{
		temp = toRemove->prev;
		temp->next = toRemove->next;
		temp = toRemove->next;
		temp->prev = toRemove->prev;
		freePossibilityBoard(toRemove->player.possibilities);
	}
}

void makeEmptyActivePlayersList(ActivePlayersList* lst)
{
	lst->head = lst->tail = NULL;
}

bool isEmptyActivePlayersList(ActivePlayersList lst)
{
	return (lst.head == NULL);
}

void insertNodeToEndWinList(WinnersPlayersList* lst, PlayerNode* newTail)
{
	newTail->next = newTail->prev = NULL; // reset next and prev playerNode
	
	if (isEmptyWinList(*lst))
	{
		lst->head = lst->tail = newTail;
	}
	else
	{
		newTail->prev = lst->tail;
		lst->tail->next = newTail;
		lst->tail = newTail;
	}
}

bool isEmptyWinList(WinnersPlayersList lst)
{
	return (lst.head == NULL);
}

void makeEmptyWinList(WinnersPlayersList* lst)
{
	lst->head = lst->tail = NULL;
}
