# Scheduler Architecture

> Status: **Planned (v0.3+)**

## Overview

The FynOS scheduler will manage process execution, switching between tasks cooperatively then preemptively.

## Planned Design

- Round-robin preemptive scheduling via PIT timer interrupt
- Process control blocks in `kernel/process/`
- Context switch in `kernel/arch/x86/switch.asm`

## API (Planned)

```c
void scheduler_init(void);
void scheduler_add_task(task_t *task);
void scheduler_yield(void);
```

## Rules

- Scheduler never touches hardware directly - uses timer driver and arch switch routines
- Drivers are not aware of scheduling

## Dependencies

- Memory: paging and per-process address spaces
- Process manager: task creation and destruction
- CPU: timer interrupt (PIT), IDT

## References

- [OSDev Wiki - Scheduling](https://wiki.osdev.org/Scheduling)
