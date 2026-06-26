# Security Architecture

> Status: **Planned (evolves with userspace)**

## Overview

FynOS security model will grow from a single ring-0 kernel (v0.1) to ring separation with syscalls (v0.5+).

## v0.1 - Kernel Only

- All code runs in ring 0 (supervisor mode)
- No userspace isolation yet
- No authentication - single-user by design

## v0.5+ - Ring Separation (Planned)

```
Ring 3: Userspace applications
Ring 0: Kernel + drivers
```

- Syscall gate via `int 0x80` or `sysenter`
- Applications cannot access hardware or kernel memory
- Each process gets isolated address space (requires paging)

## Future Hardening

- Stack canaries in kernel builds
- W^X (write xor execute) pages when paging enabled
- Capability-based permissions for drivers
- Secure boot chain with UEFI

## Rules

- Applications cannot access hardware directly - ever
- Syscall interface is the only userspace -> kernel boundary
- Driver code runs in ring 0 but is isolated by module boundaries

## References

- [OSDev Wiki - Syscalls](https://wiki.osdev.org/Syscall)
- [OSDev Wiki - Paging](https://wiki.osdev.org/Paging)
