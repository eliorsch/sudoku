#pragma once
#include "Array.h"

typedef short row[9];
typedef row board[9];

typedef struct {
	int x;
	int y;
} square;

typedef struct {
	char name[100];
	short board[9][9];
	Array* Possibilities;
} player;

typedef struct {
	player* item;
	playerListItem* next;
} playerListItem;

typedef struct {
	playerListItem* head;
	playerListItem* tail;
} playerListHead;

typedef struct {
	player* item;
	playerTreeNode* small;
	playerTreeNode* big;
} playerTreeNode;


void playerListPush(playerListHead* head, playerListItem* item);

void playerListRemove(playerListHead* head, playerListItem* item);

//TODO:

playerTreeNode* createPlayersTree(player** arr);


