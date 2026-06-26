# FynOS Build Instructions

## Development Platform

**Linux/WSL only.** No Windows native build scripts.

```
Windows  ->  WSL Ubuntu  ->  make
```

## Prerequisites

```bash
sudo apt update
sudo apt install -y nasm qemu-system-x86 build-essential gcc-multilib
```

Verify:

```bash
nasm -v
gcc --version
ld --version
qemu-system-i386 --version
```

## Build

From the project root (in WSL):

```bash
make
```

Output:

```
build/boot.bin      # Stage 1 bootloader
build/stage2.bin    # Stage 2 loader
build/kernel.bin    # C kernel (flat binary)
build/fynos.img     # Complete bootable image
```

## Run in QEMU

```bash
make run
```

Normal development - QEMU window stays open (`-no-shutdown`).

### Debug when QEMU exits or hangs

```bash
make run-debug
```

Shows **serial boot log** in your terminal (`BOOT 1`, `BOOT 2`, ...) and writes `qemu.log` for CPU resets and triple faults.

```bash
make run-gdb
```

In another terminal:

```bash
gdb build/kernel.elf
(gdb) target remote :1234
```

### Workflow

1. `make run` - normal
2. `make run-debug` - if QEMU closes or kernel hangs
3. `make run-gdb` - step through code

Click inside the QEMU window before typing. Press Ctrl+Alt+G to release the mouse.

## Clean

```bash
make clean
# or
./scripts/clean.sh
```

## Legacy v0.0 Build

Build only the original single-sector boot sector:

```bash
make legacy
qemu-system-i386 -drive format=raw,file=build/boot-simple.bin
```

## Troubleshooting

### `gcc: error: unrecognized command line option '-m32'`

Install 32-bit support:

```bash
sudo apt install gcc-multilib
```

### QEMU not found

```bash
sudo apt install qemu-system-x86
```

### Permission denied on scripts

```bash
chmod +x scripts/*.sh
```

### Clock skew warnings on /mnt/c/

If you see `Clock skew detected` while building on `/mnt/c/...`, copy the project to native WSL storage:

```bash
cp -r /mnt/c/xampp/htdocs/FynOS ~/FynOS
cd ~/FynOS
make clean && make && make run
```

### No bootable device in QEMU

Rebuild after pulling fixes. `make run` must use `-fda` (floppy), not IDE. Run `make clean && make && make run`.

## Architecture

The build produces a flat disk image:

| Sector | Content |
|--------|---------|
| 1 | Stage 1 (`boot/bios/boot.asm`) |
| 2 | Stage 2 (`boot/bios/stage2.asm`) |
| 3+ | Kernel binary |

See [`docs/architecture/boot.md`](architecture/boot.md) for boot chain details.
