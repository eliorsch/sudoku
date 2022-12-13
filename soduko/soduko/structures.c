#include "structures.h"
#include "memory.h"
#include <stdio.h>

void playerListPush(playerListHead* head, playerListItem* item)
{
	playerListItem* last = head->tail;
	last->next = item;
	item->next = NULL;
	head->tail = item;
}

void playerListRemove(playerListHead* head, playerListItem* item)
{
	if (head->head == NULL) return;
	
	playerListItem* prev = item->prev;
	playerListItem* next = item->next;
	prev->next = next;
	next->prev = prev;

	m_free_one(item);
}



