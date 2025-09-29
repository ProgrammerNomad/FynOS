; FynOS — First Stage Bootloader (512B)
; Loads second stage and kernel from disk

bits 16
org 0x7C00

; Set up segments
mov ax, 0
mov ds, ax
mov es, ax
mov ss, ax
mov sp, 0x7C00

; Clear screen
mov ax, 0x0003
int 0x10

; Display loading message
mov si, loading_msg
call print_string

; Save boot drive
mov [boot_drive], dl

; Load second stage bootloader
mov bx, 0x7E00             ; Load at 0x7E00
mov dh, 0                  ; Head 0
mov dl, [boot_drive]       ; Boot drive
mov ch, 0                  ; Cylinder 0
mov cl, 2                  ; Sector 2
mov al, 1                  ; Load 1 sector

mov ah, 0x02               ; BIOS read sectors function
int 0x13                   ; Call BIOS
jc disk_error              ; Jump if error

; Jump to second stage
jmp 0x7E00

disk_error:
    mov si, error_msg
    call print_string
    jmp $

print_string:
    lodsb
    or al, al
    jz .done
    mov ah, 0x0E
    mov bh, 0x00
    mov bl, 0x07
    int 0x10
    jmp print_string
.done:
    ret

; Data
boot_drive db 0
loading_msg db "Loading FynOS...", 13, 10, 0
error_msg db "Boot Error!", 0

times 510-($-$$) db 0
dw 0xAA55           ; boot signature