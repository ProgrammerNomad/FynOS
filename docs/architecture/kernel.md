# Kernel Architecture

> Status: **v0.1 in progress**

## Overview

The FynOS kernel is written in C with assembly reserved for architecture entry (`kernel/arch/x86/entry.asm`) and interrupt stubs.

## Layer Model

```
HAL / arch  ->  cpu  ->  memory  ->  drivers  ->  terminal/video
```

Future layers: process, ipc, scheduler, fs, syscalls.

## Entry Point

1. `boot/bios/stage2.asm` jumps to `0x1000`
2. `kernel/arch/x86/entry.asm` `_start` sets stack, calls `kernel_main()`
3. `kernel/kernel.c` `kernel_main()` initializes subsystems

## Initialization Order (v0.1)

```
kernel_main()
  |- idt_init()        # CPU: interrupt descriptor table
  |- vga_init()        # Video: clear screen
  |- phys_init()       # Memory: bump allocator
  |- keyboard_init()   # Drivers: PS/2 keyboard
  `- shell_run()       # Terminal: interactive CLI
```

## Module Layout

```
kernel/
|- kernel.c              # Init orchestrator only
|- arch/x86/entry.asm    # Boot handoff
|- cpu/idt.c             # Interrupts
|- memory/phys.c         # Physical memory allocator
|- drivers/keyboard.c    # PS/2 keyboard
|- terminal/shell.c      # CLI shell
|- video/vga.c           # VGA text mode
`- include/types.h       # Shared types
```

## Rules

- `kernel.c` does not contain driver logic - only calls subsystem init
- Subsystems communicate via public APIs in their `.h` files
- No subsystem accesses hardware outside its layer (drivers -> ports, video -> VGA memory)

## Future

- Syscall interface for userspace (`kernel/arch/x86/syscall.asm`)
- Process manager in `kernel/process/`
- Scheduler in `kernel/scheduler/`
