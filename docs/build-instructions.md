# FynOS Build Instructions

## Prerequisites

### Windows
1. **NASM (Netwide Assembler)**
   - Download from: https://www.nasm.us/pub/nasm/releasebuilds/
   - Install and add to PATH

2. **QEMU**
   - Download from: https://www.qemu.org/download/#windows
   - Install and add to PATH

### Linux/WSL
```bash
sudo apt update
sudo apt install -y nasm qemu-system-x86 build-essential
```

## Building FynOS

### Method 1: Using the Batch File (Windows)
```cmd
build.bat
```

### Method 2: Manual Commands

#### Windows (PowerShell/CMD)
```cmd
# Create build directory
mkdir build

# Build boot sector
nasm -f bin boot\bios\boot.asm -o build\boot.bin

# Run in QEMU
qemu-system-i386 -drive format=raw,file=build\boot.bin
```

#### Linux/WSL
```bash
# Create build directory
mkdir -p build

# Build boot sector
nasm -f bin boot/bios/boot.asm -o build/boot.bin

# Run in QEMU
qemu-system-i386 -drive format=raw,file=build/boot.bin
```

### Method 3: Using Make (Linux/WSL)
```bash
make        # Build
make run    # Build and run
make clean  # Clean build artifacts
```

## Expected Output

When you run the boot sector in QEMU, you should see:
```
Welcome to FynOS!
```

The cursor will blink below the message, and the system will be in an infinite loop.

## Troubleshooting

### "nasm: command not found"
- Ensure NASM is installed and in your PATH
- On Windows, restart your command prompt after installation

### "qemu-system-i386: command not found"
- Ensure QEMU is installed and in your PATH
- On Windows, the executable might be named differently

### Boot sector doesn't display message
- Check that the boot.bin file is exactly 512 bytes
- Verify the boot signature (0xAA55) is present at the end

## Testing on Real Hardware (Advanced)

⚠️ **WARNING: This will overwrite data on your USB drive!**

1. Insert a USB drive (will be completely erased)
2. Find the device name (e.g., `/dev/sdb` on Linux, `\\.\PhysicalDrive1` on Windows)
3. Write the boot sector:

**Linux:**
```bash
sudo dd if=build/boot.bin of=/dev/sdX bs=512 count=1 conv=notrunc
sync
```

**Windows (as Administrator):**
```cmd
dd if=build\boot.bin of=\\.\PhysicalDrive1 bs=512 count=1
```

Replace `/dev/sdX` or `PhysicalDrive1` with your actual USB device identifier.