; FynOS Kernel Entry Point
; Assembly stub that calls C kernel

bits 32

section .note.GNU-stack noalloc noexec nowrite progbits
section .text

global _start
extern kernel_main

_start:
    ; Set up stack
    mov esp, 0x90000
    mov ebp, esp
    
    ; Call C kernel
    call kernel_main
    
    ; Hang if kernel returns
.hang:
    hlt
    jmp .hang