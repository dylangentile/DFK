#pragma once
#include <kernel/kernint.h>



//memory.s header
extern "C"
{
	typedef struct MemoryData
	{
		kuintmax_t totalMemory;
		

	} MemoryData;

	void getMemoryInfo();
}