#include "headers/ramdisk.h"

#ifndef RAMDISK_SIZE
#define RAMDISK_SIZE 1048576
#endif

RamDisk::RamDisk() : mData(nullptr), mSize(RAMDISK_SIZE)
{

}

RamDisk::~RamDisk()
{
	kfree(mData);
}

bool
RamDisk::init()
{
	mData = kalloc(mSize);
	if(mData == nullptr) return false;
	return true;
}

size_t 
RamDisk::getSize()
{
	return mSize;
}

bool
RamDisk::read(void* data, uintptr_t address, size_t bytes)
{
	if(address + bytes > mSize) return false;

	uint8_t* dest = (uint8_t*)data;
	uint8_t* ptr = (uint8_t*)mData + address;

	for(; ptr < (uint8_t*)mData + address + bytes; dest++, ptr++)
	{
		*dest = *ptr;
	}

	return true;

}

bool
RamDisk::write(uintptr_t address, void* data, size_t bytes)
{
	if(address + bytes > mSize) return false;

	uint8_t* ptr = (uint8_t*)data;
	uint8_t* dest = (uint8_t*)mData + address;

	for(; ptr < (uint8_t*)mData + address + bytes; dest++, ptr++)
	{
		*dest = *ptr;
	}

	return true;
}


//if the module is statically linked to the kernel this macro is set
//we do this since GENERATE_DEVICE_DRIVER creates the same extern "C" symbols
// for every single kernel module. When they're loaded dynamically,
// this is not a problem, but a static-linker will get confused!
#ifndef STATIC_KERNEL_MODULE 
GENERATE_DEVICE_DRIVER(12, kDeviceType_LogicalDataDevice, RamDisk)
#endif


