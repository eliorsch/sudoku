#pragma once
#define OUT_OF_MEMORY 137
#define INTERNAL_ERROR 500


void* m_malloc(int blocksize);
void m_free();
void m_free_one(void* ptr);
void m_free_and_exit(int code);



