; FynOS - Stage 2 Bootloader
; Loads kernel, enables A20, switches to 32-bit protected mode

%ifndef KERNEL_SECTORS
%define KERNEL_SECTORS 16
%endif

bits 16
org 0x7E00

mov [boot_drive], dl

mov ax, 0x0003
int 0x10

mov si, stage2_msg
call print_string

; Enable A20 via port 0x92
in al, 0x92
or al, 2
and al, 0xFE
out 0x92, al

mov si, loading_kernel_msg
call print_string

mov ax, 0
mov es, ax
mov bx, 0x1000
mov dh, 0
mov dl, [boot_drive]
mov ch, 0
mov cl, 3
mov al, KERNEL_SECTORS

mov ah, 0x02
int 0x13
jc disk_error

mov si, kernel_loaded_msg
call print_string

mov cx, 0xFFFF
delay_loop:
    nop
    loop delay_loop

mov si, pmode_msg
call print_string

cli
lgdt [gdt_descriptor]
mov eax, cr0
or eax, 1
mov cr0, eax

jmp CODE_SEG:init_pm

disk_error:
    mov si, disk_error_msg
    call print_string
    jmp $

print_string:
    lodsb
    or al, al
    jz .done
    mov ah, 0x0E
    mov bh, 0x00
    mov bl, 0x0F
    int 0x10
    jmp print_string
.done:
    ret

bits 32
init_pm:
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000
    mov esp, ebp

    jmp CODE_SEG:0x1000

    jmp $

gdt_start:
    dd 0x0
    dd 0x0

    dw 0xFFFF
    dw 0x0000
    db 0x00
    db 10011010b
    db 11001111b
    db 0x00

    dw 0xFFFF
    dw 0x0000
    db 0x00
    db 10010010b
    db 11001111b
    db 0x00

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

CODE_SEG equ 0x08
DATA_SEG equ 0x10

boot_drive db 0
stage2_msg db "Stage 2 loaded! ", 0
loading_kernel_msg db "Loading kernel... ", 0
kernel_loaded_msg db "OK!", 13, 10, 0
pmode_msg db "Switching to 32-bit mode...", 13, 10, 0
disk_error_msg db "Kernel load failed!", 0

times 512-($-$$) db 0
