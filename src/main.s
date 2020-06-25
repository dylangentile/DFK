;;kernel.asm

;nasm directive - 32 bit
bits 32
section .text
        ;multiboot spec
        align 4
        dd 0x1BADB002            ;magic
        dd 0x00                  ;flags
        dd - (0x1BADB002 + 0x00) ;checksum. m+f+c should be zero

global _start
extern kmain	       

gdtr DW 0 ; For limit storage
     DD 0 ; For base storage

setGdt:
	mov   EAX, [esp + 4]
	mov   [gdtr + 2], EAX
	mov   AX, [ESP + 8]
	mov   [gdtr], AX
	lgdt  [gdtr]
	ret

_start:
  	cli 	; disable interrupts
  	mov 	esp, stack_space	;set stack pointer			
  	call 	setGdt
	lgdt 	[gdtr]    ; load GDT register with start address of Global Descriptor Table
	mov 	eax, cr0 
	or 		al, 1       ; set PE (Protection Enable) bit in CR0 (Control Register 0)
	mov 	cr0, eax
  	
  	call 	kmain
  	hlt		 	;halt the CPU

section .bss
resb 8192		;8KB for stack
stack_space: