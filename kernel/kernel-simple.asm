; FynOS — 32-bit Protected Mode Kernel (Assembly version)
; Demonstrates protected mode with colorful VGA output

bits 32
org 0x1000

; Kernel entry point
kernel_main:
    ; Clear screen first
    call clear_screen
    
    ; Print title with green color
    mov edi, 0xB8000        ; VGA text buffer
    mov esi, title_msg
    mov ah, 0x2F            ; Bright white on green
    call print_string
    
    ; Move to next line
    add edi, 160            ; Next line (80 chars * 2 bytes)
    
    ; Print version info
    mov esi, version_msg
    mov ah, 0x0A            ; Bright green on black
    call print_string
    
    ; Move to next line and skip one
    add edi, 320            ; Skip 2 lines
    
    ; Print features list
    mov esi, features_msg
    mov ah, 0x0F            ; White on black
    call print_string
    
    add edi, 160
    mov esi, feature1_msg
    mov ah, 0x0E            ; Yellow on black
    call print_string
    
    add edi, 160
    mov esi, feature2_msg
    mov ah, 0x0E
    call print_string
    
    add edi, 160
    mov esi, feature3_msg
    mov ah, 0x0E
    call print_string
    
    add edi, 160
    mov esi, feature4_msg
    mov ah, 0x0E
    call print_string
    
    ; Skip a line and print status
    add edi, 320
    mov esi, status_msg
    mov ah, 0x0B            ; Bright cyan on black
    call print_string
    
    ; Demo color cycling
    add edi, 320
    mov esi, demo_msg
    mov ah, 0x0C            ; Bright red on black
    call print_string
    
    ; Color animation loop
color_demo:
    push edi
    mov ecx, 16             ; 16 colors
    mov al, '*'
    
color_loop:
    mov ah, cl              ; Use counter as color
    mov [edi], ax
    add edi, 2
    loop color_loop
    pop edi
    
    ; Wait a bit
    mov ecx, 0x3FFFFFF
delay:
    nop
    loop delay
    
    ; Infinite loop with halt
hang:
    hlt
    jmp hang

; Clear screen function
clear_screen:
    push eax
    push ecx
    push edi
    
    mov edi, 0xB8000
    mov eax, 0x0720         ; Space with gray on black
    mov ecx, 2000           ; 80x25 screen
    rep stosw
    
    pop edi
    pop ecx
    pop eax
    ret

; Print string function
print_string:
    push eax
.loop:
    lodsb
    test al, al
    jz .done
    mov [edi], ax
    add edi, 2
    jmp .loop
.done:
    pop eax
    ret

; Data
title_msg db "    FynOS v0.1.0 - 32-bit Protected Mode Kernel    ", 0
version_msg db "Successfully booted into protected mode!", 0
features_msg db "Features:", 0
feature1_msg db "  * Multi-stage bootloader", 0
feature2_msg db "  * 32-bit protected mode", 0
feature3_msg db "  * VGA text mode output", 0
feature4_msg db "  * Assembly kernel", 0
status_msg db "System Status: RUNNING", 0
demo_msg db "Color Demo: ", 0

; Padding to make it a full sector
times 512-($-$$) db 0