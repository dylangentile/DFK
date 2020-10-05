SECTIONS
{
	. = 0x401000;
	
	.text : {
		*(.text)
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