#include <stdbool.h> /* C doesn't have booleans by default. */
#include <stddef.h>
#include <stdint.h>
#include "kernel/lib/fallback_vga.h"
#include "kernel/lib/gdt.h"

#if i386 != 1
#error "Non-i386 compilation is not yet supported"
#endif


void kernel_entry()
{
	gdt_install();
	/* Initialize terminal interface */
	terminal_initialize();
}

void kernel_main()
{
	/* Since there is no support for newlines in terminal_putchar
         * yet, '\n' will produce some VGA specific character instead.
         * This is normal.
         */
	terminal_writestring("Hello, kernel World!\n");
}
