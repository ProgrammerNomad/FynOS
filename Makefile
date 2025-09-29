# FynOS Makefile v0.1.0
# Build system for FynOS operating system

# Directories
BUILD_DIR = build
BOOT_DIR = boot
BIOS_DIR = $(BOOT_DIR)/bios
KERNEL_DIR = kernel
ARCH_DIR = $(KERNEL_DIR)/arch/x86

# Tools
NASM = nasm
CC = gcc
LD = ld
QEMU = qemu-system-i386

# Compiler flags
CFLAGS = -m32 -ffreestanding -fno-builtin -fno-stack-protector -nostdlib -Wall -Wextra
LDFLAGS = -m elf_i386

# Default target
all: $(BUILD_DIR)/fynos.img

# Build complete OS image
$(BUILD_DIR)/fynos.img: $(BUILD_DIR)/boot.bin $(BUILD_DIR)/stage2.bin $(BUILD_DIR)/kernel.bin | $(BUILD_DIR)
	cat $^ > $@
	@echo "FynOS v0.1.0 built successfully!"

# Build boot sector (stage 1)
$(BUILD_DIR)/boot.bin: $(BIOS_DIR)/boot.asm | $(BUILD_DIR)
	$(NASM) -f bin $< -o $@

# Build stage 2 bootloader
$(BUILD_DIR)/stage2.bin: $(BIOS_DIR)/stage2.asm | $(BUILD_DIR)
	$(NASM) -f bin $< -o $@

# Build kernel
$(BUILD_DIR)/kernel.bin: $(BUILD_DIR)/entry.o $(BUILD_DIR)/kernel.o
	$(LD) $(LDFLAGS) -T $(KERNEL_DIR)/linker.ld -o $@ $^

# Build kernel entry point
$(BUILD_DIR)/entry.o: $(ARCH_DIR)/entry.asm | $(BUILD_DIR)
	$(NASM) -f elf32 $< -o $@

# Build kernel C code
$(BUILD_DIR)/kernel.o: $(KERNEL_DIR)/kernel.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Run in QEMU
run: $(BUILD_DIR)/fynos.img
	$(QEMU) -drive format=raw,file=$<

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)/*

# Debug with QEMU monitor
debug: $(BUILD_DIR)/fynos.img
	$(QEMU) -drive format=raw,file=$< -monitor stdio

# Legacy v0.0.1 build (simple bootloader only)
legacy: $(BUILD_DIR)/boot-simple.bin

$(BUILD_DIR)/boot-simple.bin: $(BIOS_DIR)/boot-simple.asm | $(BUILD_DIR)
	$(NASM) -f bin $< -o $@

.PHONY: all run clean debug legacy