#include <kernel/kernint.h>

extern "C" void __cxa_pure_virtual();


extern "C"
{
	void* kalloc(size_t bytes);
	void kfree(void*);

}


void *operator new(size_t size);
void *operator new[](size_t size);
void operator delete(void* ptr);
void operator delete[](void* ptr);
