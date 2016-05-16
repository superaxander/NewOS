#ifndef _ISR_H_
#define _ISR_H_

#include <stdint.h>
#include <stddef.h>
#include "kernel/lib/klibc.h"
#include "kernel/lib/idt.h"
#include "kernel/lib/fallback_vga.h"

void isr_install();

struct regs
{
    unsigned int gs, fs, es, ds;    
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
    unsigned int int_no, err_code;   
    unsigned int eip, cs, eflags, useresp, ss;   
};

#endif
