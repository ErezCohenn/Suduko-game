#pragma once

// constants
#define MAX_LEN_NAME 101
#define FINISH_SUCCESS 0
#define NOT_FINISH 1
#define FINISH_FAILURE 2
#define FILLED 1
#define FAIL -1
#define SIZE 9
#define INVALID 0 
#define VALID 1
#define NOT_FOUND -1

// structs
typedef struct _Cell {
	int x;
	int y;
}Cell;

typedef struct dlistnode
{
	Cell c;
	struct dlistnode* next;
	struct dlistnode* prev;

}DListNode;

typedef struct dlist
{
	DListNode* head;
	DListNode* tail;
}DList;

typedef struct _Array
{
	short* arr;
	unsigned short size;
}Array;

typedef struct _Player
{
	char* name;
	short sudukoBoard[SIZE][SIZE];
	Array*** possibilities;
}Player;

typedef struct _PlayerNode
{
	Player player;
	struct _PlayerNode* next;
	struct _PlayerNode* prev;
}PlayerNode;

typedef struct _ActivePlayersList
{
	PlayerNode* head;
	PlayerNode* tail;
}ActivePlayersList;

typedef struct _WinnersPlayersList
{
	PlayerNode* head;
	PlayerNode* tail;
}WinnersPlayersList;

typedef struct treeNode
{
	PlayerNode** data;
	struct treeNode* left;
	struct treeNode* right;
}TreeNode;

typedef struct tree
{
	TreeNode* root;
}Tree;