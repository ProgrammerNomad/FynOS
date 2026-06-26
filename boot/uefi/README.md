# UEFI Boot (Planned)

UEFI boot loader for FynOS. Will become the primary boot path before desktop work.

## Status

Not yet implemented. See `docs/architecture/boot.md`.

## Planned Layout

```
boot/uefi/
|- main.c           # UEFI application entry
|- boot.c           # Load kernel from EFI partition
`- linker.ld        # PE/COFF linker script
```

## Boot Flow

```
UEFI Firmware -> boot/uefi/main.c -> Load kernel.elf -> ExitBootServices -> kernel
