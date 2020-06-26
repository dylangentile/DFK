#pragma once
#include "kernel/device.h"

extern "C"
{

	typedef enum
	{
		kModuleType_NULL,
		kModuleType_FileSystem
	}ModuleType;


}










class Module
{
protected: 
	Module(ModuleType type);
public:
	~Module();

	const ModuleType mType;
};


class FileSystem : public Module
{
protected:	
	FileSystem();
public:
	~FileSystem();


	class FileDescriptor
	{
	public:
		FileDescriptor();
		~FileDescriptor();

		/*
		be smart about this one and allocate the const char* in your constructor
		then free it in the destructor. NO MEMORY LEAKS (please?)
		*/
		virtual const char* getPath() = 0; //returns the path to the file
		

		virtual size_t getSize() = 0; //get the size of the file

		//loads the file into memory(blocking) The kernel guarentees that the 
		//appropriate amount of memory (according to getSize) will be availible.
		//This is very sensitive code! Don't write more bytes 
		// than what you reported or we'll get scribbling!
		virtual void loadFile(void* location/*, void(*callback)(void)*/) = 0;

		//write to the file descriptor
		virtual bool write(const void* bytes, int size) = 0; 

	};


public:

	/*
	The device must be formatted with the appropriate filesystem.
	Note that this should be implemented as a pure function in the sense that
	it does not modify member variables of the class. IE format literally just
	formats the disk with the filesystem, and that is it. The disk is not mounted
	This function is only in this class to keep things organized, not to tie
	it to state.
	*/
	virtual void format(LogicalDataDevice* dataDevice) = 0;

	/*
	the file system module is supplied a DataDevice by the the kernel.
	It must properly mount this data device and be able to utilize it.
	If it fails to mount the device it must have left it untouched,  and 
	must return false.
	*/
	virtual bool mount(LogicalDataDevice* dataDevice) = 0;

	/*
	return true/false for success/failure to open file.
	modify the fd variable with the appropriate file descriptor 
	*/
	virtual bool open(const char* path, FileDescriptor** fd) = 0;

	/*
	close the file descriptor. Most likely you allocated it in open, and you're
	deleteing here.
	*/
	virtual bool close(FileDescriptor** fd) = 0;




};



