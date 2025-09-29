# FynOS Makefile
# Build system for FynOS operating system

# Directories
BUILD_DIR = build
BOOT_DIR = boot
BIOS_DIR = $(BOOT_DIR)/bios

# Tools
NASM = nasm
QEMU = qemu-system-i386

# Default target
all: $(BUILD_DIR)/boot.bin

# Build boot sector
$(BUILD_DIR)/boot.bin: $(BIOS_DIR)/boot.asm | $(BUILD_DIR)
	$(NASM) -f bin $< -o $@
	@echo "Boot sector built successfully!"

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Run in QEMU
run: $(BUILD_DIR)/boot.bin
	$(QEMU) -drive format=raw,file=$<

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)/*

# Debug with QEMU monitor
debug: $(BUILD_DIR)/boot.bin
	$(QEMU) -drive format=raw,file=$< -monitor stdio

.PHONY: all run clean debug