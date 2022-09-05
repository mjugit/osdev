# REMARK mju 22-09-03:
# Depending on where the toolchain was installed, the following paths to the compiler
# or assembler need to be changed. To use Bash variables in the script, the dollar sign
# $ introducing the variable must be masked as $$.

# Assembler options
#   Get by absolute path
# AS = $$HOME/tools/crc/bin/i686-elf-as
#   or - if you have it in your PATH -
AS = i686-elf-as

# C compiler options
#   Get by absolute path
# CC = $$HOME/tools/crc/bin/i686-elf-gcc
#   or - if you have it in your PATH -
CC = i686-elf-gcc

CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra
# Linker options
LFLAGS = -ffreestanding -O2 -nostdlib

# Output directories
BUILD_DIR = ../build
LIBC_OBJ_DIR = $(BUILD_DIR)/libc
LIBK_OBJ_DIR = $(BUILD_DIR)/libk
BOOT_OBJ_DIR = $(BUILD_DIR)/boot
ISO_DIR = $(BUILD_DIR)/iso
KERNEL_DIR = $(BUILD_DIR)

ISO = release.iso
KERNEL = $(KERNEL_DIR)/kernel.bin

# Object files

LIBC_OBJ = \
	$(LIBC_OBJ_DIR)/string.o

LIBK_OBJ = \
	$(LIBK_OBJ_DIR)/vga.o

BOOT_OBJ = \
	$(BOOT_OBJ_DIR)/boot.o

KERNEL_OBJ = $(LIBK_OBJ_DIR)/kmain.o

.PHONY: iso
iso: kernel | $(ISO_DIR)
	grub-mkrescue -o $(BUILD_DIR)/$(ISO) $(ISO_DIR)

$(ISO_DIR):
	mkdir -p $(ISO_DIR)/boot/grub
	cp boot/grub.cfg $(ISO_DIR)/boot/grub/grub.cfg
	cp $(KERNEL) $(ISO_DIR)/boot/kernel.bin

.PHONY: kernel
kernel: libk kmain.c boot | $(KERNEL_DIR)
	$(CC) -c kmain.c -o $(KERNEL_OBJ) $(CFLAGS)
	$(CC) -T linker.ld -o $(KERNEL) $(LFLAGS) \
		$(KERNEL_OBJ) \
		$(wildcard $(BOOT_OBJ_DIR)/*) \
		$(wildcard $(LIBC_OBJ_DIR)/*) \
		$(wildcard $(LIBK_OBJ_DIR)/*) \
		-lgcc


$(KERNEL_DIR):
	mkdir -p $(KERNEL_DIR)

.PHONY: clean
clean:
	rm -r $(BUILD_DIR)/*

# Rules for libc

.PHONY: libc
libc: $(LIBC_OBJ)

$(LIBC_OBJ_DIR)/%.o: libc/%.c | $(LIBC_OBJ_DIR)
	$(CC) -c $< -o $@ $(CFLAGS)

$(LIBC_OBJ_DIR):
	mkdir -p $(LIBC_OBJ_DIR)


# Rules for libk

.PHONY: libk
libk: libc $(LIBK_OBJ)

$(LIBK_OBJ_DIR)/%.o: libk/%.c | $(LIBK_OBJ_DIR)
	$(CC) -c $< -o $@ $(CFLAGS)

$(LIBK_OBJ_DIR):
	mkdir -p $(LIBK_OBJ_DIR)


# Rules for boot

.PHONY: boot
boot: $(BOOT_OBJ_DIR)/boot.o

$(BOOT_OBJ_DIR)/%.o: boot/%.s | $(BOOT_OBJ_DIR)
	$(AS) $< -o $@

$(BOOT_OBJ_DIR):
	mkdir -p $(BOOT_OBJ_DIR)

