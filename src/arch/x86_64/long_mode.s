go_long_mode:
	call check_cpuid
	cmp eax, 0
	je hang ; Show message to user before this?
	call check_extended_cpuid
	call check_long_mode
	call setup_paging
	; Ready to switch to 32-bit long-mode
	mov ecx, 0xC0000080
	rdmsr
	or eax, 1 << 8
	wrmsr
	; We are in 32-bit long-mode (compatibility mode)
	mov eax, cr0
	or eax, 1 << 31
	mov cr0, eax
	; Paging (with PAE) enabled
	lgdt [GDT64.pointer]
	jmp GDT64.coded:entry_64_bit
	

setup_paging: ;Not quite sure if I understand this part
	mov edi, 0x1000 ; Should I check if 0x1000 is free to be used first? (grub memory map?)
	mov cr3, edi
	xor eax, eax
	mov ecx, 4096
	rep stosd
	mov edi, cr3
	; Tables cleared
	mov DWORD [edi], 0x2003
	add edi, 0x1000
	mov DWORD [edi], 0x3003
	add edi, 0x1000
	mov DWORD [edi], 0x4003
	add edi, 0x1000
	; Pointers created?
	mov ebx, 0x00000003
	mov ecx, 512
.setentry: ; this repeats 512 times?
	mov DWORD [edi], ebx
	add ebx, 0x1000
	add edi, 8
	loop .setentry
	; first two megabytes of memory identity mapped
	mov eax, cr4
	or  eax, 1 << 5
	mov cr4, eax
	; PAE bit set
	ret
	
check_extended_cpuid:
	mov eax, 0x80000000
	cpuid
	cmp eax, 0x80000001
	jb hang ; show message to user before this?
	ret

check_long_mode:
	mov eax, 0x80000001
	cpuid
	test edx, 1 << 29
	jz hang ; show message to user before this?
	ret

check_cpuid:	; returns 1 if available or 0 if not
	pushfd
	pop eax

	mov ecx, eax

	xor eax, 1 << 21

	push eax
	popfd
	
	push ecx
	popfd
	
	xor eax, ecx
	jz .nocpuid
	mov eax, 1
	ret

.nocpuid:
	mov eax, 0
	ret

;GDT64:
;	.nulld: equ $ - GDT64	     ; The null descriptor
;	dw 0                         ; Limit (low).
;	dw 0                         ; Base (low).
;	db 0                         ; Base (middle)
;	db 0                         ; Access.
;	db 0                         ; Granularity.
;	db 0                         ; Base (high).
;	.coded: equ $ - GDT64        ; The code descriptor.
;	dw 0xFFFF                    ; Limit (low).
;	dw 0                         ; Base (low).
;	db 0                         ; Base (middle)
;	db 10011010b                 ; Access (exec/read).
;	db 10010000b                 ; Granularity.
;	db 0                         ; Base (high).
;	.datad: equ $ - GDT64        ; The data descriptor.
;	dw 0xFFFF                    ; Limit (low).
;	dw 0                         ; Base (low).
;	db 0                         ; Base (middle)
;	db 10010010b                 ; Access (read/write).
;	db 10010000b                 ; Granularity.
;	db 0                         ; Base (high).
;	.pointer:                    ; The GDT-pointer.
;	dw $ - GDT64 - 1             ; Limit.
;	dq GDT64                     ; Base.
;
GDT64:                           ; Global Descriptor Table (64-bit).
    .nulld: equ $ - GDT64         ; The null descriptor.
    dw 0                         ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 0                         ; Access.
    db 0                         ; Granularity.
    db 0                         ; Base (high).
    .coded: equ $ - GDT64         ; The code descriptor.
    dw 0                         ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 10011010b                 ; Access (exec/read).
    db 00100000b                 ; Granularity.
    db 0                         ; Base (high).
    .datad: equ $ - GDT64         ; The data descriptor.
    dw 0                         ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 10010010b                 ; Access (read/write).
    db 00000000b                 ; Granularity.
    db 0                         ; Base (high).
    .pointer:                    ; The GDT-pointer.
    dw $ - GDT64 - 1             ; Limit.
    dq GDT64                     ; Base.
