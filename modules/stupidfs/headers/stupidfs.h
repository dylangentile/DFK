#include <module/fs_module.h>
#include <string.h>

class StupidFS : public FileSystem
{
public:
	StupidFS();
	~StupidFS();

	class StupidFD : public FileDescriptor
	{
	public:
		StupidFD(StupidFS* p, size_t size, const char* path);
		~StupidFD();

		virtual const char* getPath() override;
		virtual size_t getSize() override;
		virtual void loadFile(void* location/*, void(*callback)(void)*/) override;
		virtual bool write(const void* bytes, size_t size) override;
	private:
		const size_t mSize;
		void* mData;
		char* mPath;

		StupidFS* parent;


	};

	virtual void format(LogicalDataDevice* dataDevice) override;
	virtual bool mount(LogicalDataDevice* dataDevice) override;
	virtual bool open(const char* path, FileDescriptor** fd) override;
	virtual bool close(FileDescriptor** fd) override;
private:
	friend class StupidFD;

	bool overwrite(void* address, const void* bytes, size_t size);

};

