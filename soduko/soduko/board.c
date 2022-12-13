#include "board.h"


void __initGame__(int* numOfPlayers, playerListHead** listHead, player*** sortedPlayersArray, playerTreeNode** playersRoot)
{
	//get number of players
	printf("Hello, welcome to soduko game :-)\n");
	printf("Please enter the number of players: ");
	while (scanf(" %d", numOfPlayers) != 1) printf("invalied number. number must be a whole positive number.\nplease re-enter: ");
	
	//create linked-list of players
	*listHead = createNewPlayerList(*numOfPlayers);
	
	//create sorted array of players
	*sortedPlayersArray = createArrayFromPlayerList(*listHead, *numOfPlayers);
	sortPlayersArray(*sortedPlayersArray, *numOfPlayers);

	//create players tree
	*playersRoot = createPlayersTree(*sortedPlayersArray, *numOfPlayers);


}

playerListHead* createNewPlayerList(int length)
{
	playerListHead* head = m_malloc(sizeof(playerListHead));

	head->head = NULL;
	head->tail = NULL;

	if (length == 0) return head;
	
	playerListItem** prev = &head->head;

	for (int i = 0; i < length; i++)
	{
		playerListItem* ptr = m_malloc(sizeof(playerListItem));
		
		ptr->item = createPlayer;

		*prev = ptr;
		prev = &ptr->next;

		head->tail = ptr;
	}
	*prev = NULL;

	return head;
}

player* createPlayer()
{
	player* item = m_malloc(sizeof(player));

	printf("please enter player's name: ");
	scanf("%s", item->name);

	createRandomBoard(item->board);
	item->Possibilities = PossibleDigits(item->board);

	return item;
}

player** createArrayFromPlayerList(playerListHead* listHead, int length)
{
	player** arr = m_malloc(sizeof(player*) * length);
	playerListItem* listItem = listHead->head;
	for (int i = 0; i < length; i++)
	{
		arr[i] = listItem;
		listItem = listItem->next;
	}
	return arr;
}

void sortPlayersArray(player** arr, int size)
{
	if (size <= 1) return;
	else
	{
		sortPlayersArray(arr, (size / 2));
		sortPlayersArray(arr + (size / 2), size - (size / 2));

		player** newArr = malloc(sizeof(player*) * size);
		if (newArr == NULL) m_free_and_exit(OUT_OF_MEMORY);

		mergePlayersArray(arr, (size / 2), arr + (size / 2), size - (size / 2), newArr);
		for (int i = 0; i < size; i++)
		{
			arr[i] = newArr[i];
		}
		free(newArr);
	}
}

void mergePlayersArray(player** arr1, int size1, player** arr2, int size2, player** arr3)
{
	int size3 = size1 + size2;
	int i1 = 0, i2 = 0, i3 = 0;

	while (i1 < size1 && i2 < size2)
	{
		int sum1 = filledSquares(arr1[i1]->board);
		int sum2 = filledSquares(arr2[i2]->board);
		
		if (sum1 == sum2)
		{
			int res = strcmp(arr1[i1]->name, arr2[i2]->name);
			if (res < 0) sum1 = -1;
		}

		if (sum1 < sum2)
		{
			arr3[i3] = arr1[i1];
			i3++;
			i1++;
		}
		else
		{
			arr3[i3] = arr2[i2];
			i3++;
			i2++;
		}


	}

	while (i1 < size1)
	{
		arr3[i3] = arr1[i1];
		i1++;
		i3++;
	}

	while (i2 < size2)
	{
		arr3[i3] = arr2[i2];
		i2++;
		i3++;
	}

}

int filledSquares(short board[][9])
{
	int sum = 0;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (board[i][j] > 0) sum++;
		}
	}
	return sum;
}
// im here----------
playerTreeNode* createPlayersTree(player** arr, int size)
{
	if (size <= 0) return NULL;

	playerTreeNode* node = m_malloc(sizeof(playerTreeNode));
}

