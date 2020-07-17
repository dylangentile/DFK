#pragma once
#include <kernel/module.h>

/*
The TTY Module operates upon the stdin, stdout, and stderr streams.
First the TTY Module talks to the terminal, which drives the actual printing
of characters and the recieving of keyboard input.



*/


class TTY_Module : public Module
{
public:
	TTY_Module();
	~TTY_Module();
	

private:
	friend class Terminal;

	//you must supply the strings length (len not size ie w/o null terminator)
	void write_stdin(const char* str, size_t str_len);

public:
	
	//reads buf_size - 1 chars + '\0' at the end.
	//returns how many chars it wrote (includeing null terminator)
	//read_stdin(nullptr, *) will return how many chars it has buffered
	
	size_t read_stdin(char* buf, size_t buf_size);	

	//you must supply the strings length (len not size ie w/o null terminator)
	void write_stdout(const char* str, size_t str_len);
	void write_stderr(const char* str, size_t str_len);



	

};