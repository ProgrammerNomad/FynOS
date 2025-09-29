# FynOS 🌱
> **Tiny core — endless growth**

FynOS is a hobby operating system that starts as a **512-byte bootloader** that prints text on bare metal and gradually grows into a **C-based kernel**, **CLI shell**, and later a **GUI desktop**.

---

## ✨ Features (current & planned)
- **v0.0.1** – 512B BIOS boot sector that prints: `Welcome to FynOS!`
- **v0.1.0** – 32-bit protected-mode kernel written in C
- **v0.2.0** – VGA text-mode terminal & keyboard input
- **v0.3.0** – Paging, heap allocator, timer interrupts
- **v0.4.0** – GRUB boot + linear framebuffer → draw pixels
- **v0.5.0** – Simple userspace shell
- **v0.6.0+** – Window server, compositor, GUI toolkit

---

## 🗂️ Project Structure
```
FynOS/
├─ boot/              # Bootloaders (ASM)
│  └─ bios/           # 16-bit BIOS boot sector
├─ kernel/            # Core kernel (C + ASM)
│  ├─ arch/x86/       # Architecture-specific code
│  └─ drivers/        # Text, keyboard, etc.
├─ gui/               # Future GUI server & toolkit
├─ docs/              # Design notes, specifications
├─ build/             # Build artifacts (ignored in git)
└─ README.md          # You are here
```

---

## 🛠️ Build Environment

### Option 1: **Linux / WSL (Recommended)**
Install prerequisites:
```bash
sudo apt update
sudo apt install -y nasm qemu-system-x86 build-essential grub-pc-bin xorriso
```

### Option 2: **Windows Native**
- [NASM for Windows](https://www.nasm.us/pub/nasm/releasebuilds/)
- [QEMU for Windows](https://www.qemu.org/download/#windows)
- Use VS Code or any editor you like.

**✅ Verify:**
```bash
nasm -v
qemu-system-i386 --version
```

---

## 🚀 Quick Start — Hello World Boot Sector

### 1. `boot/bios/boot.asm`
```asm
; FynOS — BIOS boot sector (512B)
bits 16
org 0x7C00

mov ax, 0x0003      ; clear screen to text mode
int 0x10

mov si, msg
call print

jmp $               ; hang forever

print:
    lodsb
    or  al, al
    jz  .done
    mov ah, 0x0E
    mov bh, 0x00
    mov bl, 0x07
    int 0x10
    jmp print
.done:
    ret

msg db "Welcome to FynOS!", 0

times 510-($-$$) db 0
dw 0xAA55           ; boot signature
```

### 2. Build
```bash
nasm -f bin boot/bios/boot.asm -o build/boot.bin
```

### 3. Run in QEMU
```bash
qemu-system-i386 -drive format=raw,file=build/boot.bin
```

You should see:
```
Welcome to FynOS!
```

### 4. (Optional) Boot from USB — ⚠️ Dangerous
Write the boot sector to a USB drive (this erases its first 512 bytes!):
```bash
sudo dd if=build/boot.bin of=/dev/sdX bs=512 count=1 conv=notrunc
sync
```
*Replace `/dev/sdX` with your USB device.*

---

## 🧩 Next Milestones

### v0.1.0 — 32-bit Kernel in C
- Create a second-stage loader that switches CPU to protected mode.
- Print banner via VGA text mode.
- Add `kernel_main()` in C.

### v0.2.0 — Terminal
- Keyboard input (PS/2).
- Basic shell commands: `help`, `clear`, `mem`.

### v0.3.0 — Memory Management
- Enable paging and simple heap.
- Timer interrupt (PIT) for uptime.

### v0.4.0 — Framebuffer
- Boot via GRUB into linear framebuffer mode.
- Draw pixels, fonts, colors → set up for GUI.

### v0.5.0 — Userspace
- Implement a simple task switcher.
- Move shell to userspace via syscalls.

### v0.6.0 — GUI Alpha
- Window server manages framebuffer.
- Basic window, titlebar, close button.
- Mouse support.

---

## 🗒️ Development Notes
- **Target architecture:** x86 (32-bit) for simplicity.
- **Initial boot:** BIOS/Legacy → later add UEFI support.
- **Code style:** `-ffreestanding -m32`, no host libc.
- **Build tools:** nasm, ld, gcc/clang cross-compiler (`i686-elf-gcc`).
- **Emulation:** QEMU (fast) → later test on real hardware.

---

## 🤝 Contributing
1. Fork and clone the repo.
2. Create feature branches (`feat/keyboard`, `feat/gui-server`).
3. Submit PRs with clear commit messages.

---

## 📜 License
MIT License — free to learn, modify, and share.

---

## 🌟 Credits
FynOS is a hobby project to explore how operating systems boot and grow:
- Boot sector inspired by [OSDev Wiki](https://wiki.osdev.org/) examples.
- Developed by ProgrammerNomad ([@ProgrammerNomad](https://github.com/ProgrammerNomad)).

*"FynOS starts tiny — just text on screen — then grows into your own desktop OS."*
