#!/bin/bash
cd /vagrant
function help {
	echo usage: $0 \[option\]
	echo Available options:
	echo help
	echo i386
}

function build_i386 {
	nasm -felf32 ./src/arch/i386/boot.s -o build/boot.o
	i686-elf-gcc -c ./src/kernel/kernel.c -o build/kernel.o -std=gnu99 -D i386=1 -ffreestanding -O2 -Wall -Wextra -Werror
}
function link_i386 {
	i686-elf-gcc -T ./linker.ld -o build/os.bin -ffreestanding -O2 -nostdlib ./build/boot.o ./build/kernel.o -lgcc
}
function build_common {
	echo common build not implemented
}
function create_image {
	cp ./build/os.bin ./isodir/boot/os.bin
	grub-mkrescue -o os.iso isodir
}
if [ -z "$1" ]; then
	help
fi
if [ "$1" = "help" ]; then
	help
elif [ "$1" = "i386" ]; then
	build_i386
	build_common
	link_i386
	create_image
else
	help
fi

