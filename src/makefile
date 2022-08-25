AS = "$$HOME/tools/crc/bin/i686-elf-as"
GCC = "$$HOME/tools/crc/bin/i686-elf-gcc"
BUILD_DIR = ../build
OBJ_DIR = ../build/obj

OBJECTS = $(OBJ_DIR)/boot.o $(OBJ_DIR)/kernel.o
IMG = sys_img.bin

.PHONY: mkdirs
all: mkdirs $(OBJECTS)
	$(GCC) -T linker.ld -o $(BUILD_DIR)/$(IMG) -ffreestanding -O2 -nostdlib $(OBJ_DIR)/* -lgcc

mkdirs:
	mkdir -p $(OBJ_DIR)

.PHONY: clean
clean:
	rm $(OBJ_DIR)/*

$(OBJ_DIR)/boot.o: boot.s
	$(AS) boot.s -o $(OBJ_DIR)/boot.o

$(OBJ_DIR)/kernel.o: kernel.c
	$(GCC) -c kernel.c -o $(OBJ_DIR)/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
