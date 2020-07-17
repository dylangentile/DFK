#pragma once
#include <kernel/device.h>

extern "C"
{

	typedef enum
	{
		kModuleType_NULL,
		kModuleType_FileSystem,
		kModuleType_TTY
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





