# FynOS v0.1.0 - Toolchain Setup

## Required Tools for v0.1.0

To build FynOS v0.1.0 with the C kernel, you need:

1. **NASM** - Netwide Assembler ✅ (You have this)
2. **GCC** - GNU Compiler Collection with 32-bit support
3. **LD** - GNU Linker
4. **QEMU** - Emulator ✅ (You have this)

## Installation Options

### Option 1: MinGW-w64 (Recommended for Windows)

1. **Download MinGW-w64:**
   - Go to: https://www.mingw-w64.org/downloads/
   - Choose "MingW-W64-builds"
   - Download the installer

2. **Install with these settings:**
   - Architecture: `i686` (32-bit support)
   - Threads: `posix`
   - Exception: `dwarf`
   - Build revision: latest

3. **Add to PATH:**
   - Add `C:\mingw32\bin` to your Windows PATH
   - Restart PowerShell

### Option 2: WSL Ubuntu (Alternative)

If you prefer Linux environment:

```bash
# Install WSL if needed
wsl --install -d Ubuntu

# Inside WSL, install build tools
sudo apt update
sudo apt install build-essential gcc-multilib nasm qemu-system-x86
```

### Option 3: MSYS2 (Another Windows option)

1. Install MSYS2 from: https://www.msys2.org/
2. Run MSYS2 terminal and install packages:
```bash
pacman -S mingw-w64-i686-gcc mingw-w64-i686-binutils nasm
```

## Testing Installation

After installing, test in PowerShell:

```powershell
# Test GCC
gcc --version

# Test 32-bit compilation
gcc -m32 --version

# Test linker
ld --version

# Test NASM (should work)
nasm -v

# Test QEMU (should work)
qemu-system-i386 --version
```

## Build v0.1.0

Once you have the toolchain:

```powershell
# Windows batch script
.\build.bat

# Or step by step:
nasm -f bin boot\bios\boot.asm -o build\boot.bin
nasm -f bin boot\bios\stage2.asm -o build\stage2.bin
nasm -f elf32 kernel\arch\x86\entry.asm -o build\entry.o
gcc -m32 -ffreestanding -fno-builtin -fno-stack-protector -nostdlib -Wall -Wextra -c kernel\kernel.c -o build\kernel.o
ld -m elf_i386 -T kernel\linker.ld -o build\kernel.bin build\entry.o build\kernel.o
copy /b build\boot.bin + build\stage2.bin + build\kernel.bin build\fynos.img
qemu-system-i386 -drive format=raw,file=build\fynos.img
```

## Expected Result

When successful, you should see:
```
Welcome to FynOS v0.1.0!
32-bit Protected Mode Kernel

Features:
- 32-bit protected mode
- C kernel
- VGA text output
- Multi-stage bootloader

System ready!
```

## For Now: Test Stage 1 Only

Since you don't have GCC yet, let's test just the updated stage 1 bootloader:

```powershell
# Build just stage 1 (works with NASM only)
nasm -f bin boot\bios\boot.asm -o build\boot.bin
qemu-system-i386 -drive format=raw,file=build\boot.bin
```

You should see "Loading FynOS..." followed by "Boot Error!" (expected, since stage 2 isn't loaded from disk properly in QEMU without a full disk image).