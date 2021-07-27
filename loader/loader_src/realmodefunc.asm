%include "realmodefunc.inc"
global _start
[section .text]
[bits 16]
_start:
_16_mode:
    mov bp, 0x20
    mov ds, bp
    mov es, bp
    mov ss, bp
    mov ebp, cr0
    and ebp, 0xfffffffe
    mov cr0, ebp
    jmp 0:real_entry
real_entry:
    mov bp, cs
    mov ds, bp
    mov es, bp
    mov ss, bp
    mov sp, 08000h
    mov bp, func_table
    add bp, ax
    call [bp]
    cli
    call disable_nmi
    mov ebp, cr0
    or ebp, 1
    mov cr0, ebp
    jmp dword 0x8 : _32bits_mode
[bits 32]
_32bits_mode:
    mov bp, 0x10
    mov ds, bp
    mov ss, bp
    mov esi, [PM32_EIP_OFF]
    mov esp, [PM32_ESP_OFF]
    jmp esi

[bits 16]

_get_e820map:
    push ds
    push es
    push ss
    mov esi, 0
    mov dword[E820MAP_NR], esi
    mov dword[E820MAP_ADR_ADR], E820MAP_ADR

    xor ebx, ebx
    mov edi, E820MAP_ADR
loop:
	mov eax,0e820h
	mov ecx,20
	mov edx,0534d4150h
	int 15h
	jc .1

	add edi,20
	cmp edi,E820MAP_ADR+0x1000
	jg .1

	inc esi

	cmp ebx,0
	jne loop

	jmp .2
.1:
	mov esi,0

.2:
	mov dword[E820MAP_NR],esi
	pop ss
	pop es
	pop ds
	ret


[BITS 16]
DispStr:
	mov bp,ax
	mov cx,23
	mov ax,01301h
	mov bx,000ch
	mov dh,10
	mov dl,25
	mov bl,15
	int 10h
	ret

disable_nmi:
	push ax
	in al, 0x70     ; port 0x70NMI_EN_PORT
	or al, 0x80	; disable all NMI source
	out 0x70,al	; NMI_EN_PORT
	pop ax
	ret

func_table:
    dw _get_e820map

msg: 
    db     "call _get_e820map"
    db 0