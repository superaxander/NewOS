[BITS 32]
; Declare constants used for creating a multiboot header.
MBALIGN     equ  1<<0                   ; align loaded modules on page boundaries
MEMINFO     equ  1<<1                   ; provide memory map
FLAGS       equ  MBALIGN | MEMINFO      ; this is the Multiboot 'flag' field
MAGIC       equ  0x1BADB002             ; 'magic number' lets bootloader find the header
CHECKSUM    equ -(MAGIC + FLAGS)        ; checksum of above, to prove we are multiboot
 
section .multiboot
align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM
 
section .bootstrap_stack, nobits
align 4
stack_bottom:
resb 16384
stack_top:
 
section .text
global _start
_start:
	xchg bx, bx ; breakpoint bochs
	mov esp, stack_top
 
	cli
	
	jmp go_long_mode
	cli
hang:
	hlt
	jmp hang

%include "long_mode.s"

[BITS 64]
entry_64_bit:
	xchg bx, bx
	cli
	;Do setup things(also clear screen)
	xchg bx, bx
	mov ax, GDT64.datad
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	xchg bx, bx
	mov edi, 0xB8000 ;frame buffer
	mov rax, 0x1F201F201F201F20
	mov ecx, 500
	rep stosq

	;C set up
	extern kernel_entry
	call kernel_entry
	
	;Kernel functions here!
	extern kernel_main
 	call kernel_main
	
	cli
	jmp hang


