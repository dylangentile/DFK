#include <kernel/module.h>
#include <cstdlib/string.h>

class StupidFS : public FileSystem
{
public:
	StupidFS();
	~StupidFS();

	class StupidFD : public FileDescriptor
	{
	public:
		StupidFD(size_t size) : mSize(size) {}
		~StupidFD();

		virtual const char* getPath() override;
		virtual int getSize() override;
		virtual void loadFile(void* location/*, void(*callback)(void)*/) override;
		virtual bool write(const void* bytes, int size) override;
	private:
		const size_t mSize;

	};

	virtual void format(LogicalDataDevice* dataDevice) override;
	virtual bool mount(LogicalDataDevice* dataDevice) override;
	virtual bool open(const char* path, FileDescriptor** fd) override;
	virtual bool close(FileDescriptor** fd) override;

};

