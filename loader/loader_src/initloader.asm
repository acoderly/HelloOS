%include "initloader.inc"
global _start
global realmode_call_entry
extern loader_entry
[section .text]
[bits 32]
_start:
_entry:
    cli
    lgdt [GDT_PTR]
    lidt [IDT_PTR]
    jmp dword 0x8:_32bits_mode

_32bits_mode:
    mov ax, 0x10
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    xor eax, eax
    xor ebx, ebx
    xor ecx, ecx
    xor edx, edx
    xor edi, edi
    xor esi, esi
    xor ebp, ebp
    xor esp, esp
    mov esp, 0x90000
    call loader_entry
    xor ebx, ebx
    jmp $
    jmp 0x2000000 ;Jump to kernel
    jmp $ ;Halt


realmode_call_entry:
    pushad
    push ds
    push es
    push fs
    push gs
    call save_eip_jmp
    pop gs
    pop fs
    pop es
    pop ds
    popad
    ret
save_eip_jmp:
    pop esi
    mov [PM32_EIP_OFF], esi
    mov [PM32_ESP_OFF], esp
    jmp dword far [realmode_selector]
realmode_selector:
    dd 0x1000
    dw 0x18
    jmp $


GDT_START:
knull_dsc: dq 0
kcode_dsc: dq 0x00cf9a000000ffff ;a-e
kdata_dsc: dq 0x00cf92000000ffff
k16cd_dsc: dq 0x00009a000000ffff ;a-e
k16da_dsc: dq 0x000092000000ffff
GDT_END:

GDT_PTR:
GDTLEN	dw GDT_END-GDT_START-1	;GDT界限
GDTBASE	dd GDT_START

IDT_PTR:
IDTLEN	dw 0x3ff
IDTBAS	dd 0