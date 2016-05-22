#!/bin/bash
cd /vagrant
function help {
	echo usage: $0 \[option\]
	echo Available options:
	echo help
	echo x86_64
}

function build_x86_64 {
	nasm -f elf64 -i./src/arch/x86_64/ ./src/arch/x86_64/boot.s -o build/boot.o
	nasm -f elf64 -i./src/arch/x86_64/ ./src/arch/x86_64/idt.s -o build/idt_asm.o
	nasm -f elf64 -i./src/arch/x86_64/ ./src/arch/x86_64/isr.s -o build/isr_asm.o
	nasm -f elf64 -i./src/arch/x86_64/ ./src/arch/x86_64/irq.s -o build/irq_asm.o
	x86_64-elf-gcc -I./src -c ./src/kernel/kernel.c -o build/kernel.o -std=gnu99 -D i386=1 -ffreestanding -O2 -Wall -Wextra -Werror
	x86_64-elf-gcc -I./src -c ./src/kernel/lib/klibc.c -o build/klibc.o -std=gnu99 -D i386=1 -ffreestanding -O2 -Wall -Wextra -Werror
	x86_64-elf-gcc -I./src -c ./src/kernel/lib/fallback_vga.c -o build/fallback_vga.o -std=gnu99 -D i386=1 -ffreestanding -O2 -Wextra -Werror
	x86_64-elf-gcc -I./src -c ./src/kernel/lib/idt.c -o build/idt_c.o -std=gnu99 -D i386=1 -ffreestanding -O2 -Wextra -Werror
	x86_64-elf-gcc -I./src -c ./src/kernel/lib/isr.c -o build/isr_c.o -std=gnu99 -D i386=1 -ffreestanding -O2 -Wextra -Werror
	x86_64-elf-gcc -I./src -c ./src/kernel/lib/irq.c -o build/irq_c.o -std=gnu99 -D i386=1 -ffreestanding -O2 -Wextra -Werror
}
function link_x86_64 {
	x86_64-elf-gcc -mno-red-zone -T ./linker.ld -o build/os.bin64 -ffreestanding -O2 -nostdlib ./build/boot.o ./build/kernel.o ./build/klibc.o ./build/fallback_vga.o ./build/idt_asm.o ./build/idt_c.o ./build/isr_asm.o ./build/isr_c.o ./build/irq_asm.o ./build/irq_c.o -lgcc
}
function build_common {
	echo common build not implemented
}
function create_image {
	x86_64-elf-objcopy build/os.bin64 -O elf32-i386 build/os.bin32	
	cp ./build/os.bin32 ./isodir/boot/os.bin
	grub-mkrescue -o os.iso isodir
}
if [ -z "$1" ]; then
	help
fi
if [ "$1" = "help" ]; then
	help
elif [ "$1" = "x86_64" ]; then
	build_x86_64
	build_common
	link_x86_64
	create_image
else
	help
fi

