#ifndef _IDT_H_
#define _IDT_H_

#include <stddef.h>
#include <stdint.h>
#include "kernel/lib/klibc.h"

void idt_install();
void idt_set_gate(unsigned char, unsigned long, unsigned short, unsigned char);

#endif
