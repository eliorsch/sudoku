#include "Array.h"
#include "memory.h"
#include "print.h"
#include <stdio.h>
#include <stdlib.h>


Array*** PossibleDigits(short sudokuBoard[][9])
{
	Array*** main = m_malloc(sizeof(Array**) * 9);

	for (int i = 0; i < 9; i++)
	{
		main[i] = m_malloc(sizeof(Array*) * 9);
		for (int j = 0; j < 9; j++)
		{
			if (sudokuBoard[i][j] < 0)
				main[i][j] = m_malloc(sizeof(Array));
			else
				main[i][j] = NULL;
		}
	}

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (main[i][j] == NULL) continue;

			int temp[] = { 1,2,3,4,5,6,7,8,9 };
			int count = 0;
			for (int dig = 0; dig < 9; dig++)
			{
				if (isPossibleDigit(sudokuBoard, i, j, temp[dig]))
				{
					count++;
				}
				else
				{
					temp[dig] = (-1);
				}
			}
			if (count < 1)
			{
				m_free_and_exit(500);
			}
			else
			{
				main[i][j]->arr = m_malloc(sizeof(short) * count);
				main[i][j]->size = count;
				for (int temp_i = 0, arr_i = 0; temp_i < 9; temp_i++)
				{
					if (temp[temp_i] > 0)
					{
						main[i][j]->arr[arr_i] = temp[temp_i];
						arr_i++;
					}
				}
		
			}
		}
	}

	return main;
}

int isPossibleDigit(short sudokuBoard[][9], int x, int y, int dig)
{
	return (!(isOnHorizontal(sudokuBoard, x, y, dig)
		|| isOnVertical(sudokuBoard, x, y, dig)
		|| isInSquare(sudokuBoard, x, y, dig)));
}

int isOnHorizontal(short sudokuBoard[][9], int x, int y, int dig)
{
	for (int k = 0; k < 9; k++)
	{
		if (k == y) continue;
		if (sudokuBoard[x][k] == dig) return 1;
	}
	return 0;
}

int isOnVertical(short sudokuBoard[][9], int x, int y, int dig)
{
	for (int k = 0; k < 9; k++)
	{
		if (k == x) continue;
		if (sudokuBoard[k][y] == dig) return 1;
	}
	return 0;
}

int isInSquare(short sudokuBoard[][9], int x, int y, int dig)
{
	int starts_x = x - (x % 3);
	int starts_y = y - (y % 3);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (i == x && j == y) continue;

			if (sudokuBoard[starts_x+i][starts_y+j] == dig) return 1;
		}
	}
	return 0;
}

int OneStage(short board[][9], Array*** possibilities, int* x, int* y)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (possibilities[i][j] != NULL)
			{
				if (possibilities[i][j]->size == 1)
				{
					board[i][j] = possibilities[i][j]->arr[0];
					m_free_one(possibilities[i][j]);
					possibilities[i][j] = NULL;
					updatePossibilities(possibilities, i, j, board[i][j]);
					i = j = 0;
				}
			}
		}
	}

	if (isBoardLegal(board))
	{
		if (isBoardFull(board)) return FINISH_SUCCESS;
		else
		{
			(*x) = 0;
			(*y) = 0;
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					if (possibilities[i][j]->size < possibilities[(*x)][(*y)]->size)
					{
						(*x) = i;
						(*y) = j;
					}
				}
			}
			return NOT_FINISH;
		}
		
	}
	else return FINISH_FAILURE;
	
}

void updatePossibilities(Array*** possibilities, int x, int y, int dig)
{
	for (int i = 0; i < 9; i++)
	{
		if (i == x) continue;
		if (possibilities[i][y] == NULL) continue;
		for (int k = 0; k < possibilities[i][y]->size; k++)
		{
			if (possibilities[i][y]->arr[k] == dig)
			{
				possibilities[i][y]->arr[k] = -1;
				break;
			}
		}
		shrinkArray(possibilities[i][y]);
	}

	for (int i = 0; i < 9; i++)
	{
		if (i == y) continue;
		if (possibilities[x][i] == NULL) continue;
		for (int k = 0; k < possibilities[x][i]->size; k++)
		{
			if (possibilities[x][i]->arr[k] == dig)
			{
				possibilities[x][i]->arr[k] = -1;
				break;
			}
		}
		shrinkArray(possibilities[x][i]);
	}

	int start_x = x - (x % 3);
	int start_y = y - (y % 3);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if ((start_x + i) == x && (start_y + j) == y) continue;
			if (possibilities[start_x+i][start_y+j] == NULL) continue;
			for (int k = 0; k < possibilities[start_x + i][start_y + j]->size; k++)
			{
				if (possibilities[start_x + i][start_y + j]->arr[k] == dig)
				{
					possibilities[start_x + i][start_y + j]->arr[k] = -1;
					break;
				}
			}
			shrinkArray(possibilities[start_x + i][start_y + j]);
		}
	}
}

void shrinkArray(Array* obj)
{
	for (int i = 0; i < obj->size; i++)
		if (obj->arr[i] == -1)
		{
			obj->arr[i] = obj->arr[(obj->size) - 1];
			obj->arr = realloc(obj->arr, (obj->size) - 1);
			if (obj->arr == NULL) m_free_and_exit(OUT_OF_MEMORY);
			else
			{
				obj->size -= 1;
				return;
			}
		}
}

int isBoardLegal(short board[][9])
{
	for (int x = 0; x < 9; x++)
		for (int y = 0; y < 9; y++)
		{
			if (board[x][y] < 0) continue;
			else if (!isPossibleDigit(board, x, y, board[x][y]))
				return 0;
		}
	return 1;
}

int isBoardFull(short board[][9])
{
	for (int x = 0; x < 9; x++)
		for (int y = 0; y < 9; y++)
			if (board[x][y] < 1) 
				return 0;
	return 1;
}

int FillBoard(short board[][9], Array*** possibilities)
{
	int x, y;
	int res = OneStage(board, possibilities, &x, &y);
	if (res == NOT_FINISH)
	{
		system("cls");
		printBoard(board);
		//change printboard as needed
		printf("please choose a number to enter at %d, %d:", x, y);
		scanf(" %d", &board[x][y]);
		updatePossibilities(possibilities, x, y, board[x][y]);
		return FillBoard(board, possibilities);
	}
	else return res;

}


