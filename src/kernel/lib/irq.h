#ifndef __IRQ_H__
#define __IRQ_H__
#include <stddef.h>
#include <stdint.h>
#include "kernel/lib/idt.h"
#include "kernel/lib/isr.h"

void irq_install(void);
void irq_install_handler(int, void (*handler)(struct regs *r));
void irq_uninstall_handler(int);

#endif
