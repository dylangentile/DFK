#pragma once

#include <device/graphics_device.h>




/*
	This driver assumes that the kernel uses Pure64 and 
	that it(the driver) is statically linked into the kernel and called into by the kernel
*/


class VGA_Device : public GraphicsDevice
{
public:
	//this is not a conforming driver
	//the constructor must be empty
	// I'm allowed to to this since the kernel will call into this directly
	// but eventually there should exist enough architecture to deprecate this
	VGA_Device(const void* p64_);

	~VGA_Device();

	virtual bool init();

	virtual void getInfo(GD_Info* info);

	virtual void setMode(uint16_t);

	virtual void putPixel(const uint16_t x, const uint16_t y, const RGB color);

	virtual void putPixelBuffer(const RGB* buf, const size_t bufSize);



private:
	uint8_t* videoMemory;
	uint16_t x_res;
	uint16_t y_res;
	uint8_t videoDepth;

	size_t videoMemorySize;

	GD_Info mInfo;
	uint64_t mode;



};