bits 64
section .text

global _start
extern bmain	       



_start:
	cli
  	mov 	rsp, stack_space	;set stack pointer			
  	call 	bmain
  	push 0x401000 
  	ret
  	hlt		 	;halt the CPU



section .bss
resb 8192		;8KB for stack
stack_space: