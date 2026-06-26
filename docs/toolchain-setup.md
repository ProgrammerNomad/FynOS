# FynOS Toolchain Setup

## Development Platform

**Linux/WSL only.** See `docs/build-instructions.md`.

Windows users:

```
Windows -> WSL Ubuntu -> make
```

## Install (WSL Ubuntu)

```bash
sudo apt update
sudo apt install -y nasm qemu-system-x86 build-essential gcc-multilib
```

## Verify

```bash
nasm -v
gcc --version
ld --version
qemu-system-i386 --version
```

## Build Kernel

```bash
cd /path/to/FynOS
make
make run
```

## Compiler Flags

Defined in `Makefile`:

```
-m32 -std=c99 -ffreestanding -fno-builtin -fno-stack-protector
-nostdlib -Wall -Wextra -Werror
```

## Cross-Compiler (Future)

For self-hosting (v4.x), an `i686-fynos-gcc` cross-compiler may be added under `tools/`.

Currently the host GCC with `-m32` is sufficient.
