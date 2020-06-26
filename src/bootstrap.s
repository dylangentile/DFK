;; This is the 32 bit bootstrap into the 64-bit kernel
bits 32
section .text
global bootstrap
extern _start

multiboot_header:
        ;multiboot spec
        align 4
        dd 0x1BADB002            ;magic
        dd 0x00                  ;flags
        dd - (0x1BADB002 + 0x00) ;checksum. m+f+c should be zero



bootstrap:
	call _start