#include <kernel/kernel.h>
#include <kernel/kio.h>

extern "C"
{
	void kmain(void)
	{
		Kernel kern;
		kern.init();


		return;
	}

}

