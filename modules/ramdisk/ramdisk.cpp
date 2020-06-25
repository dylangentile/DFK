#include "kernel/module.h"
#include "kernel/alloc.h"

#ifndef RAMDISK_SIZE
#define RAMDISK_SIZE 1048576
#endif

class RamDisk : public DataDevice
{
public:
	RamDisk();
	~RamDisk();
	virtual bool init() override;

	void* mData;
};


RamDisk::RamDisk() : mData(nullptr)
{

}

bool
RamDisk::init()
{
	mData = rawalloc(RAMDISK_SIZE);
}


RamDisk::~RamDisk()
{
	rawfree(mData);
}



