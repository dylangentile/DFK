#include "kernel/kio.h"
#include "cstdlib/string.h"

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

void
klog(const char* msg)
{
	char* vidptr = (char*)0xb8000; // 80 x 25 x 2  1st byte is char, 2nd is "attribute"
	int vidloc = 0;

	//clear screen;
	while(vidloc < 80 * 25 * 2) 
	{
		vidptr[vidloc] = ' ';
		vidptr[vidloc+1] = 0x07; 		
		vidloc += 2;
	}
	vidloc = 0;

	int msglen = strlen(msg);

	if(msglen > 80 * 25) msglen = 80 * 25;

	for(int i = 0; i < strlen(msg) + 1; ++i)
	{
		char printme = msg[i];
		if(printme == '\n')
		{
			vidloc = vidloc / 160;
			vidloc = (vidloc + 1) * 160;
		
			if(vidloc > 160 * 25) return;
		}
		else
		{
			vidptr[vidloc] = printme;
			vidptr[vidloc + 1] = 0x07;
			vidloc += 2;
		}
		
	}
}