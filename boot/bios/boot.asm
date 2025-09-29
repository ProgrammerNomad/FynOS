; FynOS — BIOS boot sector (512B)
bits 16
org 0x7C00

mov ax, 0x0003      ; clear screen to text mode
int 0x10

mov si, msg
call print

jmp $               ; hang forever

print:
    lodsb
    or  al, al
    jz  .done
    mov ah, 0x0E
    mov bh, 0x00
    mov bl, 0x07
    int 0x10
    jmp print
.done:
    ret

msg db "Welcome to FynOS!", 0

times 510-($-$$) db 0
dw 0xAA55           ; boot signature