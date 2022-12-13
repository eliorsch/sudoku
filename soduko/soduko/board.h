#pragma once
#include "structures.h"
#include "memory.h"
#include "Array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void __initGame__(int* numOfPlayers, playerListHead** listHead, player*** sortedPlayersArray, playerTreeNode** playersRoot);

player* createPlayer();

playerListHead* createNewPlayerList(int length);

player** createArrayFromPlayerList(playerListHead* listHead, int length);

void sortPlayersArray(player** arr, int size);

void mergePlayersArray(player** arr1, int size1, player** arr2, int size2, player** arr3);

int filledSquares(short board[][9]);

//-----TODO---

void createRandomBoard(short board[][9]);


playerTreeNode* createPlayersTree(player** arr, int size);



