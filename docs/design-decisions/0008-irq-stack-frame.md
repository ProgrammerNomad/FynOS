# ADR 0008: IRQ ISR stack frame (OSDev layout)

## Problem

Enabling interrupts (`sti`) crashed the kernel on the first IRQ. QEMU logged invalid opcode and page faults after vector `0x20` (PIT). `uptime` could not work without a reliable IRQ 0 handler.

## Options

- Keep keyboard polling and leave IRQ disabled
- Patch `add esp, 8` / `registers_t` offsets incrementally
- Align `isr.asm` with the [OSDev interrupt stub pattern](https://wiki.osdev.org/Handling_Interrupts) and fix section placement

## Decision

1. Place ISR stubs in `section .text` (not `.note.GNU-stack`).
2. Use OSDev-style `isr_common`: `pusha`, save segment registers via `push eax` after reading each selector, call `isr_handler(esp)`, restore segments with `pop eax` / `mov`, `popa`, `add esp, 8`, `iret`.
3. Match `registers_t` in `idt.h` to the stack layout: `gs, fs, es, ds`, then `eax` through `edi` (pusha order), then `int_no` and `err_code`.
4. Use `ISR_ERR` only for CPU exceptions that push an error code (10–14, 17). Use `ISR_NOERR` for double fault (8) and all IRQ stubs (32–47).
5. Panic only on CPU exceptions (`int_no < 32`); IRQ handlers always send PIC EOI.

## Why

ISR code in `.note.GNU-stack` was not linked into executable `.text`, so the first interrupt jumped into non-code bytes. Correct stack layout and exception stub pairing prevent bad `iret` returns. Serial `BOOT 8` and ~100 Hz timer interrupts confirm the fix.
