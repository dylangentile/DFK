SECTIONS
{
	. = 0x100000;
	.main :
	{
		main.o (.text)
	}
	
	.text : {
		*(EXCLUDE_FILE(main.o) .text)
	}
	.data : {
		*(.data)
	}
	.rodata : {
		*(.rodata)
	}
	.bss : {
		*(.bss)
	}

	_end = .;

	/DISCARD/ :
	{
		*(.comment)
	}
}