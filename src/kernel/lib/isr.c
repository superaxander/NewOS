#include "kernel/lib/isr.h"
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();
extern void isr31();

void isr_install()
{
  idt_set_gate(0,  (uintptr_t)isr0,  0x08, 0x8E);
  idt_set_gate(1,  (uintptr_t)isr1,  0x08, 0x8E);
  idt_set_gate(2,  (uintptr_t)isr2,  0x08, 0x8E);
  idt_set_gate(3,  (uintptr_t)isr3,  0x08, 0x8E);
  idt_set_gate(4,  (uintptr_t)isr4,  0x08, 0x8E);
  idt_set_gate(5,  (uintptr_t)isr5,  0x08, 0x8E);
  idt_set_gate(6,  (uintptr_t)isr6,  0x08, 0x8E);
  idt_set_gate(7,  (uintptr_t)isr7,  0x08, 0x8E);
  idt_set_gate(8,  (uintptr_t)isr8,  0x08, 0x8E);
  idt_set_gate(9,  (uintptr_t)isr9,  0x08, 0x8E);
  idt_set_gate(10, (uintptr_t)isr10, 0x08, 0x8E);
  idt_set_gate(11, (uintptr_t)isr11, 0x08, 0x8E);
  idt_set_gate(12, (uintptr_t)isr12, 0x08, 0x8E);
  idt_set_gate(13, (uintptr_t)isr13, 0x08, 0x8E);
  idt_set_gate(14, (uintptr_t)isr14, 0x08, 0x8E);
  idt_set_gate(15, (uintptr_t)isr15, 0x08, 0x8E);
  idt_set_gate(16, (uintptr_t)isr16, 0x08, 0x8E);
  idt_set_gate(17, (uintptr_t)isr17, 0x08, 0x8E);
  idt_set_gate(18, (uintptr_t)isr18, 0x08, 0x8E);
  idt_set_gate(19, (uintptr_t)isr19, 0x08, 0x8E);
  idt_set_gate(20, (uintptr_t)isr20, 0x08, 0x8E);
  idt_set_gate(21, (uintptr_t)isr21, 0x08, 0x8E);
  idt_set_gate(22, (uintptr_t)isr22, 0x08, 0x8E);
  idt_set_gate(23, (uintptr_t)isr23, 0x08, 0x8E);
  idt_set_gate(24, (uintptr_t)isr24, 0x08, 0x8E);
  idt_set_gate(25, (uintptr_t)isr25, 0x08, 0x8E);
  idt_set_gate(26, (uintptr_t)isr26, 0x08, 0x8E);
  idt_set_gate(27, (uintptr_t)isr27, 0x08, 0x8E);
  idt_set_gate(28, (uintptr_t)isr28, 0x08, 0x8E);
  idt_set_gate(29, (uintptr_t)isr29, 0x08, 0x8E);
  idt_set_gate(30, (uintptr_t)isr30, 0x08, 0x8E);
  idt_set_gate(31, (uintptr_t)isr31, 0x08, 0x8E);
}

char *exception_messages[32] =
{
  "Division By Zero",
  "Debug",
  "Non Maskable Interupt",
  "Breakpoint",
  "Into Detected Overflow",
  "Out of Bounds",
  "Invalid Opcode",
  "No Coprocessor",
  "Double Fault",
  "Coprocessor Segment Overrun",
  "Bad TSS",
  "Segement Not Present",
  "Stack Fault",
  "General Protection Fault",
  "Page Fault",
  "Unknown Interrupt",
  "Coprocessor Fault",
  "Alignment Check",
  "Machine Check",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
};

void fault_handler(struct regs *r)
{
  char err_code[128];
  inttostr(r->err_code, 16, err_code);
  if (r->int_no < 32)
  {
    terminal_writestring(exception_messages[r->int_no]);
    terminal_writestring(" Exception. System Halted!\n");
    switch(r->int_no)
    {
      default:
        terminal_writestring("No error code\n");
        break;
      case 8:
        terminal_writestring("Error code: ");
        terminal_writestring(err_code);
        break;
      case 10:
        terminal_writestring("Error code: ");
        terminal_writestring(err_code);
        break;
      case 11:
        terminal_writestring("Error code: ");
        terminal_writestring(err_code);
        break;
      case 12:
        terminal_writestring("Error code: ");
        terminal_writestring(err_code);
        break;
      case 13:
        terminal_writestring("Error code: ");
        terminal_writestring(err_code);
        break;
      case 14:
        terminal_writestring("Error code: ");
        terminal_writestring(err_code);
        break;
    }
    __asm__ __volatile__  ("cli");
    for (;;)
	    __asm__ __volatile__ ("hlt");
  }
}
