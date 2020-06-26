#include "headers/stupidfs.h"
#include <stdlib.h>


StupidFS::StupidFD::StupidFD(StupidFS* p, size_t size, const char* path) : parent(p), mSize(size)
{
	mPath = (char*)calloc(1, strlen(path) + 1);
	strcpy(mPath, path);
}

StupidFS::StupidFD::~StupidFD()
{
	free(mPath);
}

const char*
StupidFS::StupidFD::getPath()
{
	return (const char*)mPath;
}

size_t
StupidFS::StupidFD::getSize()
{
	return mSize;
}

void
StupidFS::StupidFD::loadFile(void* location)
{
	memcpy(location, mData, mSize);
}

bool
StupidFS::StupidFD::write(const void* bytes, size_t size)
{

}

StupidFS::StupidFS()
{

}

StupidFS::~StupidFS()
{

}

void
StupidFS::format(LogicalDataDevice* dataDevice)
{

}

bool 
StupidFS::mount(LogicalDataDevice* dataDevice)
{

}

bool 
StupidFS::open(const char* path, FileDescriptor** fd)
{
	
}

bool
StupidFS::close(FileDescriptor** fd)
{

}

bool 
StupidFS::overwrite(void* address, const void* bytes, size_t size)
{

}









