# FynOS Development Notes

## Version 0.0.1 - Initial Boot Sector

### Current Status
- ✅ 512-byte BIOS boot sector
- ✅ Prints "Welcome to FynOS!" message
- ✅ Basic project structure

### Technical Details

#### Boot Process
1. BIOS loads our 512-byte boot sector to memory address `0x7C00`
2. CPU starts in 16-bit real mode
3. Clear screen and set text mode (INT 10h, AX=0003h)
4. Print welcome message using BIOS interrupt
5. Infinite loop to prevent system from continuing

#### Memory Layout (16-bit Real Mode)
```
0x0000:0x0000 - 0x0000:0x03FF  Interrupt Vector Table
0x0000:0x0400 - 0x0000:0x04FF  BIOS Data Area
0x0000:0x0500 - 0x0000:0x7BFF  Free memory
0x0000:0x7C00 - 0x0000:0x7DFF  Boot sector (our code)
0x0000:0x7E00 - 0x0009:0xFFFF  Free memory
```

#### Code Structure
- `bits 16`: Tells NASM we're working in 16-bit mode
- `org 0x7C00`: Sets the origin address where BIOS loads us
- Boot signature `0xAA55` at bytes 510-511 tells BIOS this is bootable

### Next Steps for v0.1.0
1. ✅ Create a second-stage bootloader
2. ✅ Switch to 32-bit protected mode  
3. ✅ Load a simple C kernel
4. ✅ Set up basic VGA text output from C code

## Version 0.1.0 - 32-bit Protected Mode Kernel

### Current Status
- ✅ Multi-stage bootloader (512B + 512B)
- ✅ 32-bit protected mode switching
- ✅ C kernel with VGA text output
- ✅ Cross-platform build system

### New Architecture

#### Boot Process
1. **Stage 1 (boot.asm)**: BIOS loads 512 bytes at 0x7C00
   - Sets up segments and stack
   - Loads stage 2 from disk sector 2
   - Jumps to stage 2 at 0x7E00

2. **Stage 2 (stage2.asm)**: 512-byte second stage loader
   - Loads kernel from disk (sectors 3-17)
   - Sets up Global Descriptor Table (GDT)
   - Switches CPU to 32-bit protected mode
   - Jumps to C kernel at 0x1000

3. **Kernel (kernel.c)**: C-based kernel
   - VGA text mode output with colors
   - Proper cursor handling and screen management
   - Modular design for future expansion

#### Memory Layout (Protected Mode)
```
0x00000000 - 0x000003FF  Interrupt Vector Table (real mode)
0x00000400 - 0x000004FF  BIOS Data Area
0x00000500 - 0x00007BFF  Free memory
0x00007C00 - 0x00007DFF  Stage 1 bootloader
0x00007E00 - 0x00007FFF  Stage 2 bootloader
0x00001000 - 0x0000FFFF  Kernel code and data
0x00010000 - 0x0008FFFF  Free memory
0x00090000 - 0x0009FFFF  Stack space
0x000B8000 - 0x000B8FA0  VGA text buffer
```

#### Build Requirements
- **NASM**: Assembly compilation
- **GCC**: C compiler with 32-bit support
- **LD**: GNU linker
- **QEMU**: Testing and debugging

### Installation Instructions

#### Windows - Install MinGW-w64
1. Download from: https://www.mingw-w64.org/downloads/
2. Install with 32-bit support
3. Add to PATH: `C:\mingw64\bin`

#### Alternative: Use WSL
```bash
sudo apt update
sudo apt install build-essential gcc-multilib
```

### Resources
- [OSDev Wiki - Boot Sequence](https://wiki.osdev.org/Boot_Sequence)
- [OSDev Wiki - Real Mode](https://wiki.osdev.org/Real_Mode)
- [BIOS Interrupts](https://wiki.osdev.org/BIOS)