#include "kernel/lib/idt.h"
#include "kernel/lib/fallback_vga.h"
#include "kernel/lib/klibc.h"

struct idt_entry
{
    uint16_t base_lo;
    uint16_t sel;        
    uint8_t  always0;     
    uint8_t  flags;       
    uint16_t base_mid;
    uint32_t base_hi;
    uint32_t always0_2;
} __attribute__((packed));

struct idt_ptr
{
    uint16_t limit;
    uint64_t base;
} __attribute__((packed));

struct idt_entry   idt[256];
struct idt_ptr     idtp = {0, 1};

extern void idt_load();

void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags)
{
    idt[num].base_lo  = (base & 0xFFFF);
    idt[num].base_mid = (base >> 16) & 0xFFF;
    idt[num].base_hi  = (base >> 32) & 0xFFF;

    idt[num].sel      = sel;
    idt[num].always0  = 0;
    idt[num].always0_2= 0;
    idt[num].flags    = flags;
}

void idt_install()
{
    char buf[128];

    __asm__ __volatile__("xchg %bx, %bx");
    __asm__ __volatile__("xchg %bx, %bx");
    idtp.limit       = (sizeof (struct idt_entry) * 256) - 1;
    idtp.base        = (uintptr_t)&idt;
    
    inttostr((sizeof(struct idt_entry) * 256) - 1, 16, buf);
    terminal_writestring(buf);

    memset(&idt, 0, sizeof(struct idt_entry) * 256);
    __asm__ __volatile__("xchg %bx, %bx");
    idt_load();
}
