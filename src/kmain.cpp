#include "kernel/kernel.h"


extern "C"
{
	void kmain(void)
	{
		Kernel kern;
		kern.init();



		const char *str = "my first kernel";
		char *vidptr = (char*)0xb8000; 	//video mem begins here.
		unsigned int i = 0;
		unsigned int j = 0;

		/* this loops clears the screen
		* there are 25 lines each of 80 columns; each element takes 2 bytes */
		while(j < 80 * 25 * 2) {
			/* blank character */
			vidptr[j] = ' ';
			/* attribute-byte - light grey on black screen */
			vidptr[j+1] = 0x07; 		
			j = j + 2;
		}

		j = 0;

		/* this loop writes the string to video memory */
		while(str[j] != '\0') {
			/* the character's ascii */
			vidptr[i] = str[j];
			/* attribute-byte: give character black bg and light grey fg */
			vidptr[i+1] = 0x07;
			++j;
			i = i + 2;
		}

		char x = '\0';



		char* ps2 = (char*)0x63;
		x = *ps2;
		while(x == *ps2);

		vidptr[0] = 'A';


		return;
	}

}

