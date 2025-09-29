; FynOS — Complete Stage 2 Bootloader
; Loads kernel and switches to 32-bit protected mode

bits 16
org 0x7E00                  ; Second stage loads at 0x7E00

; Save boot drive number
mov [boot_drive], dl

; Clear screen and show progress
mov ax, 0x0003
int 0x10

mov si, stage2_msg
call print_string

; Load kernel from disk
mov si, loading_kernel_msg
call print_string

mov bx, 0x1000             ; Load kernel at 0x1000
mov dh, 0                  ; Head 0
mov dl, [boot_drive]       ; Boot drive
mov ch, 0                  ; Cylinder 0
mov cl, 3                  ; Start from sector 3 (sector 2 is this loader)
mov al, 1                  ; Load 1 sector (kernel)

mov ah, 0x02               ; BIOS read sectors function
int 0x13                   ; Call BIOS

jc disk_error              ; Jump if error

; Print success message
mov si, kernel_loaded_msg
call print_string

; Small delay to let user see messages
mov cx, 0xFFFF
delay_loop:
    nop
    loop delay_loop

; Switch to protected mode
mov si, pmode_msg
call print_string

cli                        ; Disable interrupts
lgdt [gdt_descriptor]      ; Load Global Descriptor Table
mov eax, cr0
or eax, 1                  ; Set PE bit
mov cr0, eax

; Far jump to 32-bit code
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
    mov bl, 0x0F            ; White
    int 0x10
    jmp print_string
.done:
    ret

bits 32
init_pm:
    ; Set up protected mode segment registers
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; Set up stack
    mov ebp, 0x90000
    mov esp, ebp

    ; Jump to kernel main
    jmp 0x1000

    ; Hang if kernel returns
    jmp $

; Global Descriptor Table
gdt_start:
    ; Null descriptor
    dd 0x0
    dd 0x0

    ; Code segment descriptor
    dw 0xFFFF       ; Limit low
    dw 0x0000       ; Base low
    db 0x00         ; Base middle
    db 10011010b    ; Access byte
    db 11001111b    ; Flags + limit high
    db 0x00         ; Base high

    ; Data segment descriptor
    dw 0xFFFF       ; Limit low
    dw 0x0000       ; Base low
    db 0x00         ; Base middle
    db 10010010b    ; Access byte
    db 11001111b    ; Flags + limit high
    db 0x00         ; Base high

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1  ; Size
    dd gdt_start                ; Offset

; Constants
CODE_SEG equ gdt_start + 8
DATA_SEG equ gdt_start + 16

; Data
boot_drive db 0
stage2_msg db "Stage 2 loaded! ", 0
loading_kernel_msg db "Loading kernel... ", 0
kernel_loaded_msg db "OK!", 13, 10, 0
pmode_msg db "Switching to 32-bit mode...", 13, 10, 0
disk_error_msg db "Kernel load failed!", 0

; Padding
times 512-($-$$) db 0