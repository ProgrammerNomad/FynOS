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
1. Create a second-stage bootloader
2. Switch to 32-bit protected mode
3. Load a simple C kernel
4. Set up basic VGA text output from C code

### Resources
- [OSDev Wiki - Boot Sequence](https://wiki.osdev.org/Boot_Sequence)
- [OSDev Wiki - Real Mode](https://wiki.osdev.org/Real_Mode)
- [BIOS Interrupts](https://wiki.osdev.org/BIOS)