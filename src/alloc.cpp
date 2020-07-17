#include <kernel/alloc.h>

void __cxa_pure_virtual() {while(1);}

typedef struct MemoryInfo
{
	size_t dataSize;
	MemoryInfo* next;
	bool is_free;
} MemoryInfo;

void* const basePointer =   (void*)0x800000; //  8 MiB
void* const maxPointer 	= 	(void*)0x8000000;//128 MiB
void* currentPointer 	= 	basePointer;




//I don't trust compilers. Doesn't hurt to leave this in.... ("SANITY CHECK")
static_assert(sizeof(MemoryInfo) % 8 == 0, "MemoryInfo struct misaligned!");

void* kalloc(size_t bytes)
{
	bytes += 8 - (bytes % 8); //padding

	

	if(sizeof(MemoryInfo) + (size_t)currentPointer + bytes > (size_t)maxPointer)
	{
		MemoryInfo* firstFree;
		MemoryInfo* memIt = (MemoryInfo*)basePointer;

		while(memIt != nullptr)
		{
			while(!memIt->is_free)
			{
				memIt = memIt->next;
				if(memIt == nullptr) //we never found a single free block!
					return nullptr;
			}

			if(memIt->dataSize >= bytes)
			{
				 //do we have enough room after what we are allocating to 
				// allocate more stuff
				if(memIt->dataSize - bytes > sizeof(MemoryInfo) + 8)
				{
					MemoryInfo* extra = (MemoryInfo*)((size_t)memIt + bytes + sizeof(MemoryInfo));
					extra->dataSize = memIt->dataSize - bytes - sizeof(MemoryInfo);
					memIt->dataSize = bytes;

					extra->is_free = true;
					extra->next = memIt->next;
					memIt->next = extra; 

				}

				memIt->is_free = false;
				return (void*)((size_t)memIt + sizeof(MemoryInfo));
			}
			//ELSE

			firstFree = memIt;
			memIt = memIt->next;
			if(memIt == nullptr) //we couldn't find any single/consecutive free blocks!
				return nullptr;

			size_t free_space = firstFree->dataSize;
			
			while(memIt->is_free)
			{
				free_space += memIt->dataSize + sizeof(MemoryInfo);
				memIt = memIt->next;
				if(memIt == nullptr)
					break;

				if(free_space >= bytes)
					break;
			}

			if(free_space >= bytes)
			{
				firstFree->next = memIt;
				firstFree->dataSize = free_space;

				if(firstFree->dataSize - bytes > sizeof(MemoryInfo) + 8)
				{
					MemoryInfo* extra = (MemoryInfo*)((size_t)firstFree + bytes + sizeof(MemoryInfo));
					extra->dataSize = firstFree->dataSize - bytes - sizeof(MemoryInfo);
					firstFree->dataSize = bytes;

					extra->is_free = true;
					extra->next = firstFree->next;
					firstFree->next = extra;
				}

				firstFree->is_free = false;
				return (void*)((size_t)firstFree + sizeof(MemoryInfo));
			}
		}

		return nullptr;		

	}
	else
	{
		MemoryInfo* memPtr = (MemoryInfo*)currentPointer;
		currentPointer = (void*)(sizeof(MemoryInfo) + (size_t)memPtr + bytes);
		memPtr->dataSize = bytes;
		memPtr->is_free = false;

		if(currentPointer >= maxPointer)
			memPtr->next = nullptr;
		else
			memPtr->next = (MemoryInfo*)currentPointer;

		return (void*)((size_t)memPtr + sizeof(MemoryInfo));
	}
}

void kfree(void* ptr)
{
	if(ptr == nullptr)
		return;

	MemoryInfo* memPtr = (MemoryInfo*)((size_t)ptr - sizeof(MemoryInfo));
	memPtr->is_free = true;
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