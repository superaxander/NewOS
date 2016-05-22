#include <stdbool.h> /* C doesn't have booleans by default. */
#include <stddef.h>
#include <stdint.h>
#include "kernel/lib/fallback_vga.h"
#include "kernel/lib/idt.h"
#include "kernel/lib/isr.h"
#include "kernel/lib/irq.h"

#if i386 != 1
#error "Non-i386 compilation is not yet supported"
#endif


void kernel_entry()
{
	__asm__ __volatile__ ("xchg %bx, %bx");
	/* Initialize terminal interface */
	terminal_initialize();
}

void kernel_main()
{
	terminal_writestring("GDT successfully loaded\nLoading IDT");
	terminal_translate(-11, 0);
	idt_install();
	terminal_writestring("IDT successfully loaded\nLoading ISRs");
	terminal_translate(-12, 0);
	isr_install();
	terminal_writestring("ISRs successfully loaded\nLoading IRQs");
	terminal_translate(-12, 0);
	irq_install();
	restore_interrupts();
	terminal_writestring("IRQs successfully loaded\n");
}
