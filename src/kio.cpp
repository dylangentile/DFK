#include <kernel/kio.h>
#include <kernel/kernel.h>
#include <kernel/alloc.h>
#include <string.h>




int
write(int fd, const void* data, int bytes)
{
	return -1;
}

int 
open(const char* path)
{
	return -1;
}


GraphicsDevice* gd = nullptr;
GraphicsDevice::GD_Info g_info;
GraphicsDevice::RGB* screen_buf;
size_t screen_buf_size = 0;
size_t effective_size = 0;

uint16_t rows = 0, columns = 0;
size_t row_offset = 0;

void
setGd(GraphicsDevice* GD)
{
	gd = GD;
	gd->getInfo(&g_info);
	screen_buf_size = g_info.modeList->xResolution * g_info.modeList->yResolution * 3;
	screen_buf = (GraphicsDevice::RGB*)kalloc(screen_buf_size);
	if(screen_buf == nullptr) //kalm... panik!!!
		kernel_panic();


	gd->setMode(0);

	memset(screen_buf, 0xFF, screen_buf_size);

	rows = g_info.modeList->yResolution / 16;
	columns = g_info.modeList->yResolution / 8;

	effective_size = (rows * 16) * (columns * 8) * 3;

	row_offset = g_info.modeList->xResolution * 16;





}



void
setPixel(uint32_t x, uint32_t y, GraphicsDevice::RGB color)
{
	GraphicsDevice::RGB* loc = screen_buf + (columns * 8 * y) + x;
	loc->r = color.r;
	loc->g = color.g;
	loc->b = color.b;
}

#include <misc/IBM_VGA_8x16.h>

void
klog(const char* msg)
{
	uint8_t* fontbuf = IBM_VGA_8x16;
	memmove(screen_buf, screen_buf + row_offset, effective_size - row_offset); //scroll
	

}