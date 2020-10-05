#include <kernel/kernel.h>
#include <kernel/kio.h>
#include <kernel/cpuio.h>
#define PORT 0x3f8   /* COM1 */

extern "C"
{
	int is_transmit_empty() 
	{
		return inb(PORT + 5) & 0x20;
	}

	void write_serial(char a) 
	{
		while (is_transmit_empty() == 0);

		outb(PORT,a);
	}

	void write_str(const char* msg)
	{
		for(const char* ptr = msg; *ptr != '\0'; ptr++)
		{
			write_serial(*ptr);
		}
	}

	void kmain(void)
	{
		write_str("Kernel booted!");
		Kernel kern;
		kern.init();
		
		
		while(1)
		{
			
		}


		return;
	}

}

