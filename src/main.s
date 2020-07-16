;;kernel.asm
bits 64
section .text

global _start
extern kmain	       


_start:
	cli
  	mov 	rsp, stack_space	;set stack pointer			
  	call 	kmain
  	hlt		 	;halt the CPU

section .bss
resb 8192		;8KB for stack
stack_space: