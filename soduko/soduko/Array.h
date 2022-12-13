#pragma once
#define NOT_FINISH 1
#define  FINISH_SUCCESS 0
#define FINISH_FAILURE -1


typedef struct _Array
{
	short* arr;
	unsigned short size;
} Array;

Array*** PossibleDigits(short sudokuBoard[][9]);

int isPossibleDigit(short sudokuBoard[][9], int x, int y, int dig);

int isOnHorizontal(short sudokuBoard[][9], int x, int y, int dig);

int isOnVertical(short sudokuBoard[][9], int x, int y, int dig);

int isInSquare(short sudokuBoard[][9], int x, int y, int dig);

int OneStage(short board[][9], Array*** possibilities, int* x, int* y);

void updatePossibilities(Array*** possibilities, int x, int y, int dig);

void shrinkArray(Array* obj);

int isBoardLegal(short board[][9]);

int isBoardFull(short board[][9]);

int FillBoard(short board[][9], Array*** possibilities);

//-----TODO---





