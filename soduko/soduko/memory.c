#include<stdlib.h>
#include <stdio.h>
#include <memory.h>


void** __AllocatedMemorey = (void*)0;
int __AllocatedMemoreySize = 0;

void* m_malloc(int blocksize)
{
	if (blocksize < 1) m_free_and_exit(1);
	void** temp_arr = realloc(__AllocatedMemorey, (__AllocatedMemoreySize + 1) * sizeof(void*));
	if (temp_arr == NULL) m_free_and_exit(137);
	else
	{
		__AllocatedMemorey = temp_arr;
		__AllocatedMemoreySize += 1;
	}
		

	void* temp = malloc(blocksize);
	if (temp == NULL) m_free_and_exit(137);
	else __AllocatedMemorey[__AllocatedMemoreySize - 1] = temp;

	return temp;
}

void m_free()
{
	
	printf("\n%d pointers", __AllocatedMemoreySize);
	if (__AllocatedMemorey == 0) return;
	else
	{
		for (int i = 0; i < __AllocatedMemoreySize; i++)
		{
			if (__AllocatedMemorey[i] != NULL)
			free(__AllocatedMemorey[i]);
		}
		free(__AllocatedMemorey);
		__AllocatedMemorey = NULL;
		__AllocatedMemoreySize = 0;
	}
	return;
}

void m_free_one(void* ptr)
{
	for (int i = 0; i < __AllocatedMemoreySize; i++)
	{
		if (__AllocatedMemorey[i] == ptr)
		{
			free(ptr);
			__AllocatedMemorey[i] = NULL;
			return;
		}
	}
}

void m_free_and_exit(int code)
{
	m_free();
	exit(code);
}
