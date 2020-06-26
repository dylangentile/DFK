#include <kernel/alloc.h>

void __cxa_pure_virtual() {while(1);}


void* kalloc(size_t bytes)
{
	return nullptr;
}

void kfree(void*)
{
	return;	
}

void *operator new(size_t size)
{
	return kalloc(size);
}

void *operator new[](size_t size)
{
	return kalloc(size);
}

void operator delete(void* ptr)
{
	kfree(ptr);
}

void operator delete[](void* ptr)
{
	kfree(ptr);
}