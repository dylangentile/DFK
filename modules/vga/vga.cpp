#include <device/graphics_device.h>
#include <kernel/kernel.h>
#include <string.h>
/*
	This driver assumes that the kernel uses Pure64 and 
	that it is statically linked into the kernel and called into by the kernel
*/


class VGA_Device : public GraphicsDevice
{
public:
	//this is not a conforming driver
	//the constructor must be empty
	// I'm allowed to to this since the kernel will call into this directly
	// but eventually there should exist enough architecture to deprecate this
	VGA_Device(const Pure64Data* p64)
	{
		videoMemory = (uint8_t*)(*p64->VIDEO_BASE);
		x_res = *p64->VIDEO_X;
		y_res = *p64->VIDEO_Y;
		videoDepth = *p64->VIDEO_DEPTH;
	}

	~VGA_Device(){}

	virtual bool init()
	{
		mInfo.modeList = (GD_Info::modeListUnion*)&mode;

		mInfo.modeCount = 1;
		mInfo.modeList->yResolution = x_res;
		mInfo.modeList->yResolution = y_res;
		mInfo.modeList->refreshRate = 0;
		mInfo.modeList->colorBits = 8;
		mInfo.modeList->colorDepth = videoDepth;

		videoMemorySize = x_res * y_res * videoDepth;

		return true;

	}

	virtual void getInfo(GD_Info* info)
	{
		memcpy(info, &mInfo, sizeof(GD_Info));
	}

	virtual void setMode(uint16_t)
	{
		//does nothing. There's only one mode
	}

	virtual void putPixel(const uint16_t x, const uint16_t y, const RGB color)
	{
		uint8_t* ptr = (uint8_t*)((uintptr_t)videoMemory + (uintptr_t)((y * y_res) + x));
		uint8_t* colorPtr = (uint8_t*)&color;
		for(int i = 0; i < 3; i++)
		{
			*ptr = *colorPtr;
			ptr++;
			colorPtr++;
		}
	}

	virtual void putPixelBuffer(const RGB* buf, const size_t bufSize)
	{
		if(bufSize > videoMemorySize)
			memcpy(videoMemory, buf, y_res * x_res * videoDepth);
		else
			memcpy(videoMemory, buf, bufSize);
	}



private:
	uint8_t* videoMemory;
	uint16_t x_res;
	uint16_t y_res;
	uint8_t videoDepth;

	size_t videoMemorySize;

	GD_Info mInfo;
	uint64_t mode;



};