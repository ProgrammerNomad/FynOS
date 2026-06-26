# FynOS Makefile
# Single canonical build system - Linux/WSL only

BUILD_DIR = build
BIOS_DIR  = boot/bios
KERNEL_DIR = kernel
ARCH_DIR  = $(KERNEL_DIR)/arch/x86

NASM = nasm
CC   = gcc
LD   = ld
OBJCOPY = objcopy
QEMU = qemu-system-i386

CFLAGS = -m32 -std=c99 -ffreestanding -fno-builtin -fno-stack-protector \
         -nostdlib -Wall -Wextra -Werror \
         -I$(KERNEL_DIR) -I$(KERNEL_DIR)/include

LDFLAGS = -m elf_i386

KERNEL_C_SRCS = \
	$(KERNEL_DIR)/kernel.c \
	$(KERNEL_DIR)/cpu/pic.c \
	$(KERNEL_DIR)/cpu/idt.c \
	$(KERNEL_DIR)/video/vga.c \
	$(KERNEL_DIR)/video/framebuffer.c \
	$(KERNEL_DIR)/memory/phys.c \
	$(KERNEL_DIR)/drivers/keyboard.c \
	$(KERNEL_DIR)/terminal/shell.c \
	$(KERNEL_DIR)/terminal/commands.c \
	$(KERNEL_DIR)/fs/vfs.c \
	$(KERNEL_DIR)/fs/fat32.c

KERNEL_C_OBJS = $(patsubst $(KERNEL_DIR)/%.c,$(BUILD_DIR)/kernel/%.o,$(KERNEL_C_SRCS))

KERNEL_ASM_OBJS = $(BUILD_DIR)/kernel/arch/x86/entry.o \
                  $(BUILD_DIR)/kernel/cpu/isr.o

KERNEL_OBJS = $(KERNEL_C_OBJS) $(KERNEL_ASM_OBJS)

.PHONY: all run clean debug legacy

all: $(BUILD_DIR)/fynos.img

$(BUILD_DIR)/fynos.img: $(BUILD_DIR)/boot.bin $(BUILD_DIR)/stage2.bin $(BUILD_DIR)/kernel.bin | $(BUILD_DIR)
	cat $^ > $@
	truncate -s 1474560 $@
	@echo "FynOS built successfully."

$(BUILD_DIR)/boot.bin: $(BIOS_DIR)/boot.asm | $(BUILD_DIR)
	$(NASM) -f bin $< -o $@

# stage2 must be built after kernel.bin so sector count matches actual kernel size
$(BUILD_DIR)/stage2.bin: $(BIOS_DIR)/stage2.asm $(BUILD_DIR)/kernel.bin | $(BUILD_DIR)
	$(NASM) -f bin -DKERNEL_SECTORS=$(shell echo $$(( ($$(wc -c < $(BUILD_DIR)/kernel.bin | tr -d ' ') + 511) / 512 ))) $< -o $@

$(BUILD_DIR)/kernel.bin: $(BUILD_DIR)/kernel.elf
	$(OBJCOPY) -O binary $< $@
	truncate -s %512 $@

$(BUILD_DIR)/kernel.elf: $(KERNEL_OBJS) $(KERNEL_DIR)/linker.ld | $(BUILD_DIR)
	$(LD) $(LDFLAGS) -T $(KERNEL_DIR)/linker.ld -o $@ $(KERNEL_OBJS)

$(BUILD_DIR)/kernel/%.o: $(KERNEL_DIR)/%.c | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/kernel/arch/x86/entry.o: $(ARCH_DIR)/entry.asm | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(NASM) -f elf32 $< -o $@

$(BUILD_DIR)/kernel/cpu/isr.o: $(KERNEL_DIR)/cpu/isr.asm | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(NASM) -f elf32 $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

run: $(BUILD_DIR)/fynos.img
	$(QEMU) -no-reboot -fda $<

debug: $(BUILD_DIR)/fynos.img
	$(QEMU) -no-reboot -fda $< -monitor stdio

clean:
	rm -rf $(BUILD_DIR)

legacy: $(BUILD_DIR)/boot-simple.bin

$(BUILD_DIR)/boot-simple.bin: $(BIOS_DIR)/boot-simple.asm | $(BUILD_DIR)
	$(NASM) -f bin $< -o $@
