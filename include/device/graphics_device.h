#pragma once
#include <kernel/device.h>

class GraphicsDevice : public Device
{
public:
	GraphicsDevice();
	~GraphicsDevice();

	struct GD_Info
	{
		uint16_t modeCount;
		union modeListUnion {
			struct {
				uint16_t xResolution;
				uint16_t yResolution;
				uint16_t refreshRate;
				uint8_t colorBits;
				uint8_t colorDepth;
			};
			uint64_t val;
		}* modeList;
		
	};

	virtual bool init() = 0;
	 //graphics driver should populate this
	virtual void getInfo(GD_Info* info) = 0;

	virtual void setMode(uint16_t modeNum) = 0; //based upon modeList location 

	//the sizeof color is the current mode's color bits * the color depth, rounded to nearest byte
	virtual void putPixel(const uint16_t x, const uint16_t y, void* color) = 0;

	//for double buffering. The buffer should be the size of the videoMemory, but if it isn't,
	// just copy as much as you can.
	virtual void putPixelBuffer(const void* buf, const size_t bufSize) = 0;
};