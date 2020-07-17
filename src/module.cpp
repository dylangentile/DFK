#include <kernel/module.h>


Module::Module(ModuleType type) : mType(type)
{

} 

Module::~Module()
{

}

#include <module/fs_module.h>

FileSystem::FileSystem() : Module(kModuleType_FileSystem)
{

}

FileSystem::~FileSystem()
{

}


FileSystem::FileDescriptor::FileDescriptor()
{

}

FileSystem::FileDescriptor::~FileDescriptor()
{
	
}