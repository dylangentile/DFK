#include <kernel/device.h>
#include <kernel/alloc.h>

class RamDisk : public LogicalDataDevice
{
public:
	RamDisk();
	~RamDisk();
	virtual bool init() override;
	virtual size_t getSize() override;

	//read n-bytes into data pointer from address, return true/false for success
	virtual bool read(void* data, uintptr_t address, size_t bytes) override;
	//write n-bytes into address from data pointer, return true/false for success
	virtual bool write(uintptr_t address, void* data, size_t bytes) override;

private:
	void* mData;
	const size_t mSize;
};