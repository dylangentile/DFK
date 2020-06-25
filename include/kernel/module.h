#pragma once
#include "kernel/device.h"

class Module
{
public:
	Module() = delete;
	

};


class FileSystem : public Module
{
public:
	FileSystem() = delete;
	~FileSystem();


	class FileDescriptor
	{
	public:
		FileDescriptor() = delete;
		~FileDescriptor();

		/*
		be smart about this one and allocate the const char* in your constructor
		then free it in the destructor. NO MEMORY LEAKS (please?)
		*/
		virtual const char* getPath() = 0; //returns the path to the file
		

		virtual int getSize() = 0; //get the size of the file

		//loads the file into memory(blocking) The kernel guarentees that the 
		//appropriate amount of memory (according to getSize) will be availible.
		//This is very sensitive code! Don't write more bytes 
		// than what you reported or we'll get scribbling!
		virtual void loadFile(void* location/*, void(*callback)(void)*/) = 0;

		//write to the file descriptor
		virtual bool write(const void* bytes, int size); 

	};


public:

	/*
	The device must be formatted with the appropriate filesystem.
	*/
	virtual void format(DataDevice* dataDevice) = 0;

	/*
	the file system module is supplied a DataDevice by the the kernel.
	It must properly mount this data device and be able to utilize it.
	If it fails to mount the device it must have left it untouched,  and 
	must return false.
	*/
	virtual bool initialize(DataDevice* dataDevice) = 0;

	/*
	return true/false for success/failure to open file.
	modify the fd variable with the appropriate file descriptor 
	*/
	virtual bool open(const char* path, FileDescriptor** fd) = 0;

	/*
	close the file descriptor. Most likely you allocated it in open, and you're
	deleteing here.
	*/
	virtual bool close(FileDescriptor** fd);




};


