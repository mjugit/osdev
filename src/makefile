AS = "$$HOME/tools/crc/bin/i686-elf-as"
GCC = "$$HOME/tools/crc/bin/i686-elf-gcc"
CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra

BUILD_DIR = ../build
OBJ_DIR = ../build/obj
ISO_DIR = ../build/iso
BOOT_DST = ../build/iso/boot
GRUB_DIR = ../build/iso/boot/grub

OBJECTS = $(OBJ_DIR)/boot.o $(OBJ_DIR)/kernel.o $(OBJ_DIR)/string.o

IMG = sys_img.bin

.PHONY: mkdirs
all: mkdirs $(OBJECTS) iso/*
	$(GCC) -T linker.ld -o $(BUILD_DIR)/$(IMG) -ffreestanding -O2 -nostdlib $(OBJ_DIR)/* -lgcc
	cp $(BUILD_DIR)/$(IMG) $(BOOT_DST)
	cp iso/bootloader.cfg $(GRUB_DIR)/grub.cfg;
	grub-mkrescue -o $(ISO_DIR)/system-img-$$(date +%F).iso $(ISO_DIR)

mkdirs:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(GRUB_DIR)

.PHONY: clean
clean:
	rm $(OBJ_DIR)/*
	rm -r $(ISO_DIR)/*
	rm $(BUILD_DIR)/$(IMG)

$(OBJ_DIR)/boot.o: boot.s
	$(AS) boot.s -o $(OBJ_DIR)/boot.o

$(OBJ_DIR)/kernel.o: kernel.c
	$(GCC) -c kernel.c -o $(OBJ_DIR)/kernel.o $(CFLAGS)

$(OBJ_DIR)/string.o: include/string.c include/string.h
	$(GCC) -c include/string.c -o $(OBJ_DIR)/string.o$(CFLAGS)
