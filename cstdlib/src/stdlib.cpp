#include "stdlib.h"
#include "string.h"
#include <kernel/alloc.h>

void* 
malloc(size_t size)
{
	return kalloc(size);
}

void* 
calloc(size_t n, size_t size)
{
	void* data = kalloc(n * size);
	if(data == nullptr) return nullptr;

	memset(data, 0, n * size);
	return data;
}

void 
free(void* ptr)
{
	kfree(ptr);
}
