#include <stdio.h>

void printLine()
{
	for (int i = 0; i < 13; i++)
	{
		printf(" -");
	}
	printf("\n");
}

void printRow(short arr[], int index)
{
	
	if (index < 0) printf("   ");
	else printf(" %d ", index);

	for (int i = 0; i < 9; i++)
	{
		if (i % 3 == 0) printf(": ");
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void printHeader()
{
	int arr[] = { 0,1,2,3,4,5,6,7,8,9 };
	printRow(arr, -1);
	printLine();
}

void printBoard(short board[][9])
{
	printf("\n");
	printHeader();
	for (int i = 0; i < 3; i++)
	{
		if (i % 3 == 0) printLine();
		printRow(board[i], i);
	}
}

